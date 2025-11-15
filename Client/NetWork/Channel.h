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
enum class ConnectionStatus{
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

    Channel(ChannelType type, MessageQueue* recvQueue, std::condition_variable* recvCV);
    ~Channel();

    void send(char* data, size_t size);

    void setRecv(RecvCallBack &cb){
        recvCallBack_ = cb;
    }

    std::time_t getLastActiveTime(){ return lastActiveTime_; }

private:
    void send();
    void recv();

private:
    ConnectionStatus        state_;
    ChannelType             type_;

    WSADATA                 wsaData_;
    SOCKET                  fd_;
    sockaddr_in             serverAddr_;

    RecvCallBack            recvCallBack_;

    MessageQueue*           sendQueue_;
    MessageQueue*           recvQueue_;

    std::condition_variable sendCv_;
    std::mutex              sendMutex_;
    std::condition_variable* recvCv_;

    std::time_t             lastActiveTime_;
};