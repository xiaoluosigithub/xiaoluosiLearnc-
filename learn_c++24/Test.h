//
// Created by lyx on 2025/8/3.
//

#ifndef LEARNC___TEST_H
#define LEARNC___TEST_H
#include <iostream>
#include <memory>

class Test {

};

class B;
class A{
public:
    std::weak_ptr<B> ptrB;
    A(){
        std::cout << "A()" << std::endl;
    }
    ~A(){
        std::cout << "~A()" << std::endl;
    }
};

class B{
public:
    std::weak_ptr<A> ptrA;
    B(){
        std::cout << "B()" << std::endl;
    }
    ~B(){
        std::cout << "~B()" <<std::endl;
    }
};

#endif //LEARNC___TEST_H
