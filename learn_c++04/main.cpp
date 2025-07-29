//
// Created by lyx on 2025/7/29.
//
#include <iostream>
#include "global.h"

int main(){
    std::cout << "global_age is : " << global_age << std::endl;
    std::cout << "global_name is : " << global_name << std::endl;
    std::cout << "hello world!" << std::endl;
    // 调用全局函数
    print_global();
    return 0;
}