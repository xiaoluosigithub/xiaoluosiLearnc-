//
// Created by lyx on 2025/7/29.
//
#include <iostream>
#include "global.h"
int main(){


    const int i = 10;
    int const j = 10;

    int const i1 = 10;
    int const i2 = i1;

    int i3 = i2;
    PrintBufAdress();
    std::cout << "main.cpp bufSize address : " << &bufSize << std::endl;
    std::cout << "main.cpp bufSize2 address : " << &bufSize2 << std::endl;

    const int &r1 = i;

    // int &r2 = i; i不允许被修改，那么引用同样无法被修改，只能使用const类型的引用
    const int &r2 = i;

    int m = 1024;
    const int & rm = m;
    int &rm2 = m;
    m = 2048;
    std::cout << "rm = : " << rm << std::endl;
    std::cout << "rm2 = : " << rm2 << std::endl;
    rm2 = 4096;
    std::cout << "rm = : " << rm << std::endl;
    std::cout << "rm2 = : " << rm2 << std::endl;

    {
        const double PI = 3.14;
        const double *ptr = &PI;

    }
    //sz不是常量表达式，运行时计算才得知
    const int sz = GetSize();

    constexpr int i4 = 200;
    constexpr int i5 = GetSizeConst();

    return 0;
}