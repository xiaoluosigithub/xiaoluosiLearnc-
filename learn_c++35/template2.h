//
// Created by lyx on 2025/8/7.
//

#ifndef LEARNC___TEMPLATE2_H
#define LEARNC___TEMPLATE2_H
#include <iostream>


template <typename T>
class Printer{
public:
    void print(const T & obj){
        std::cout << "General Printer : " << obj << std::endl;
    }
};

template<>
class Printer<std::string>{
public:
    void print(std::string obj){
        std::cout << "String Printer : " << obj << std::endl;
    }
};

template <typename T, typename U>
class Pair{
public:
    T first;
    U second;
    Pair(T a, U b) : first(a), second(b){}
    void print() const{
        std::cout << "Pair : " << first << ", " << second << std::endl;
    }
};

template<typename T, typename U>
class Pair<T, U*>{
public:
    T first;
    U * second;
    Pair(T a, U * b) : first(a), second(b){}
    void print() const{
        std::cout << "Pair : " << first << ", " << *second << std::endl;
    }
};


template <typename T>
void printValue(const T& obj){
    std::cout << "General printValue : " << obj << std::endl;
}

// 为 std::string 特化添加前置声明
template<>
void printValue<std::string>(const std::string& obj);

// 为 int* 特化添加前置声明
template<>
void printValue<int*>(int* const& p);

template<>
inline void printValue<std::string>(const std::string& obj){
    std::cout << "String printValue : " << obj << std::endl;
}

template<>
inline void printValue<int *>(int* const& p){
    if (p != nullptr) {
        std::cout << "int * printValue : " << *p << std::endl;
    } else {
        std::cout << "int * printValue : nullptr" << std::endl;
    }
}

void printAll();

template<typename T, typename... Args>
void printAll(const T& first, const Args&... args){
    std::cout << first << " ";
    printAll(args...);
}

template<typename... Args>
void coutAll(const Args&... args){
    ((std::cout << args << ' '), ...);
}


template<typename... Args>
auto sumAll(Args... args) -> decltype((args + ...)){
    return (args + ...);
}

#endif //LEARNC___TEMPLATE2_H
