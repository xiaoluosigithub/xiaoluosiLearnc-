//
// Created by lyx on 2025/8/2.
//

#include "MemoryPool.h"

MemoryPool::MemoryPool(size_t objSize, size_t totalSize): objSize(objSize), totalSize(totalSize){
    pool = (char *) malloc(objSize * totalSize);
    if(pool == nullptr){
        throw std::bad_alloc();
    }

    // 初始化freeList
    for(size_t i = 0; i < totalSize; ++i){
        freeList.push(pool + i * objSize);
    }

}

MemoryPool::~MemoryPool() {
    free(pool);
}

void *MemoryPool::allocate() {
    if(freeList.empty()){
        throw std::bad_alloc();
    }
    void *p = freeList.top();
    freeList.pop();
    return p;
}

void MemoryPool::deallocate(void *ptr) {
    freeList.push(ptr);
}
