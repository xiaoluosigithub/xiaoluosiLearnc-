//
// Created by lyx on 2025/7/31.
//
#include <iostream>
#include <vector>
#include <string>

struct Student{
    int id;
    std::string name;
    float grade;

    void printInfo() const{
        std::cout << "学生ID" << id
        << "学生姓名" << name
        << "学生成绩" << grade << std::endl;
    }
};

// 添加学生
void addStudent(std::vector<Student> &students, int id, const std::string &name, float grade){
    Student newStudent = {id, name, grade};
    students.push_back(newStudent);
    std::cout << "添加学生成功" << std::endl;
}

// 显示所有学生
void displayStudents(const std::vector<Student> &students){
    if(students.empty()){
        std::cout << "没有学生信息" << std::endl;
        return;
    }
    std::cout << "所有学生信息如下：" << std::endl;
    for(const auto &student : students){
        student.printInfo();
    }
}

// 根据ID查找学生
void findStudentById(const std::vector<Student> &students, int id){
    for(const auto &student : students){
        if(student.id == id){
            std::cout << "找到学生信息：" << std::endl;
            student.printInfo();
            return;
        }
    }
    std::cout << "未找到ID为" << id << "的学生" << std::endl;
}

int main(){
    system("chcp 65001");
    std::vector<Student> students;
    int choice;
    do{
        std::cout << "\n===== 学生信息管理系统 =====" << std::endl;
        std::cout << "1. 添加学生" << std::endl;
        std::cout << "2. 显示所有学生" << std::endl;
        std::cout << "3. 根据ID查找学生" << std::endl;
        std::cout << "4. 退出系统" << std::endl;
        std::cout << "请选择操作：";
        std::cin >> choice;

        if(choice == 1){
            int id;
            std::string name;
            float grade;
            std::cout << "请输入学生ID：";
            std::cin >> id;
            std::cout << "请输入学生姓名：";
            std::cin >> name;
            std::cout << "请输入学生成绩：";
            std::cin >> grade;
            addStudent(students,id, name, grade);
        } else if(choice == 2){
            displayStudents(students);
        } else if(choice == 3){
            int searchId;
            std::cout << "请输入要查询的ID：";
            std::cin >> searchId;
            findStudentById(students, searchId);
        } else if(choice == 4){
            std::cout << "感谢使用学生管理系统！" << std::endl;
        } else {
            std::cout << "无效的选择，请重新输入！" << std::endl;
        }

    } while (choice != 4);

    return 0;
}