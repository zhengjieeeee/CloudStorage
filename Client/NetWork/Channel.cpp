#include "Channel.h"
#include "../../Util/MemoryPool/MemoryPool.h"

#include <string>

static int serverPort = 8080;
static std::string serverIp = "";
    

Channel::Channel(ChannelType type, MessageQueue* recvQueue, std::condition_variable* recvCV) 
    : type_(type)
    , recvQueue_(recvQueue)
    , recvCv_(recvCV)
{
    state_ = ConnectionStatus::CONNTECTING;
    if (WSAStartup(MAKEWORD(2,2), &wsaData_) != 0) {
        state_ = ConnectionStatus::ERROR_;
        return;
    }
    fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd_ == INVALID_SOCKET) {
        state_ = ConnectionStatus::ERROR_;
        WSACleanup();
        return;
    }
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(serverPort);
    serverAddr_.sin_addr.S_un.S_addr = inet_addr(serverIp.c_str());
    if (connect(fd_, (sockaddr*)&serverAddr_, sizeof(serverAddr_)) == SOCKET_ERROR) {
        state_ = ConnectionStatus::ERROR_;
        closesocket(fd_);
        WSACleanup();
        return;
    }
    state_ = ConnectionStatus::CONNECTED;

    sendQueue_ = new MessageQueue();
}

Channel::~Channel(){
    if (state_ == ConnectionStatus::CONNECTED) {
        closesocket(fd_);
        sendCv_.notify_one();
    }
    delete sendQueue_;
    WSACleanup();
}

void Channel::send(char* data, size_t size){
    sendQueue_ -> push(data, size);
    sendCv_.notify_one();
}

void Channel::send(){
    while (state_ == ConnectionStatus::CONNECTED){
        std::unique_lock<std::mutex> lock(sendMutex_);
        while (sendQueue_ -> empty()){
            sendCv_.wait(lock);
        }

        if (state_ == ConnectionStatus::CLOSE || state_ == ConnectionStatus::ERROR_){
            break;
        }

        auto msg = sendQueue_ -> pop();
        size_t sendBytes = ::send(fd_, msg.data_, msg.size_, 0);
        if (sendBytes < 0){
            state_ = ConnectionStatus::ERROR_;
            MemoryPool::deallocate(msg.data_, msg.size_);
            break;
        }else{
            MemoryPool::deallocate(msg.data_, msg.size_);
        }
    }
}

void Channel::recv(){
    char* sizeBuffer = new char[4];
    bool flag = false;
    char* dataBuffer = nullptr;
    size_t totalSize = 0;
    size_t currentSize = 0;

    while (state_ == ConnectionStatus::CONNECTED){
        if (!flag){
            // 接收4字节数据头，表示数据长度
            size_t recvBytes = ::recv(fd_, sizeBuffer, 4, 0);
            if (recvBytes == -1){
                state_ = ConnectionStatus::ERROR_;
                break;
            }else if (recvBytes == 0){
                // 连接关闭
                state_ = ConnectionStatus::CLOSE;
                break;
            }else if (recvBytes == 4){
                uint32_t netDataLen = *reinterpret_cast<uint32_t*>(sizeBuffer);
                totalSize = static_cast<size_t>(ntohl(netDataLen));
                dataBuffer = static_cast<char*>(MemoryPool::allocate(totalSize));
                flag = true;
            }
        }else{
            // 根据数据长度申请内存并接收数据
            size_t recvBytes = ::recv(fd_, dataBuffer + currentSize, sizeof(dataBuffer) - currentSize, 0);
            if (recvBytes == -1){
                state_ = ConnectionStatus::ERROR_;
                break;
            }else if (recvBytes == 0){
                // 连接关闭
                state_ = ConnectionStatus::CLOSE;
                break;
            }else if (recvBytes > 0){
                currentSize += recvBytes;
                if (currentSize < totalSize){

                }else if (currentSize == totalSize){
                    recvQueue_ -> push(dataBuffer, totalSize);
                    recvCv_ -> notify_one();
                    
                    currentSize = 0;
                    totalSize = 0;
                    flag = false;
                    dataBuffer = nullptr;
                }else{
                    // 可能跟了下一个文件的数据
                }
            }
        }
    }
}
