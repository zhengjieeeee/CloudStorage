#pragma once

#include <ctime>
#include <string>
#include <thread>
#include <functional>
#include <chrono>
#include <mutex>
#include <condition_variable>

class Time
{
public: 
    Time(int timeout, std::function<void()> cb) 
        : timeout_(timeout)
        , cb_(cb)
        , thread_(nullptr)
    { 
    }

    ~Time(){
        exit();
    }

    static std::string getTimeStr(){
        std::time_t now = std::time(nullptr);
        std::tm* localtime = std::localtime(&now);
        char timestr[20];
        std::strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime);
        return std::string(timestr);
    }

    static int difftime(time_t start, time_t end){
        return static_cast<int>(start - end);
    }

    void setCallbak(std::function<void()> cb){
        cb_ = cb;
    }

    void start(){
        thread_ = new std::thread(&Time::Countdown, this);
    }

    void exit(){
        isRunning_ = false;
        cv_.notify_one();
        if (thread_ && thread_->joinable()){
            thread_->join();
            delete thread_;
            thread_ = nullptr;
        }
    }

private:
    void Countdown(){
        while (isRunning_){
            std::unique_lock<std::mutex> lock(mutex_);
            auto status = cv_.wait_for(lock, std::chrono::seconds(timeout_), 
                [this]() { return !isRunning_; });
            if (!isRunning_){
                break;
            }
            cb_();
        }
    }

    std::mutex mutex_;
    std::condition_variable cv_;

    bool isRunning_ = true;
    int timeout_;
    std::function<void()> cb_;
    std::thread* thread_;
};