//
// Created by lyx on 2025/8/1.
//
#include <iostream>
#include "Derived.h"


int main(){
//    Derived d(10, 20);
//    d.derivedFunc();
//    d.baseFunc();
    std::cout << "------------------" << std::endl;
    Derived d2;
//    d2.derivedFunc();
//    d2.baseFunc();
    d2.display();
    std::cout << "----------------" << std::endl;
    d2.callBaseDisplay();
    std::cout << "-----------------" << std::endl;
    Base *bp = new Derived();
    bp->display();
    std::cout << "-----------------" << std::endl;

    Vehicle * pcar = new Car();
    pcar->startEngine();

    Vehicle * pmt = new Motorcycle();
    pmt -> startEngine();


    return 0;
}