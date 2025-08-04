//
// Created by lyx on 2025/8/2.
//

#ifndef LEARNC___DYNAMICARRAY_H
#define LEARNC___DYNAMICARRAY_H
#include <iostream>

// 实现一个简单的动态数组，支持添加元素、访问元素和自动扩展
class DynamicArray {
public:
    DynamicArray():capacity(2), size(0), data((int*)malloc(capacity * sizeof(int))){
        if(data == nullptr){
            std::cerr << "malloc failed" << std::endl;
            throw std::bad_alloc{};
        }
    }
    ~DynamicArray(){
        free(data);
    }
    void add(int value){
        if(size == capacity){
            resize(capacity * 2);
        }
        data[size++] = value;
    }

    int get(size_t index){
        if(index >= size){
            throw std::out_of_range{"index out of range"};
        }
        return data[index];
    }
    size_t getSize() const{
        return size;
    }
private:
    void resize(size_t new_capacity){
        int *temp = (int *)realloc(data, new_capacity * sizeof(int));
        if(temp == nullptr){
            throw std::bad_alloc{};
        }
        data = temp;
        capacity = new_capacity;
    }
    std::size_t capacity;
    std::size_t size;
    int *data;
};


#endif //LEARNC___DYNAMICARRAY_H
