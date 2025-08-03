//
// Created by lyx on 2025/8/3.
//

#include "MyString.h"
#include <iostream>
#include <cstring>
// 有参构造函数
MyString::MyString(const char * str){
    if(str == nullptr){
        _data = nullptr;
        return;
    }
    _data = new char[strlen(str) + 1];
    strcpy(_data, str);
    _data[strlen(str)] = '\0';
}

// 拷贝构造函数
MyString::MyString(const MyString & other){
    if(other._data == nullptr){
        _data = nullptr;
        return;
    }
    _data = new char[strlen(other._data) + 1];
    strcpy(_data, other._data);
    _data[strlen(other._data)] = '\0';
}


// 拷贝赋值
MyString &MyString::operator = (const MyString &other) {
    // 如果该指针 等于传入变量的地址
    if(this == &other){
        return *this; // 返回当前指针的引用
    }
    if(other._data == nullptr){
        delete[] this->_data; // 避免泄漏
        this->_data = nullptr;
        return *this;
    }
    delete[] this->_data;
    this->_data = new char[strlen(other._data) + 1];
    strcpy(this->_data, other._data);
    return *this;
}

// 移动构造
MyString::MyString(const MyString && other) noexcept {
    if(other._data == nullptr){
        this->_data = nullptr;
        return;
    }
    _data = new char[strlen(other._data) + 1];
    strcpy(_data, other._data);
    _data[strlen(other._data)] = '\0';
}

// 移动赋值
MyString& MyString::operator = (MyString && other) noexcept{
    if(this == &other){
        return *this;
    }
    if(other._data == nullptr){
        delete[] _data;
        _data = nullptr;
        return *this;
    }
    delete[] _data;
    _data = new char[strlen(other._data) + 1];
    strcpy(_data, other._data);
    _data[strlen(other._data)] = '\0';
    return *this;
}

// 重载加法
MyString& MyString::operator + (const MyString && other){
    if(other._data == nullptr){
        return *this;
    }
    char *temp = new char[strlen(other._data) + strlen(_data) + 1];
    strcpy(temp, _data);
    strcat(temp, other._data);
    delete[] _data;
    _data = temp;
    return *this;
}

// 比较运算符重载
bool MyString::operator == (const MyString & other){
    if(other._data == nullptr){
        return _data == nullptr;
    }
    return strcmp(_data, other._data) == 0;
}

// 重载输出
std::ostream & operator << (std::ostream & os, const MyString & MyStr){
    os << MyStr._data;
    return os;
}

//重载析构函数
MyString::~MyString(){
    if(_data == nullptr) return;
    delete[] _data;
    _data = nullptr
}
