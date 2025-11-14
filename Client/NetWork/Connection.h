#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "../../Util/tools/MessageType.h"
#include "Channel.h"

class Connection
{
public:
    static Connection& getInstance(){
        static Connection instance;
        return instance;
    }

    // 使用内存池优化
    bool send(char* data, size_t size, ChannelType type);
private:
    Connection();
    ~Connection();
    Connection(const Connection&) = delete;
    Connection(Connection&&) = delete;
    Connection& operator= (const Connection&) = delete;

private:
   std::unordered_map<ChannelType, Channel*> channels_;
};