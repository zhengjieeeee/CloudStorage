#include "ThreadPool.h"

#include <functional>

ThreadPool::ThreadPool(size_t defaultNumThreads, Time* timer)
{
    timer_ = timer;
    timer_ -> setCallbak(std::bind(&ThreadPool::flush, this));
    for (size_t i = 0; i < defaultNumThreads; ++i){
        Thread* thread = new Thread("ThreadPool-Worker-" + std::to_string(i));
        threads_.push_back(thread);
    }
    timer_ -> start();
}

ThreadPool::~ThreadPool(){
    if (timer_) delete timer_;
    for (auto thread : threads_){
        thread -> destroy();
    }
}

void ThreadPool::enqueueTask(std::function<void()> task){
    std::lock_guard<std::mutex> lock(queueMutex_);
    for (auto thread : threads_){
        if (thread -> getState() == ThreadState::SLEEPING){
            thread -> start(task);
        }
    }
}

void ThreadPool::clear(){
    std::lock_guard<std::mutex> lock(queueMutex_);
    for (auto thread : threads_){
        thread -> destroy();
    }
}

void ThreadPool::flush(){
    if (timer_ == nullptr) return;
    std::lock_guard<std::mutex> lock(queueMutex_);
    
}