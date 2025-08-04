//
// Created by lyx on 2025/8/4.
//

#ifndef LEARNC___MEMORYPOOL_H
#define LEARNC___MEMORYPOOL_H
#include <iostream>
#include <stack>

class MemoryPool {
public:
    // 构造函数 传入对象大小和内存池大小
    MemoryPool(size_t objectSize, size_t poolSize);
    ~MemoryPool();
    void * allocate();
    void deallocate(void * ptr);
private:
    size_t _objSize;
    size_t _totalSize;
    char * pool;
    std::stack<void *> freeList;
};
#endif //LEARNC___MEMORYPOOL_H
