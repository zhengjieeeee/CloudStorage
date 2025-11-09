#include "ThreadCache.h"
#include "CentralCache.h"
#include <cstdlib>

void* ThreadCache::allocate(size_t size){
    if (size == 0){
        // 至少分配一个对齐大小
        size = ALIGNMENT;
    }
    if (size > MAN_BYTES){
        // 大内存直接从系统分配
        return malloc(size);
    }

    size_t index = SizeClass::getIndex(size);

    freelistSize_[index]--;

    // 检查线程本地自由链表
    if (void* ptr = freelist_[index]){
        // 将头节点取出返回，更新头节点为下一个
        freelist_[index] = *reinterpret_cast<void**>(ptr);
        return ptr;
    }

    // 如果线程本地为空，则从中心缓存获取一批内存
    return fetchFromCentralCache(index);
}

void ThreadCache::deallocate(void* ptr, size_t size){
    if (size > MAN_BYTES){
        free(ptr);
        return;
    }

    size_t index = SizeClass::getIndex(size);

    // 让该节点的值等于头节点，再让该节点成为头节点
    *reinterpret_cast<void**>(ptr) = freelist_[index];
    freelist_[index] = ptr;

    freelistSize_[index]++;

    // 判断是否需要将部分内存回收给中心内存
    if (shouldReturnToCentralCache(index)){
        returnToCentralCache(freelist_[index], size);
    }
}

bool ThreadCache::shouldReturnToCentralCache(size_t index){
    size_t threshold = 128;
    return (freelistSize_[index] > threshold);
}

void* ThreadCache::fetchFromCentralCache(size_t index){
    // 从中心缓存批量获取内存
    void* start = CentralCache::getInstance().fetchRange(index);
    if (!start) return nullptr;

    // 取一个返回，剩下的放入链表
    void* result = start;
    freelist_[index] = *reinterpret_cast<void**>(start);

    size_t batchNum = 0;
    void* current = start;

    // 计算从中心缓存获取的内存块的数量
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
        freelist_[index] = start;

        // 更新自由链表大小
        freelistSize_[index] = keepNum;

        // 将剩余部分返回给CentralCache
        if (returnNum > 0 && nextNode != nullptr)
        {
            CentralCache::getInstance().returnRange(nextNode, returnNum * alignedSize, index);
        }
    }
}

