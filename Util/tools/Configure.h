#pragma once

#include <cstdlib>
#include <unordered_map>
#include <string>
#include <iostream>
#include <unistd.h>
#include <memory>
#include <cstdio>

class Config
{
public:
    static Config& getInstance(){
        static Config instance;
        return instance;
    }

    bool init(int argc, char** argv){
        // ./xxx -i xxx.config
        if (argc != 3){
            std::cout << "格式 : command -i <配置文件路径路径>" << std::endl;
            exit(EXIT_FAILURE);
            return false;
        }

        int o;
        std::string config_file;
        while (-1 != (o = getopt(argc, argv, "i:"))){
            switch (o){
                case 'i':
                    config_file = optarg;
                    break;
                case '?':
                    std::cout << "格式 : command -i <配置文件路径路径>" << std::endl;
                    exit(EXIT_FAILURE);
                case ':':
                    std::cout << "格式 : command -i <配置文件路径路径>" << std::endl;
                    exit(EXIT_FAILURE);
                default:
                    break;
            }
        }

        loadConfigFile(config_file);
        return true;
    }

    std::string getValue(const std::string& key){
        auto it = config_map.find(key);
        if(it == config_map.end()) return "";
        return it -> second;
    }

private:
    void loadConfigFile(const std::string& path){
        std::unique_ptr<FILE, decltype(&fclose)> fp(fopen(path.c_str(), "r"), &fclose);
        if (fp == nullptr) exit(EXIT_FAILURE);

        char buf[1024];
        while (fgets(buf, 1024, fp.get())){
            std::string read_buf(buf);
            trim(read_buf);

            if (read_buf[0] == '#' || read_buf.empty()) continue;

            //key=value
            size_t index = read_buf.find('=');
            if (index == -1) continue;
            std::string key = read_buf.substr(0, index);

            size_t endindex = read_buf.size() - index + 1;
            std::string value = read_buf.substr(index + 1, endindex);

            config_map.insert({key, value});
        }
    }

    // 去除空格
    void trim(std::string& buf) {
        size_t slow = 0;

        for (size_t fast = 0; fast < buf.size(); ++fast) {
            if (buf[fast] != ' ' && buf[fast] != '\n') {
                buf[slow++] = buf[fast]; 
            }
        }
        buf.resize(slow);
    }
    
private:
    std::unordered_map<std::string, std::string> config_map;
};