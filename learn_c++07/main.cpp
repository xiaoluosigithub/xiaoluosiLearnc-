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


    return 0;
}