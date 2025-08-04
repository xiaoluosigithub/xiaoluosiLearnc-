//
// Created by lyx on 2025/8/4.
//

#include "MemoryPool.h"

// 构造函数
MemoryPool::MemoryPool(size_t objectSize, size_t poolSize) :
    _objSize(objectSize), _totalSize(poolSize), pool((char *) malloc(objectSize * poolSize)){
    // 如果申请内存失败
    if(pool == nullptr){
        throw std::bad_alloc();
    }
    for(size_t i = 0; i < poolSize; ++i){
        // 将每个元素的指针 对应 首指针的偏移地址 压入栈中
        freeList.push(pool + i * objectSize);
    }
}

// 析构函数
MemoryPool::~MemoryPool(){
    free(pool);
}

// 申请空闲资源
void * MemoryPool::allocate(){
    // 栈为空
    if(freeList.empty()){
        throw std::bad_alloc();
    }
    void * ptr = freeList.top(); // 取出栈首的空闲指针
    freeList.pop(); // 将其弹出栈
    return ptr; // 返回空闲指针
}

void MemoryPool::deallocate(void * ptr){
    freeList.push((char *)ptr);
}