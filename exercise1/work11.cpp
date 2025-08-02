//
// Created by lyx on 2025/8/2.
//
#include <iostream>
#include <string>

class Person{
private:
    std::string _name;
    int _age;
public:
    Person(const std::string & name, int age){
        this->_name = name;
        this->_age = age;
    }
    virtual void displayInfo() const{
        std::cout << "name is : " << _name << std::endl;
        std::cout << "age is : " << _age << std::endl;
    }
};

class Student: public Person{
private:
    std::string _studentID;
public:
    Student(const std::string &name, int age, const std::string &studentID):
            Person(name, age), _studentID(studentID){
    }
    void displayInfo()const override{
        Person::displayInfo();
        std::cout << "StudentID : " << _studentID << std::endl;
    }
};

void demo1(){
    // 创建 Student 对象
    Student stu("Tom", 20, "S123456");

    // 显示信息
    stu.displayInfo();
}


class Shape{
public:
    virtual void draw(){
        std::cout << "Drawing a generic shape" << std::endl;
    }
    virtual ~Shape(){}
};

class Circle:public Shape{
public:
    void draw() override{
        std::cout << "Drawing a circle." << std::endl;
    }
};


class Rectangle:public Shape{
public:
    void draw() override{
        std::cout << "Drawing a rectangle." << std::endl;
    }
};

void demo2(){
    Shape* shapes[2];
    shapes[0] = new Circle();
    shapes[1] = new Rectangle();

    // 遍历调用 draw()
    for (int i = 0; i < 2; ++i) {
        shapes[i]->draw();
    }

    // 释放内存
    for (int i = 0; i < 2; ++i) {
        delete shapes[i];
    }
}

class Calculator{
public:
    int add(int a, int b){
        return a + b;
    }
    double add(double a, double b){
        return a + b;
    }
};

class AdvancedCalculator: public Calculator{
public:
    using Calculator::add;
    int add(int a, int b, int c){
        return a + b + c;
    }
};

void demo3(){
    AdvancedCalculator test;
    std::cout << test.add(2, 3) << std::endl;
    std::cout << test.add(2.2, 3.3) << std::endl;
    std::cout << test.add(2, 3, 4) << std::endl;
}

class Animal{
public:
    virtual void makeSound() const = 0;
    virtual ~Animal()= default;
};

class Dog: public Animal{
public:
    void makeSound() const override{
        std::cout << "Woof!" << std::endl;
    }
};

class Cat: public Animal{
public:
    void makeSound() const override{
        std::cout << "Meow!" << std::endl;
    }
};

void demo4(){
    Animal* ptr[2];
    ptr[0] = new Dog;
    ptr[1] = new Cat;

    ptr[0]->makeSound(); // Woof!
    ptr[1]->makeSound(); // Meow!

    delete ptr[0];
    delete ptr[1];
}

class Vehicle{
public:
    Vehicle(){
        std::cout << "Vehicle constructed." << std::endl;
    }
    virtual ~Vehicle(){
        std::cout << "Vehicle destructed" << std::endl;
    }
};

class Car:public Vehicle{
public:
    Car(){
        std::cout << "Car constructed" << std::endl;
    }
    ~Car(){
        std::cout << "Car destructed" << std::endl;
    }
};

void demo5(){
    Car car;
}


int main(){
    demo5();
    return 0;
}