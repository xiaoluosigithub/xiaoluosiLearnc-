//
// Created by lyx on 2025/8/2.
//

#ifndef LEARNC___STUDENT_H
#define LEARNC___STUDENT_H
#include <iostream>
#include <string>
#include <utility>


class Student {
public:
    Student():age(7), name("student"){}
    Student(std::string name, int age):name(std::move(name)), age(age){}
    std::string name;
    int age;
};


#endif //LEARNC___STUDENT_H
