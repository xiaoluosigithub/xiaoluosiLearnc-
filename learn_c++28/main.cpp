//
// Created by lyx on 2025/8/4.
//
#include <iostream>
#include <deque>
#include "Deque.h"

int main(){
    Deque<std::string> dq;
    dq.push_back("Hello");
    dq.push_back("World!");
    for(auto it = dq.begin(); it != dq.end(); ++it){
        std::cout << *it << std::endl;
    }
    std::cout << "-----------" << std::endl;
    dq.push_front("C++");
    dq.push_front("Programming");
    for(auto it = dq.begin(); it != dq.end(); ++it){
        std::cout << *it << std::endl;
    }


    return 0;
}