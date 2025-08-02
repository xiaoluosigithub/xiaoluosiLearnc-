//
// Created by lyx on 2025/8/2.
//

#ifndef LEARNC___MEMORYPOOL_H
#define LEARNC___MEMORYPOOL_H
#include <iostream>
#include <stack>

class MemoryPool {
public:
    // 构造函数
    MemoryPool(size_t objSize, size_t totalSize);
    // 析构函数
    ~MemoryPool();
    // 分配内存
    void *allocate();
    // 释放内存
    void deallocate(void *ptr);

private:
    size_t objSize;
    size_t totalSize;
    char *pool;
    std::stack<void *> freeList;
};


#endif //LEARNC___MEMORYPOOL_H
