#pragma once

#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "Thread.h"
#include "../../Util/tools/Time.h"

class ThreadPool
{
public:
    ThreadPool(size_t defaultNumThreads);
    ~ThreadPool();

    void enqueueTask(std::function<void()> task);
    void clear();

private:
    void flush();

private:
    std::vector<Thread*> threads_;
    std::queue<std::function<void()>> taskQueue_;
    std::mutex queueMutex_;
    Time* timer_;
};