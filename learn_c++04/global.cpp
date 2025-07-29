//
// Created by lyx on 2025/7/29.
//
#include "global.h"
#include <iostream>
int global_age = 10;
std::string global_name = "abcd";

// 实现全局函数
void print_global(){
    std::cout << "global function called" << std::endl;
    std::cout << "global_name : " << global_name << std::endl;
    std::cout << "global_age : " << global_age << std::endl;
}