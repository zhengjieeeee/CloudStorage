#include "../..//tools/Configure.h"

#include <iostream>

int main(int argc, char** argv){
    Config config = Config::getInstance();
    if (config.init(argc, argv)){
        std::cout << "init successfully" << std::endl;
    }

    std::string maxthread = config.getValue("maxthread");
    std::string minthread = config.getValue("minthread");
    std::string time = config.getValue("time");

    std::cout << "maxthread : " << maxthread << std::endl;
    std::cout <<maxthread.size() << std::endl;
    std::cout << "minthread : " << minthread << std::endl;
    std::cout << "time : " << time << std::endl;
    return 0;
}