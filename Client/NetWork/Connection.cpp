#include "Connection.h"

Connection::Connection(){
    serverIp_ = "8.137.39.201";
    serverPort_ = 8000;

    status_ = Status::CONNTECTING;

    if (WSAStartup(MAKEWORD(2,2), &wsaData_) != 0) {
        status_ = Status::ERROR_;
        return;
    }

    fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd_ == INVALID_SOCKET) {
        status_ = Status::ERROR_;
        WSACleanup();
        return;
    }

    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(serverPort_);
    serverAddr_.sin_addr.S_un.S_addr = inet_addr(serverIp_.c_str());

    if (connect(fd_, (sockaddr*)&serverAddr_, sizeof(serverAddr_)) == SOCKET_ERROR) {
        status_ = Status::ERROR_;
        closesocket(fd_);
        WSACleanup();
        return;
    }
    status_ = Status::CONNECTED;
}

Connection::~Connection(){
    if (status_ == Status::CONNECTED) {
        closesocket(fd_);
    }
    WSACleanup();
}

bool Connection::send(char* data, size_t size){
    if (status_ != Status::CONNECTED) {
        return false;
    }

    sendQueue_.push(data, size);
    sendCv_.notify_one();
}

void Connection::sendInThread(){
    while (status_ == Status::CONNECTED){
        std::unique_lock<std::mutex> mutex(sendMutex_);

        while (!sendQueue_.empty()){
            sendCv_.wait(mutex);
        }

        MessageInfo info = sendQueue_.pop();
        size_t sendBytes = ::send(fd_, info.data_, info.size_, 0);
        if (sendBytes > 0){

        }else{

        }
    }
}

void Connection::recvInThread(){
    char* sizeBuffer = new char[4];
    bool is_recv_data = false;
    char* dataBuffer = nullptr;
    size_t currentSize = 0;

    while (status_ == Status::CONNECTED){
        if (!is_recv_data){
            // 还没接收到数据
            int recvBytes = ::recv(fd_, sizeBuffer, 4, 0);
            if (recvBytes == -1){
                status_ = Status::ERROR_;
                break;
            }else if (recvBytes == 0){
                // 连接关闭
                status_ = Status::CLOSE;
                break;
            }else if (recvBytes > 0){
                uint32_t netDataLen = *reinterpret_cast<uint32_t*>(sizeBuffer);
                size_t dataBytes = static_cast<size_t>(ntohl(netDataLen));
                dataBuffer = static_cast<char*>(MemoryPool::allocate(dataBytes));
                is_recv_data = true;
            }
        }else{
            size_t recvBytes = ::recv(fd_, dataBuffer, sizeof(dataBuffer), 0);
            if (recvBytes == -1){
                status_ = Status::ERROR_;
                break;
            }else if (recvBytes == 0){
                // 连接关闭
                status_ = Status::CLOSE;
                break;
            }else if (recvBytes > 0){
                currentSize += recvBytes;
                if (currentSize == sizeof(dataBuffer)){
                    // 接收完成
                    recvQueue_.push(dataBuffer, currentSize);
                    recvCv_.notify_one();

                    // 重置状态
                    is_recv_data = false;
                    currentSize = 0;
                    dataBuffer = nullptr;
                }
            }
        }
    }
}

void Connection::OnRecv(){
    
}