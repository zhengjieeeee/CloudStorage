 #include "PageCache.h"
#include <sys/mman.h>
#include <cstring>

void* PageCache::allocateSpan(size_t numPages){
    std::lock_guard<std::mutex> lock(mutex_);

    //lower_bound返回第一个大于等于numPages的迭代器
    auto it = freeSpan_.lower_bound(numPages);  
    if (it != freeSpan_.end()){
        Span* span = it -> second;

        // 将取出的span从原有的空闲链表freeSpans_[it->first]中移除
        if (span -> next_){
            freeSpan_[it -> first] = span -> next_;
        }else{
            freeSpan_.erase(it);
        }

        // 如果span大于需要的numPages则进行分割
        if (span -> numPages_ > numPages){
            Span* newSpan = new Span;
            newSpan -> pageAddr_ = static_cast<char*>(span -> pageAddr_) + numPages * PAGE_SIZE;
            newSpan -> numPages_ = span -> numPages_ - numPages;
            newSpan -> next_ = nullptr;

            auto& list = freeSpan_[newSpan -> numPages_];
            newSpan -> next_ = list;
            list = newSpan;

            span -> numPages_ = numPages;
        }

        spanMap_[span -> pageAddr_] = span;
        return span -> pageAddr_;
    }

    //没有合适的span，向系统申请
    void* memory = systemAlloc(numPages);
    if (!memory) return nullptr;

    Span* span = new Span;
    span -> pageAddr_ = memory;
    span -> numPages_ = numPages;
    span -> next_ = nullptr;

    spanMap_[span -> pageAddr_] = span;
    return span -> pageAddr_;
}

void PageCache::deallocateSpan(void* ptr, size_t numPages){
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = spanMap_.find(ptr);
    if (it == spanMap_.end()) return;

    Span* span = it -> second;

    //尝试合并相邻的span
    void* nextAddr = static_cast<char*>(ptr) + numPages * PAGE_SIZE;
    auto nextIt = spanMap_.find(nextAddr);

    if (nextIt != spanMap_.end()){
        Span* nextSpan = nextIt -> second;

        bool found = false;
        auto& nextList = freeSpan_[nextSpan -> numPages_];

        if (nextList == nextSpan){
            nextList = nextSpan -> next_;
            found = true;
        }else if (nextList){
            Span* pre = nextList;
            while (pre -> next_){
                if (pre -> next_ == nextSpan){
                    pre -> next_ = nextSpan -> next_;
                    found = true;
                    break;
                }
                pre = pre -> next_;
            }
        }

        //只有在找到nextSpan的情况下才进行合并
        if (found){
            span -> numPages_ += nextSpan -> numPages_;
            spanMap_.erase(nextAddr);
            delete nextSpan;
        }
    }

    auto& list = freeSpan_[span -> numPages_];
    span -> next_ = list;
    list = span;
}

void* PageCache::systemAlloc(size_t numPages){
    size_t size = numPages * PAGE_SIZE;

    void* ptr = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    memset(ptr, 0, size);
    return ptr;
}