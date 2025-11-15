#pragma once

#include <unordered_map>
#include <string>
#include <functional>

using CommandFunc = void(*)(const std::string& args);
using RefrshUI = std::function<void(const std::string& command)>;

struct CommandInfo
{
    size_t      argc_;  //参数个数
    CommandFunc func_; //对应函数指针
};

enum class CommandType{
    NORMAL,
    COMMAND_NOT_FOUND,
    INVALID_ARGUMENTS
};

class Command
{
public:
    Command& getInstance();

    void parse(std::string& command);

private:
    Command();
    ~Command();
    Command(const Command&) = delete;
    Command(Command&&) = delete;
    Command& operator=(const Command&) = delete;

    void trim(std::string& str);
    void splice(std::string& str, CommandType type);

private:
    RefrshUI                                     refreshUI_;
    std::unordered_map<std::string, CommandInfo> commandMap_;
};