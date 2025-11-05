#pragma once

#include <python3.12/Python.h>
#include <string>
#include <unordered_map>

class CPython 
{
public:
    static CPython& getInstance(){
        static CPython cp;
        return cp;
    }

    
    void call(const std::string& module, const std::string& method, ...);
private:
    CPython();
    CPython(const CPython&) = delete;

    struct objectDes{
        PyObject* object_;
        int parameteNum_;
    };

    std::unordered_map<std::string, objectDes> object_map_;
};