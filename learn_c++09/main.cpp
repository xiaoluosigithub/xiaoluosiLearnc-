//
// Created by lyx on 2025/7/30.
//
#include <iostream>
#include <string>

struct Book{
    std::string title;
    std::string author;
    int pages;

    void printInfo() const {
        std::cout << "书名：" << title << std::endl;
        std::cout << "作者：" << author << std::endl;
        std::cout << "页数：" << pages << std::endl;
    }
};

struct Student{
    int id;
    std::string name;
    float grade;

    // 构造函数， 用来创建对象时调用，并且传入参数赋值给成员变量
    Student(int studentId, std::string studentName, float studentGrade)
    :id(studentId), name(studentName){
        grade = studentGrade;
    }
    Student(){
        id = 0;

    }
};

struct Point{
    int x;
    int y;
};
// 通过值传递
void printPiont(Point p){
    std::cout << "x = " << p.x << " y = " << p.y << std::endl;
}

// 通过引用传递
void movePoint(Point &p, int dx, int dy){
    p.x += dx;
    p.y += dy;
}


int main() {
    system("chcp 65001");
    Student student1;
    Student student2;

    student1.id = 12300;
    student1.name = "lyx";

    student2.id = 12301;
    student2.name = "lyx";

    std::cout << student1.id << " " << student1.name << std::endl;
    std::cout << student2.id << " " << student2.name << std::endl;

    // 快速初始化结构体变量
    Student student3 = {12302, "Pop", 100.0};
    std::cout << student3.id << " " << student3.name << std::endl;

    // 运算符重载后才能直接输出
    // std::cout << student3 << std::endl;

    Student student5(1004,"Daisy", 100.0);
    std::cout << "学生姓名 ： " << student5.name
    << "  学生学号 ： " << student5.id
    << "  学生成绩 ： " << student5.grade<< std::endl;


    int array[3] = {1, 2, 3};

    struct Car{
        std::string brand;
        std::string model;
        int year;
    };
    Car car1 = {"BMW", "X5", 1999};
    int a = 100;
    int *p = &a;
    Car *pcar = &car1;

    std::cout << "品牌 ：" << pcar->brand << std::endl;
    std::cout << "型号 ：" << pcar->model << std::endl;
    std::cout << "年份 ：" << pcar->year << std::endl;

    Book book1 = {"C++", "Bob", 100};
    Book book2 = {"C++ Primer Plus", "StanleyB.Lippman", 976};
    book1.printInfo();
    book2.printInfo();

    Point p1 = {10, 20};
    printPiont(p1);
    movePoint(p1, 5, 5);

    return 0;
}