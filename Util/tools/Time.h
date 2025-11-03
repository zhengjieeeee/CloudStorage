#pragma once

#include <ctime>
#include <string>


class Time
{
public: 
    static std::string getTime(){
        std::time_t now = std::time(nullptr);
        std::tm* localtime = std::localtime(&now);
        char timestr[20];
        std::strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime);
        return std::string(timestr);
    }
};