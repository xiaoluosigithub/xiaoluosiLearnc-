//
// Created by lyx on 2025/7/31.
//

#ifndef LEARNC___STUDENT_H
#define LEARNC___STUDENT_H
#include <string>
#include <iostream>
#include <sstream>

class StudentFriend;
class Student {

public:
    Student();
    Student(const std::string &name, int age, const std::string &num);
    Student(const Student &student);
    Student(Student && student);
    ~Student();
    void ChangeName(const std::string &name){
        _name = name;
    }
    void ChangeAge(int age);
    void ChangeNum(const std::string &num);

    std::string GetName() const;
    int GetAge() const;
    std::string GetNum() const;

    Student& operator=(const Student &student);
    Student& operator=(Student && student);
    friend void ChangeAge(Student &student, int age);
    friend class StudentFriend;
    friend std::ostream &operator<<(std::ostream &out, const Student &student);

private:
    std::string _name;
    int _age;
    std::string _num;
    static int _money;
};

class StudentFriend{
public:
    StudentFriend() = default;
    void ChangeAge(Student &student, int age){
        student._age = age;
    }
};


#endif //LEARNC___STUDENT_H
