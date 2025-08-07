//
// Created by lyx on 2025/8/7.
//
#include <iostream>
#include "template3.h"


int main(){
    std::cout << sumLeftFold(1, 2, 3, 4, 5, 6) << std::endl;
    std::cout << mulRightFold(1, 2, 3, 4, 5) << std::endl;

    printAll(1, 2, 3, 4, 5);

    MyPoint p1{1, 2}, p2{3, 4}, p3{5, 6};
    auto sum = sumPoints(p1, p2, p3);
    std::cout << sum.x << ' ' << sum.y << std::endl;
    return 0;
}