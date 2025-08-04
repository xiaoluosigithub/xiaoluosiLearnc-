//
// Created by lyx on 2025/8/4.
//

#include "DynamicArray.h"

// 构造函数
DynamicArray::DynamicArray() : _capacity(2), _data((int *) malloc(_capacity * sizeof(int))){
    if (_data == nullptr){ // 申请内存失败 抛出异常
        throw std::bad_alloc();
    }
}
// 析构函数
DynamicArray::~DynamicArray(){
    free(_data);
}
// 添加元素
void DynamicArray::add(int value){
    // 若当前元素数量和容量相等,就无法继续添加元素,调用扩容函数,进行扩容
    if(_size == _capacity){
        resize(_capacity * 2);
    }
    _data[_size++] = value; // _data下标从零开始, _size下标对应的位置可以存储
}
// 获取元素
int DynamicArray::get(size_t index) const{
    if(index >= _size){
        throw std::out_of_range("Index out of range!");
    }
    return _data[index];
}
// 获取元素个数
size_t DynamicArray::getSize() const{ return _size;}
// 扩容
void DynamicArray::resize(size_t new_capacity){
    // 申请内存 尝试在原位置扩展内存块,若原位置扩展不了就重新申请一个更大内存块,返回新指针
    int * temp = (int *) realloc(_data, new_capacity * sizeof(int));
    // 若未申请成功
    if (temp == nullptr) {
        // 抛出异常
        throw std::bad_alloc();
    }
    _data = temp; // 更新地址
    _capacity = new_capacity; // 更新容量
}