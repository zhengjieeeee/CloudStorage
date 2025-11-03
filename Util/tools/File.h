#pragma once

#include <algorithm>
#include <cstddef>
#include <fstream>
#include <ios>
#include <string>
#include <filesystem>
#include <vector>
#include <memory>

#include "../MemoryPool/MemoryPool.h"

namespace fs = std::filesystem;

class File
{
public:
    static bool exists(const std::string& path){
        return fs::exists(fs::path(path));
    }

    // 读取文件,返回数据指针
    static std::shared_ptr<char> read(const std::string& path){
        if (!exists(path)) return nullptr;
        
        std::ifstream file(path, std::ios::in | std::ios::binary);
        if(!file.is_open()) return nullptr;

        //获取文件大小
        file.seekg(0, std::ios::end);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        const size_t filesize = static_cast<size_t>(size);
        if (filesize == 0){
            // 空文件返回，data.get()是nullptr
            std::shared_ptr<char> data(0);
            file.close();
            return data;
        }

        char* raw = static_cast<char*>(MemoryPool::allocate(filesize));

        std::shared_ptr<char> data(raw, [filesize](char* ptr){
            if (ptr == nullptr) return;
            MemoryPool::deallocate(ptr, filesize);
        });

        file.read(data.get(), filesize);
        if (!file.good()){
            file.close();
            return nullptr;
        }

        file.close();
        return data;
    }

    // 存储文件
    static int write(char* data, const size_t size, std::string& path){
        if (fs::exists(path)) return 0; //表示文件存在，返回给用户是否覆盖
        if (!data || size == 0 || path.empty()) return -1;

        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) return -2;

        file.write(data, size);
        if (!file.good()) return -3;

        file.flush();
        file.close();

        MemoryPool::deallocate(data, size);
        return 1;
    }

    // 替换写入只能在write调用后调用
    static int replaceWrite(char* data, const size_t size, const std::string& path){
        if (!data || size == 0 || path.empty()) return -1;

        std::ofstream file(path, std::ios::binary);
        if (!file.is_open()) return -2;

        file.write(data, size);
        if (!file.good()) return -3;

        file.flush();
        file.close();

        MemoryPool::deallocate(data, size);
        return 1;
    }

    // 修改文件
    static int modify(char* data,const std::string& path, const size_t size, const size_t offset){
        if (!fs::exists(path)) return 0;
        if (!data || size == 0 || path.empty()) return -1;

        size_t fileSize = fs::file_size(path);
        if (offset > fileSize) return -2;

        std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open()) return -3; 

        file.seekp(offset);
        if (!file) return -4;

        file.write(data, size);
        if (!file) return -5;

        file.flush();
        return 0;
    }
};