#include <iostream>
#include <string>
#include <vector>

#include "../../tools/File.h"

int main(){
    const std::string path = "file_test.txt";

    if (File::exists(path)){
        std::cout << "file exists" << std::endl;
    }

    std::vector<char> data;
    if (File::read(data, path)){
        std::cout << "read successfully : " << std::string(data.begin(), data.end()) << std::endl;
    }

    std::vector<char> writedata;
    writedata.push_back('1');
    writedata.push_back('1');

    int ret = File::write(writedata, path);
    std::cout << "write code : " << ret << " context : " << std::string(data.begin(), data.end()) << std::endl;
    


    return 0;
}