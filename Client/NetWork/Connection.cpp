#include "Connection.h"

Connection::Connection(){
    recvCv_ = new std::condition_variable();
    Channel* mainChannel = new Channel(ChannelType::Main, recvQueue_, recvCv_);
    channels_.emplace(ChannelType::Main, mainChannel);

    recvQueue_ = new MessageQueue();

    running_ = true;
    threads_ -> enqueueTask(std::bind(&Connection::onRecv, this));

    timer_ = new Time(60, std::bind(&Connection::flush, this));
    timer_->start();
}

Connection::~Connection(){
    for (auto& pair : channels_){
        delete pair.second;
    }

    running_ = false;
    recvCv_ -> notify_one();
    
    delete recvCv_;
    delete timer_;
    delete recvQueue_;
    delete threads_;
}

void Connection::send(char* data, size_t size, ChannelType type){
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = channels_.find(type);
    if (it == channels_.end()){
        Channel* newChannel = new Channel(type, recvQueue_, recvCv_);
        channels_.emplace(type, newChannel);
        newChannel->send(data, size);
    }else{
        it->second->send(data, size);
    }

}   

void Connection::flush() {
    if (channels_.size() <= 1) {
        return; 
    }

    std::lock_guard<std::mutex> lock(mutex_); 
    time_t now = std::time(nullptr);
    const int timeout = 2 * 60; 

    auto it = channels_.begin();
    while (it != channels_.end()) {
        ChannelType type = it->first;
        Channel* channel = it->second;

        if (type == ChannelType::Main) {
            ++it;
            continue;
        }

        if (now - channel->getLastActiveTime() > timeout) {
            delete channel;
            it = channels_.erase(it);
        } else {
            ++it;
        }
    }
}

void Connection::onRecv(){
    while (running_){
        std::unique_lock<std::mutex> lock(mutex_);
        while (recvQueue_ -> empty() && running_){
            recvCv_ -> wait(lock);
        }

        if (!running_) break;

        auto msg = recvQueue_ -> pop();
        lock.unlock();

        cb_(msg);
    }
}