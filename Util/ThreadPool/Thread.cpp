#include "Thread.h"

Thread::Thread(const std::string& name)
    : name_(name),
      state_(ThreadState::STOPPED),
      thread_(nullptr)
{}

Thread::~Thread(){
    destroy();

}

void Thread::start(std::function<void()> task){
    if (!thread_ && state_ == ThreadState::STOPPED){
        task_ = task;
        state_ = ThreadState::RUNNING;
        thread_ = new std::thread(&Thread::run, this);
        pid_ = thread_->get_id();
        state_ = ThreadState::RUNNING;
    }else{
        if (state_ == ThreadState::SLEEPING){
            task_ = task;
            wakeUp();
        }
    }
}

void Thread::run(){
    while (state_ == ThreadState::RUNNING){
        if (task_){
            task_();
        }
        std::unique_lock<std::mutex> lock(mutex_);
        state_ = ThreadState::SLEEPING;
        while (state_ == ThreadState::SLEEPING){
            cv_.wait(lock);
        }
    }
}

void Thread::join(){
    thread_ -> join();
}

void Thread::detach(){
    thread_ -> detach();
}

void Thread::wakeUp(){
    state_ = ThreadState::RUNNING;
    cv_.notify_one();
}

void Thread::destroy(){
    state_ = ThreadState::STOPPED;
    cv_.notify_one();
    join();
}

ThreadState Thread::getState(){
    return state_;
}

std::thread::id Thread::getPid(){
    return pid_;
}

std::string Thread::getName(){
    return name_;
}
