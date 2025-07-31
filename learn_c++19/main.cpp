//
// Created by lyx on 2025/7/31.
//
#include <iostream>
#include "Student.h"


int main(){
    Student student1;
    student1.ChangeName("Alice");
    student1.ChangeAge(18);
    student1.ChangeNum("1001");

    std::cout << "Name: " << student1.GetName() << std::endl;
    std::cout << "Age: " << student1.GetAge() << std::endl;
    std::cout << "Num: " << student1.GetNum() << std::endl;

    Student student2;
    std::cout << "Name: " << student2.GetName() << std::endl;
    std::cout << "Age: " << student2.GetAge() << std::endl;
    std::cout << "Num: " << student2.GetNum() << std::endl;

    Student student3("Bob", 19, "1002");

    Student student4(student1);
    std::cout << "Name: " << student4.GetName() << std::endl;
    std::cout << "Age: " << student4.GetAge() << std::endl;
    std::cout << "Num: " << student4.GetNum() << std::endl;

    Student student5(std::move(student1));
    std::cout << "Name: " << student5.GetName() << std::endl;
    std::cout << "Age: " << student5.GetAge() << std::endl;
    std::cout << "Num: " << student5.GetNum() << std::endl;

    Student student6;
    std::cout << "Name: " << student6.GetName() << std::endl;
    std::cout << "Age: " << student6.GetAge() << std::endl;
    std::cout << "Num: " << student6.GetNum() << std::endl;

    student6 = student5;
    std::cout << "Name: " << student6.GetName() << std::endl;
    std::cout << "Age: " << student6.GetAge() << std::endl;
    std::cout << "Num: " << student6.GetNum() << std::endl;

    Student student7 = std::move(student6);
    std::cout << "Name: " << student7.GetName() << std::endl;
    std::cout << "Age: " << student7.GetAge() << std::endl;
    std::cout << "Num: " << student7.GetNum() << std::endl;


    std::cout << "-------------------------------" << std::endl;
    std::cout << "Student7: " << std::endl;
    std::cout << student7 << std::endl;
    std::cout << "-------------------------------" << std::endl;


    return 0;
}