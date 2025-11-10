#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstdarg>  // 用于解析可变参数
#include <python3.12/Python.h>
#include <python3.12/abstract.h>
#include <python3.12/import.h>
#include <python3.12/listobject.h>
#include <python3.12/object.h>
#include <python3.12/pylifecycle.h>
#include <python3.12/pytypedefs.h>
#include <python3.12/unicodeobject.h>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstring>

#include "../MemoryPool/MemoryPool.h"
#include "Configure.h"

enum class PyReturnType
{
    NONE = 1,
    INT = 2,
    DOUBLE = 3,
    BOOL = 4,
    FLOAT = 5,
    STRING = 6,
    LIST = 7,
    DICT = 8,
    OBJECT = 9,
};

struct PyReturn
{
    PyReturnType type_;

    union ValueUnion{
        int64_t int_val;
        double double_val;
        bool bool_val;
        float float_val;
        char* str_val;
        std::unordered_map<std::string, PyReturn>* dict_val;
        std::vector<PyReturn>* list_val;
        PyObject* obj_val;

        ValueUnion() {}
        ~ValueUnion() {}
    } value_;

    ~PyReturn() {
        switch (type_) {
            case PyReturnType::STRING:
                if (value_.str_val) {
                    free(value_.str_val);  
                    value_.str_val = nullptr;
                }
                break;
            case PyReturnType::LIST:
                if (value_.list_val) {
                    delete value_.list_val;
                    value_.list_val = nullptr;
                }
                break;
            case PyReturnType::DICT:
                if (value_.dict_val) {
                    delete value_.dict_val;
                    value_.dict_val = nullptr;
                }
                break;
            case PyReturnType::OBJECT:
                if (value_.obj_val) {
                    Py_DECREF(value_.obj_val);  
                    value_.obj_val = nullptr;
                }
                break;
            default:
                break;
        }
    }

    PyReturn() : type_(PyReturnType::NONE) {}
    explicit PyReturn(int64_t val) : type_(PyReturnType::INT) { value_.int_val = val; }
    explicit PyReturn(double val) : type_(PyReturnType::DOUBLE) { value_.double_val = val; }
    explicit PyReturn(bool val) : type_(PyReturnType::BOOL) { value_.bool_val = val; }
    explicit PyReturn(float val) : type_(PyReturnType::FLOAT) { value_.float_val = val; }
    explicit PyReturn(char* val) : type_(PyReturnType::STRING) { value_.str_val = val; }
    explicit PyReturn(std::unordered_map<std::string, PyReturn>* val) : type_(PyReturnType::DICT) { value_.dict_val = val; }
    explicit PyReturn(std::vector<PyReturn>* val) : type_(PyReturnType::LIST) { value_.list_val = val; }
    explicit PyReturn(PyObject* val) : type_(PyReturnType::OBJECT) { value_.obj_val = val; }
};

class CPython 
{
public:
    static CPython& getInstance() {
        static CPython cp;
        return cp;
    }

    PyReturn call(const std::string& module, const std::string& method, ...) {
        va_list args;
        va_start(args, method);  

        try {
            if (!Py_IsInitialized()) {
                throw std::runtime_error("Python interpreter not initialized");
            }

            PyGILState_STATE gilState = PyGILState_Ensure();

            PyObject* pyModule = getOrLoadModule(module);
            if (!pyModule) {
                PyGILState_Release(gilState);
                throw std::runtime_error("Failed to load module: " + module);
            }

            PyObject* pyFunc = PyObject_GetAttrString(pyModule, method.c_str());
            if (!pyFunc) {
                PyGILState_Release(gilState);
                throw std::runtime_error("Function " + method + " not found in module " + module);
            }

            int argCount = va_arg(args, int);  
            PyObject* pyArgs = PyTuple_New(argCount);  
            if (!pyArgs) {
                Py_DECREF(pyFunc);
                PyGILState_Release(gilState);
                throw std::runtime_error("Failed to create Python argument tuple");
            }

            bool argsValid = true;
            for (int i = 0; i < argCount; ++i) {
                void* argVal = va_arg(args, void*);  
                PyObject* pyArg = nullptr;

                if (i == 0) {  
                    pyArg = PyLong_FromLongLong(*reinterpret_cast<int64_t*>(argVal));
                } else if (i == 1) {  
                    pyArg = PyFloat_FromDouble(*reinterpret_cast<double*>(argVal));
                } else if (i == 2) {  
                    pyArg = PyBool_FromLong(*reinterpret_cast<bool*>(argVal) ? 1 : 0);
                } else if (i == 3) {  
                    pyArg = PyFloat_FromDouble(*reinterpret_cast<float*>(argVal));
                } else if (i == 4) {  
                    pyArg = PyUnicode_FromString(reinterpret_cast<const char*>(argVal));
                } else if (i == 5) {  
                    pyArg = PyUnicode_FromString(reinterpret_cast<std::string*>(argVal)->c_str());
                }

                if (!pyArg) {
                    argsValid = false;
                    break;
                }
                PyTuple_SetItem(pyArgs, i, pyArg);  
            }

            if (!argsValid) {
                Py_DECREF(pyArgs);
                Py_DECREF(pyFunc);
                PyGILState_Release(gilState);
                throw std::runtime_error("Failed to convert C++ argument to Python type");
            }

            PyObject* pyResult = PyObject_CallObject(pyFunc, pyArgs);
            if (!pyResult) {
                PyErr_Print();  
                Py_DECREF(pyArgs);
                Py_DECREF(pyFunc);
                PyGILState_Release(gilState);
                throw std::runtime_error("Python function " + method + " execution failed");
            }

            PyReturn result = convertPyObjToReturn(pyResult);

            Py_DECREF(pyResult);  
            Py_DECREF(pyArgs);    
            Py_DECREF(pyFunc);    
            PyGILState_Release(gilState);  

            va_end(args);

            return result;
        } catch (...) {
            va_end(args);
            throw;  
        }
    }

private:
    CPython(const CPython&) = delete;
    CPython& operator=(const CPython&) = delete;

