#pragma once

#include "Common.h"
#include <map>
#include <mutex>

class PageCache
{
public:
    static const size_t PAGE_SIZE = 4096;

    static PageCache& getInstance(){
        static PageCache instance;
        return instance;
    }

    //分配指定页数的span
    void* allocateSpan(size_t numPages);

    //释放span
    void deallocateSpan(void *ptr, size_t numPages);

private:
    PageCache() = default;

    //向系统申请内存
    void* systemAlloc(size_t numPages);

    struct Span
    {
        void* pageAddr_; //页起始地址
        size_t numPages_;//页数
        Span *next_;     //链接相同页数的空闲 Span
    };

    std::map<size_t, Span*> freeSpan_;  //不同页数对应不同Span链表
    std::map<void*, Span*> spanMap_;    //页号到span的映射，用于回收
    std::mutex mutex_;  
};

