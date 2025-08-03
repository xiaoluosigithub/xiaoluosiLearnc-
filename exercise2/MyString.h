//
// Created by lyx on 2025/8/3.
//

#ifndef LEARNC___MYSTRING_H
#define LEARNC___MYSTRING_H
#include <iostream>

class MyString {
public:
    // 默认构造函数
    MyString() : _data(nullptr){}
    // 有参构造函数
    explicit MyString(const char * str);
    // 拷贝构造函数
    MyString(const MyString & other);
    // 拷贝赋值
    MyString & operator = (const MyString & other);
    // 移动构造
    MyString(const MyString && other) noexcept ;
    // 移动赋值
    MyString & operator = (MyString && other) noexcept ;
    // 重载加法
    MyString & operator + (const MyString && other);
    // 比较运算符重载
    bool operator == (const MyString & other);
    // 输出运算符重载
    friend std::ostream & operator << (std::ostream & os, const MyString & MyStr);
    // 析构函数
    ~MyString();
private:
    char * _data{};
};


#endif //LEARNC___MYSTRING_H
