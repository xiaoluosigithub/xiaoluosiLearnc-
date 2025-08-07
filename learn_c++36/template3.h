//
// Created by lyx on 2025/8/7.
//

#ifndef LEARNC___TEMPLATE3_H
#define LEARNC___TEMPLATE3_H
#include <iostream>
template<typename... Args>
bool allNot(const Args&... args){
    // 对每个参数进行逻辑非运算，再逻辑与运算
    return (!args && ...);
}

template<typename... Args>
auto sumLeftFold(const Args&... args) -> decltype((args + ...)){
     return (args + ...);
}

template<typename... Args>
auto mulRightFold(const Args&... args) -> decltype((... * args)){
    return (... * args);
}

template<typename... Args>
void printAll(const Args&... args){
    // 左折叠
    (std::cout << ... << args) << std::endl;
}

struct MyPoint{
        int x, y;
        MyPoint(int a, int b) : x(a), y(b){}
        MyPoint operator + (const MyPoint& other) const{
            return MyPoint(x + other.x, y + other.y);
        }
};

template<typename... Args>
auto sumPoints(const Args&... args) -> decltype((args + ...)){
    return (args + ...);
}


#endif //LEARNC___TEMPLATE3_H
