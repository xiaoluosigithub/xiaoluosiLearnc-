//
// Created by lyx on 2025/8/6.
//
#include <iostream>
#include "Complex.h"
int main(){
    Complex c1(3.3, 4);
    Complex c2(5.5, 6);
    auto c3 = c1 + c2;
    std::cout << "c1 + c2 = " << c3 << std::endl;

    auto c4 = c1 - c2;
    std::cout << "c1 - c2 = " << c4 << std::endl;

    auto c5 = c1 * c2;
    std::cout << "c1 * c2 = " << c5 << std::endl;

    Complex c6 = c1;
    std::cout << "c6 = " << c6 << std::endl;

    auto bres = c1 == c3;
    std::cout << "c1 == c3 ? " << bres << std::endl;

    return 0;
}