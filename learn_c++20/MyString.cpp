//
// Created by lyx on 2025/8/1.
//



#include "MyString.h"



// 带参构造
MyString::MyString(const char *str) {
    // 判断传入指针是否为空
    if(str == nullptr){
        _data = nullptr;
        return;
    }
    // 申请空间
    _data = new char[strlen(str) + 1];
    // 进行深拷贝
    strcpy(_data, str);
    // 设置末尾'\0'
    _data[strlen(str)] = '\0';
}

// 拷贝构造
MyString::MyString(const MyString &other) {
   if(other._data == nullptr){
       _data = nullptr;
       return;
   }
    // 申请空间
    _data = new char[strlen(other._data) + 1];
    // 进行深拷贝
    strcpy(_data, other._data);
    // 设置末尾'\0'
    _data[strlen(other._data)] = '\0';
}

// 拷贝赋值
MyString &MyString::operator=(const MyString &other) {
    // 判断自身是否为other
    if(this == &other) return *this;
    // 判断拷贝的数据是否为空
    if(other._data == nullptr){
        _data = nullptr;
        return * this;
    }
    // 清空数据
    delete[] _data;
    // 申请空间
    _data = new char[strlen(other._data) + 1];
    // 进行深拷贝
    strcpy(_data, other._data);
    // 设置末尾'\0'
    _data[strlen(other._data)] = '\0';
    return *this;
}
// 移动构造
MyString::MyString(MyString &&other) {
    // 判断拷贝的数据是否为空
    if(other._data == nullptr){
        _data = nullptr;
        return;
    }

    // 申请空间
    _data = new char[strlen(other._data) + 1];
    // 进行深拷贝
    strcpy(_data, other._data);
    // 设置末尾'\0'
    _data[strlen(other._data)] = '\0';
}
// 移动赋值
MyString &MyString::operator=(MyString &&other) {
    // 判断自身是否为other
    if(this == &other) return *this;
    // 判断拷贝的数据是否为空
    if(other._data == nullptr){
        _data = nullptr;
        return * this;
    }
    // 清空数据
    delete[] _data;
    // 申请空间
    _data = new char[strlen(other._data) + 1];
    // 进行深拷贝
    strcpy(_data, other._data);
    // 设置末尾'\0'
    _data[strlen(other._data)] = '\0';
    return *this;
}
// 重载加法
MyString &MyString::operator+(const MyString &other) {
    // 判断后面的是否为空
    if(other._data == nullptr){
        return *this;
    }
    // 申请一个新空间
    char *temp = new char[strlen(_data) + strlen(other._data) + 1];
    // 进行深拷贝
    strcpy(temp, _data);
    // 进行拼接
    strcat(temp, other._data);
    // 释放旧空间
    delete[] _data;
    // 赋值给新空间
    _data = temp;
    return *this;
}
// 重载等于
bool MyString::operator==(const MyString &other) {
    // 判断是否为空
    if(other._data == nullptr){
        return _data == nullptr;
    }
    // 进行比较
    return strcmp(_data, other._data) == 0;
}
// 重载输出
std::ostream & operator << (std::ostream & out, const MyString & other){
    out << other._data;
    return out;
}

MyString::~MyString() {
    if(_data == nullptr) return;
    delete[] _data;
    _data = nullptr;
}