    CPython() {
        Py_Initialize();
        if (!Py_IsInitialized()) {
            throw std::runtime_error("Python Initialization failed");
        }

        std::string module_path = Config::getInstance().getValue("Python_Module_Path");
        if (module_path.empty()) {
            Py_Finalize();
            throw std::runtime_error("Python_Module_Path is not configured");
        }
        
        if (!addModulePath(module_path)) {
            Py_Finalize();
            throw std::runtime_error("Failed to add Python module path: " + module_path);
        }

        PyEval_InitThreads();
        PyThreadState_Swap(nullptr);  // 释放GIL，允许其他线程使用
    }

    ~CPython() {
        if (Py_IsInitialized()) {
            for (auto& [modName, pyMod] : m_moduleCache) {
                Py_DECREF(pyMod);
            }
            m_moduleCache.clear();
            Py_Finalize();
        }
    }

    /**
     * @brief 添加模块路径到sys.path
     */
    bool addModulePath(const std::string& path) {
        PyObject* sysModule = PyImport_ImportModule("sys");
        if (!sysModule) {
            PyErr_Print();
            return false;
        }

        PyObject* sysPath = PyObject_GetAttrString(sysModule, "path");
        if (!sysPath) {
            PyErr_Print();
            Py_DECREF(sysModule);
            return false;
        }

        PyObject* pyPath = PyUnicode_FromString(path.c_str());
        if (!pyPath) {
            PyErr_Print();
            Py_DECREF(sysPath);
            Py_DECREF(sysModule);
            return false;
        }

        int contains = PySequence_Contains(sysPath, pyPath);
        if (contains == -1) {
            PyErr_Print();
            Py_DECREF(pyPath);
            Py_DECREF(sysPath);
            Py_DECREF(sysModule);
            return false;
        }

        if (contains == 0) {
            if (PyList_Append(sysPath, pyPath) != 0) {
                PyErr_Print();
                Py_DECREF(pyPath);
                Py_DECREF(sysPath);
                Py_DECREF(sysModule);
                return false;
            }
        }

        Py_DECREF(sysPath);
        Py_DECREF(sysModule);
        Py_DECREF(pyPath);
        return true;
    }

    /**
     * @brief 查找或加载Python模块（缓存优先）
     */
    PyObject* getOrLoadModule(const std::string& moduleName) {
        auto iter = m_moduleCache.find(moduleName);
        if (iter != m_moduleCache.end()) {
            return iter->second;  
        }

        PyObject* pyModule = PyImport_ImportModule(moduleName.c_str());
        if (!pyModule) {
            PyErr_Print();
            return nullptr;
        }

        m_moduleCache[moduleName] = pyModule;
        return pyModule;
    }

    /**
     * @brief 将Python对象转换为C++ PyReturn结构
    */
    PyReturn convertPyObjToReturn(PyObject* pyObj) {
        if (pyObj == Py_None) {
            return PyReturn();  
        } else if (PyLong_Check(pyObj)) {
            int64_t val = PyLong_AsLongLong(pyObj);
            if (val == -1 && PyErr_Occurred()) {
                throw std::runtime_error("Failed to convert Python int to C++ int64_t");
            }

            return PyReturn(val);
        } else if (PyFloat_Check(pyObj)) {
            double val = PyFloat_AsDouble(pyObj);
            if (val == -1.0 && PyErr_Occurred()) {
                throw std::runtime_error("Failed to convert Python float to C++ double");
            }

            return PyReturn(val);
        } else if (PyBool_Check(pyObj)) {
            bool val = (PyLong_AsLong(pyObj) == 1);
            return PyReturn(val);
        } else if (PyUnicode_Check(pyObj)) {
            const char* utf8Str = PyUnicode_AsUTF8(pyObj);
            if (!utf8Str) {
                throw std::runtime_error("Failed to convert Python string to UTF-8");
            }
            char* strVal = static_cast<char*>(malloc(strlen(utf8Str) + 1));
            strcpy(strVal, utf8Str);

            return PyReturn(strVal);
        } else if (PyList_Check(pyObj)) {
            auto listVal = new std::vector<PyReturn>();
            Py_ssize_t listSize = PyList_Size(pyObj);
            
            for (Py_ssize_t i = 0; i < listSize; ++i) {
                PyObject* item = PyList_GetItem(pyObj, i);
                if (!item) {
                    delete listVal;
                    throw std::runtime_error("Failed to get item from Python list");
                }
                Py_INCREF(item); 
                listVal->push_back(convertPyObjToReturn(item));
                Py_DECREF(item);
            }

            return PyReturn(listVal);
        } else if (PyDict_Check(pyObj)) {
            auto dictVal = new std::unordered_map<std::string, PyReturn>();
            PyObject *key, *value;
            Py_ssize_t pos = 0;

            while (PyDict_Next(pyObj, &pos, &key, &value)) {
                if (!PyUnicode_Check(key)) {
                    delete dictVal;
                    throw std::runtime_error("Python dict key is not string type");
                }
                const char* keyStr = PyUnicode_AsUTF8(key);
                Py_INCREF(value);
                (*dictVal)[keyStr] = convertPyObjToReturn(value);
                Py_DECREF(value);
            }

            return PyReturn(dictVal);
        } else {
            Py_INCREF(pyObj); 
            return PyReturn(pyObj);
        }
    }

private:
    std::unordered_map<std::string, PyObject*> m_moduleCache;
};
