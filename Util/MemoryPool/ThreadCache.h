#pragma once

#include "Common.h"

class ThreadCache
{
public:
    static ThreadCache* getInstance(){
        static thread_local ThreadCache instance;
        return &instance;
    }

    void* allocate(size_t size);
    void deallocate(void* ptr, size_t size);
    
private:
    ThreadCache(){
        freelist_.fill(nullptr);
        freelistSize_.fill(0);
    }

    void fetchFromCentralCache(size_t index);

    void returnToCentralCache(void* start, size_t size);

    bool shouldReturnToCentralCache(size_t index);
    
private:
    std::array<void*, FREE_LIST_SIZE> freelist_;
    std::array<size_t, FREE_LIST_SIZE> freelistSize_;
};