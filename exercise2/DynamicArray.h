//
// Created by lyx on 2025/8/4.
//

#ifndef LEARNC___DYNAMICARRAY_H
#define LEARNC___DYNAMICARRAY_H
#include <iostream>

class DynamicArray {
public:
    // 构造函数
    DynamicArray();
    // 析构函数
    ~DynamicArray();
    // 添加元素
    void add(int value);
    // 获取元素
    [[nodiscard]] int get(size_t index) const;
    // 获取元素个数
    [[nodiscard]] size_t getSize() const;
private:
    void resize(size_t new_capacity); // 扩容
    size_t _capacity; // 容量
    size_t _size{}; // 元素个数
    int * _data; //  数据

};
#endif //LEARNC___DYNAMICARRAY_H
