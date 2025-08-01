//
// Created by lyx on 2025/8/1.
//

#include "Derived.h"

void Base::display(){
    std::cout << "Base display 基类虚函数" << std::endl;
    std::cout << "Private Num = " << privateNum << std::endl;
    std::cout << "Protected Num = " << protectedNum << std::endl;
}