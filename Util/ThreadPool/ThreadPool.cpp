#include "ThreadPool.h"

#include <functional>

ThreadPool::ThreadPool(size_t defaultNumThreads)
{
    timer_ -> setCallbak(std::bind(&ThreadPool::flush, this));
    for (size_t i = 0; i < defaultNumThreads; ++i){
        Thread* thread = new Thread("ThreadPool-Worker-" + std::to_string(i));
        threads_.push_back(thread);
    }
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
            return;
        }
    }

    // 没有空闲线程
    threads_.emplace_back(new Thread("ThreadPool-Worker-" + std::to_string(threads_.size())));
    threads_.back() -> start(task);
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