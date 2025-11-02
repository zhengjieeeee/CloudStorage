#include "ThreadCache.h"
#include "CentralCache.h"
#include <cstdlib>

void* ThreadCache::allocate(size_t size){
    if (size == 0){
        size = ALIGNMENT;
    }
    if (size > MAN_BYTES){
        return malloc(size);
    }

    size_t index = SizeClass::getIndex(size);

    freelistSize_[index]--;

    if (void* ptr = freelist_[index]){
        freelist_[index] = *reinterpret_cast<void**>(ptr);
        return ptr;
    }

    return fetchFromCentralCache(index);
}

void ThreadCache::deallocate(void* ptr, size_t size){
    if (size > MAN_BYTES){
        free(ptr);
        return;
    }

    size_t index = SizeClass::getIndex(size);

    *reinterpret_cast<void**>(ptr) = freelist_[index];
    freelist_[index] = ptr;

    freelistSize_[index]++;

    if (shouldReturnToCentralCache(index)){
        returnToCentralCache(freelist_[index], size);
    }
}

void ThreadCache::shouldReturnToCentralCache(size_t index){
    size_t threshold = 64;
    return (freelistSize_[index] > threshold);
}

void* ThreadCache::fetchFromCentralCache(size_t index){
    void* start = CentralCache::getInstance().fetchRange(index);
    if (!start) return nullptr;

    void* result = start;
    freelist_[index] = *reinterpret_cast<void**>(start);

    size_t batchNum = 0;
    void* current = start;

    while (current != nullptr){
        batchNum++;
        current = *reinterpret_cast<void**>(current);
    }

    freelist_[index] += batchNum;

    return result;
}

void ThreadCache::returnToCentralCache(void* start, size_t size){
    size_t index = SizeClass::getIndex(size);
    size_t alignedSize = SizeClass::roundUp(size);

    size_t batchNum = freelistSize_[index];
    if (batchNum <= 1) return;

    size_t keepNum = std::max(batchNum / 4, size_t(1));
    size_t returnNum = batchNum - keepNum;

    char* current = static_cast<char*>(start);
    char* splitNode = current;
    for (size_t i = 0; i < keepNum - 1; ++i){
        splitNode = reinterpret_cast<char*>(*reinterpret_cast<void**>(splitNode));
        if (splitNode == nullptr) 
        {
            // 如果链表提前结束，更新实际的返回数量
            returnNum = batchNum - (i + 1);
            break;
        }
    }

    if (splitNode != nullptr) 
    {
        // 将要返回的部分和要保留的部分断开
        void* nextNode = *reinterpret_cast<void**>(splitNode);
        *reinterpret_cast<void**>(splitNode) = nullptr; // 断开连接

        // 更新ThreadCache的空闲链表
        freeList_[index] = start;

        // 更新自由链表大小
        freeListSize_[index] = keepNum;

        // 将剩余部分返回给CentralCache
        if (returnNum > 0 && nextNode != nullptr)
        {
            CentralCache::getInstance().returnRange(nextNode, returnNum * alignedSize, index);
        }
    }
}

