#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "../../Util/tools/Time.h"
#include "../../Util/tools/MessageType.h"
#include "../../Util/ThreadPool/ThreadPool.h"
#include "MessageQueue.h"
#include "Channel.h"

class Connection
{
public:
    static Connection& getInstance(){
        static Connection instance;
        return instance;
    }

    // 使用内存池优化
    void send(char* data, size_t size, ChannelType type);
    void setRecvCallback() { }
private:
    Connection();
    ~Connection();
    Connection(const Connection&) = delete;
    Connection(Connection&&) = delete;
    Connection& operator= (const Connection&) = delete;

    void flush();
    void onRecv();
    
private:
    Time*                                       timer_;
    ThreadPool*                                 threads_;
    std::unordered_map<ChannelType, Channel*>   channels_;

    MessageQueue*                               recvQueue_;
    std::condition_variable*                    recvCv_;
    std::mutex                                  mutex_;
    std::atomic<bool>                           running_;

    std::function<void(MessageInfo)>            cb_;
};