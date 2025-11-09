#include "MessageQueue.h"
#include "../../Util/MemoryPool/MemoryPool.h"

MessageQueue::MessageQueue(){}

MessageQueue::~MessageQueue(){
    while (!deque_.empty()) {
        auto msg = deque_.front();
        MemoryPool::deallocate(msg.data_, msg.size_);
        deque_.pop_front();
    }
}

void MessageQueue::push(char* data, size_t size){
    MessageInfo msg;
    msg.data_ = data;
    msg.size_ = size;
    std::lock_guard<std::mutex> lock(mutex_);
    deque_.push_back(msg);
}

MessageInfo MessageQueue::pop(){
    std::lock_guard<std::mutex> lock(mutex_);
    if (deque_.empty()) {
        return MessageInfo{};
    }
    auto msg = deque_.front();
    deque_.pop_front();
    return msg;
}