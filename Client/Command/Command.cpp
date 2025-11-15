#include "Command.h"

Command::Command(){}
Command::~Command(){}

Command& Command::getInstance(){
        static Command instance;
        return instance;
    }

void Command::parse(std::string& command){
    if (!refreshUI_){
        return;
    }

    if (command.empty()){
        auto it = commandMap_.find("");
        if(it != commandMap_.end()){
            it -> second.func_("");
        }
    }

    trim(command);
    size_t spacePos = command.find(' ');
    if (spacePos == std::string::npos){
        //refreshUI_();
        return;
    }
    
    std::string cmd = command.substr(0, spacePos);
    std::string args = command.substr(spacePos + 1);
    auto it = commandMap_.find(cmd);

    if (it != commandMap_.end()){
        it -> second.func_(args);
    }else{
        refreshUI_(command);
    }
}

 void Command::trim(std::string& str) {
    size_t startPos = str.find_first_not_of(" ");
    size_t endPos = str.find_last_not_of(" ");

    if (startPos == std::string::npos) {
        str.clear(); 
        return;
    }

    std::string noSpaceStr = str.substr(startPos, endPos - startPos + 1);
    str.swap(noSpaceStr);
}

void Command::splice(std::string& str, CommandType type){

}   