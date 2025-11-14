#include "Channel.h"
#include "../../Util/MemoryPool/MemoryPool.h"

#include <string>

static std::string serverIp = "8.137.39.201";
static int serverPort_ = 8000;

Channel::Channel(ChannelType type) : type_(type)
{
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
    serverAddr_.sin_addr.S_un.S_addr = inet_addr(serverIp.c_str());
    if (connect(fd_, (sockaddr*)&serverAddr_, sizeof(serverAddr_)) == SOCKET_ERROR) {
        status_ = Status::ERROR_;
        closesocket(fd_);
        WSACleanup();
        return;
    }
    status_ = Status::CONNECTED;
}

Channel::~Channel(){
    if (status_ == Status::CONNECTED) {
        closesocket(fd_);
    }
    WSACleanup();
}

void Channel::notify(char* data, size_t size){
    sendQueue_.push(data, size);
    sendCv_.notify_one();
}

void Channel::send(){
    while (status_ == Status::CONNECTED){
        std::unique_lock<std::mutex> lock(sendMutex_);
        while (sendQueue_.empty()){
            sendCv_.wait(lock);
        }

        auto msg = sendQueue_.pop();
        size_t sendBytes = ::send(fd_, msg.data_, msg.size_, 0);
        if (sendBytes < 0){
            status_ = Status::ERROR_;
            MemoryPool::deallocate(msg.data_, msg.size_);
            break;
        }else{
            MemoryPool::deallocate(msg.data_, msg.size_);
        }
    }
}

void Channel::recv(){
    char* sizeBuffer = new char[4];
    bool is_recv_data = false;
    char* dataBuffer = nullptr;
    size_t totalSize = 0;
    size_t currentSize = 0;

    while (status_ == Status::CONNECTED){
        if (!is_recv_data){
            size_t recvBytes = ::recv(fd_, sizeBuffer, 4, 0);
            if (recvBytes == -1){
                status_ = Status::ERROR_;
                break;
            }else if (recvBytes == 0){
                // 连接关闭
                status_ = Status::CLOSE;
                break;
            }else if (recvBytes == 4){
                uint32_t netDataLen = *reinterpret_cast<uint32_t*>(sizeBuffer);
                totalSize = static_cast<size_t>(ntohl(netDataLen));
                dataBuffer = static_cast<char*>(MemoryPool::allocate(totalSize));
                is_recv_data = true;
            }
        }else{
            size_t recvBytes = ::recv(fd_, dataBuffer + currentSize, sizeof(dataBuffer) - currentSize, 0);
            if (recvBytes == -1){
                status_ = Status::ERROR_;
                break;
            }else if (recvBytes == 0){
                // 连接关闭
                status_ = Status::CLOSE;
                break;
            }else if (recvBytes > 0){
                currentSize += recvBytes;
                if (currentSize < totalSize){

                }else if (currentSize == totalSize){
                    recvQueue_.push(dataBuffer, totalSize);
                    recvCv_.notify_one();

                    currentSize = 0;
                    totalSize = 0;
                    is_recv_data = false;
                    dataBuffer = nullptr;
                }else{
                    // 可能跟了下一个文件的数据
                }
            }
        }
    }
}

void Channel::onRecv(){
    while (status_ == Status::CONNECTED || !recvQueue_.empty()){
        std::unique_lock<std::mutex> lock(recvMutex_);
        while (recvQueue_.empty()){
            recvCv_.wait(lock);
        }

        auto msg = recvQueue_.pop();
        if (recvCallBack_){
            recvCallBack_(msg.data_, msg.size_);
        }else{
            status_ = Status::ERROR_;
            break;
        }
    }
}