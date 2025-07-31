//
// Created by lyx on 2025/7/31.
//

#include "Student.h"

int Student::_money = 100;

void Student::ChangeAge(int age) {
    _age = age;
}

std::string Student::GetName() const {
    return _name;
}

void Student::ChangeNum(const std::string &num) {
    _num = num;
}

int Student::GetAge() const {
    return _age;
}
std::string Student::GetNum() const {
    return _num;
}

Student::Student(): _name("default"), _num("0"), _age(0){

}
Student::Student(const std::string &name, int age, const std::string &num)
    : _name(name), _num(num), _age(age)
{
    _name = name;
    _age = age;
    _num = num;
}
Student::Student(const Student &student) :
    _name(student._name), _num(student._num), _age(student._age){

}

Student::Student(Student &&student):
    _name(std::move(student._name)),
    _num(std::move(student._num)),
    _age(student._age)
{}

Student::~Student(){
    std::cout <<  "~Student()" << std::endl;
}

Student &Student::operator=(const Student &student) {
    if(this == &student){
        return *this;
    }
    this->_name = student._name;
    this->_num = student._num;
    this->_age = student._age;
    return * this;
}

Student &Student::operator=(Student &&student) {
    if(this == &student){
        return *this;
    }
    this->_name = std::move(student._name);
    this->_num = std::move(student._num);
    this->_age = student._age;
    return * this;
}

void ChangeAge(Student &student, int age){
    student._age = age;
}

std::ostream &operator<<(std::ostream &out, const Student &student){
    out << student._name << " " << student._num << " " << student._age;
    return out;
}
