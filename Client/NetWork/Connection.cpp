#include "Connection.h"

Connection::Connection(){
    Channel* mainChannel = new Channel(ChannelType::Main);
    channels_.emplace(ChannelType::Main, mainChannel);
}

Connection::~Connection(){
    for (auto& pair : channels_){
        delete pair.second;
    }
}

bool Connection::send(char* data, size_t size, ChannelType type){
    auto it = channels_.find(type);
    if (it == channels_.end()){
        Channel* newChannel = new Channel(type);
        channels_.emplace(type, newChannel);
        it = channels_.find(type);
    }

    it->second->notify(data, size);
    return true;
}   

