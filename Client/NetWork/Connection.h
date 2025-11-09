#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include "../../Util/MemoryPool/MemoryPool.h"
#include "../../Util/tools/MessageType.h"
#include "MessageQueue.h"

#pragma comment(lib, "ws2_32.lib")

// 连接状态
enum class Status{
    CLOSE,
    CONNTECTING,
    CONNECTED,
    ERROR_
};

class Connection
{
public:
    using RecvCallBack = std::function<void(const char*)>;

    static Connection& getInstance(){
        static Connection instance;
        return instance;
    }

    // 使用内存池优化
    bool send(char* data, size_t size);

    // 接收回调
    void setRecv(RecvCallBack &cb);

private:
    Connection();
    ~Connection();
    Connection(const Connection&) = delete;
    Connection(Connection&&) = delete;
    Connection& operator= (const Connection&) = delete;

    void sendInThread();
    void recvInThread();

    void OnRecv();

private:
    std::string serverIp_;
    int serverPort_;

    Status status_;

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
};