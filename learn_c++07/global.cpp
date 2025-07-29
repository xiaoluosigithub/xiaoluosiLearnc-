//
// Created by lyx on 2025/7/29.
//

#include "global.h"
#include <iostream>

const int bufSize2 = 10;
void PrintBufAdress(){
    std::cout << "global.cpp buf address : " << &bufSize << std::endl;
    std::cout << "global.cpp buf2 address : " << &bufSize2 << std::endl;
}