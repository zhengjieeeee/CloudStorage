#pragma once

#include <memory>
#include <deque>
#include <mutex>

struct  MessageInfo
{
    char* data_ = nullptr;
    size_t size_ = 0;
};

class MessageQueue
{
public:

    
    MessageQueue();
    ~MessageQueue();

    void push(char* data, size_t size);
    MessageInfo pop();

    bool empty() { return deque_.empty(); }
    
private:
    std::mutex mutex_;
    std::deque<MessageInfo> deque_;
};