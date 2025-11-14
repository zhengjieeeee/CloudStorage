#pragma once

#include <thread>
#include <string>
#include <functional>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <ctime>

enum class ThreadState
{
    RUNNING,
    SLEEPING,
    STOPPED
};

class Thread
{
public:
    using Task = std::function<void()>;

    Thread(const std::string& name);
    ~Thread();

    void start(std::function<void()> task);
    void join();
    void detach();
    void wakeUp();
    void destroy();
    
    ThreadState getState();
    std::thread::id getPid();
    std::string getName();
    std::time_t getLastActiveTime();
    
private:
    void run();

private:
    Thread(const Thread&) = delete;
    Thread(Thread&&) = delete;
    Thread& operator= (const Thread&) = delete;
    Thread& operator=(Thread&&) = delete;

    std::string                 name_;
    std::thread*                thread_;
    std::atomic<ThreadState>    state_;
    Task                        task_;
    std::mutex                  mutex_;
    std::condition_variable     cv_;
    std::thread::id             pid_;
};