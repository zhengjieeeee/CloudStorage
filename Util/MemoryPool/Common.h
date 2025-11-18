#pragma once

#include <cstddef>
#include <atomic>
#include <array>

constexpr size_t ALIGNMENT = 8;
constexpr size_t MAN_BYTES = 1024 * 256;
constexpr size_t FREE_LIST_SIZE = MAN_BYTES / ALIGNMENT;

struct BlockHeader
{
    size_t size_;
    bool inUse_;
    BlockHeader *next_;
};

class SizeClass
{
public:
    static size_t roundUp(size_t bytes){
        return (bytes + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
    }

    static size_t getIndex(size_t bytes){
        bytes = std::max<size_t>(bytes, ALIGNMENT);
        return (bytes + ALIGNMENT - 1) / ALIGNMENT - 1;
    }
};
 
