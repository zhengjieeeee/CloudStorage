#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "MessageQueue.h"

#pragma comment(lib, "ws2_32.lib")
// 连接状态
enum class Status{
    CLOSE,
    CONNTECTING,
    CONNECTED,
    ERROR_
};

enum class ChannelType{
    Main,
    Pull,
    Push,
    FileOpt,
    AIChat
};

class Channel
{
public:
    using RecvCallBack = std::function<void(char*, size_t)>;

    Channel(ChannelType type, bool hasTimer);
    Channel(ChannelType type);
    ~Channel();

    void notify(char* data, size_t size);

    void setRecv(RecvCallBack &cb){
        recvCallBack_ = cb;
    }

private:
    void send();
    void recv();
    void onRecv();

private:
    Status status_;
    ChannelType type_;

    WSADATA wsaData_;
    SOCKET fd_;
    sockaddr_in serverAddr_;

    RecvCallBack recvCallBack_;

    MessageQueue sendQueue_;
    MessageQueue recvQueue_;

    std::condition_variable sendCv_;
    std::condition_variable recvCv_;
    std::mutex sendMutex_;
    std::mutex recvMutex_;

    bool hasTimer_;
    std::time_t                 lastActiveTime_;
};