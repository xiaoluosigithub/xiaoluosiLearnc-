//
// Created by lyx on 2025/8/6.
//

#ifndef LEARNC___TEMPLATE2_H
#define LEARNC___TEMPLATE_H

#include <iostream>
#include <vector>
#include <list>
template <typename T>
T maxValue(T a, T b){
    return a > b ? a : b;
}

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

template<typename T, std::size_t N>
class FixedArray{
public:
    T data[N];
    T& operator[](std::size_t index){
        return data[index];
    }

    void print() const{
        for(std::size_t i = 0; i < N; ++i){
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

template<template<typename, typename> class Container, typename T>
class ContainerPrinter{
public:
    void print(const Container<T, std::allocator<T>> & container){
        for(const auto & elem : container){
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }
};

#endif //LEARNC___TEMPLATE2_H
