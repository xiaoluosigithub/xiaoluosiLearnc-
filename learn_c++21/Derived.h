//
// Created by lyx on 2025/8/1.
//

#ifndef LEARNC___DERIVED_H
#define LEARNC___DERIVED_H
#include <iostream>

class Base{
public:
//    Base() = default;
    Base(int num1, int num2) : privateNum(num1), protectedNum(num2){
        std::cout << "Base Constructor 基类构造函数" << std::endl;
    }
    ~Base(){
//        std::cout << "Base Destructor 基类析构函数" << std::endl;
    }
    void baseFunc(){
        std::cout << "Base Func" << std::endl;
        std::cout << "Private Num = " << privateNum << std::endl;
        std::cout << "Protected Num = " << protectedNum << std::endl;
    }
    virtual void display();

private:
    int privateNum;
protected:
    int protectedNum;
};

class Derived : public Base{
public:
    Derived(): Base(1, 2){
        std::cout << "Derived Constructor 子类构造函数" << std::endl;
    }
    Derived(int num1, int num2): Base(num1, num2){
        std::cout << "Derived Constructor 子类构造函数" << std::endl;
    }
    ~Derived(){
//        std::cout << "Derived Destructor 子类析构函数" << std::endl;
    }
    void derivedFunc(){
        std::cout << "Derived Func" << std::endl;
        // std::cout << "Private Num = " << privateNum << std::endl;
        std::cout << "Protected Num = " << protectedNum << std::endl;
    }

    virtual void display()override {
        std::cout << "Derived display 子类虚函数" << std::endl;
        std::cout << "Protected Num = " << protectedNum << std::endl;
    }

    void callBaseDisplay(){
        Base::display();
    }

};

class Vehicle{
public:
    virtual void startEngine() = 0;
};

class Car: public Vehicle{
public:
    void startEngine() override{
        std::cout << "Car startEngine" << std::endl;
    }
};

class Motorcycle: public Vehicle{
public:
    void startEngine() override{
        std::cout << "Motorcycle startEngine" << std::endl;
    }
};


#endif //LEARNC___DERIVED_H
