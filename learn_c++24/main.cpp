//
// Created by lyx on 2025/8/3.
//
#include <iostream>
#include <memory>
#include "../learn_c++22/Student.h"
#include "Test.h"


struct FileDeleter{
    void operator()(FILE * fp){
        if(fp){
            std::cout << "File is closed" << std::endl;
            fclose(fp);
        }
    }
};


int main(){
    auto * student = new Student();
    // std::shared_ptr<Student> shared_student(student);
    // std::shared_ptr<Student> shared_student = std::shared_ptr<Student>(student);
    // std::shared_ptr<Student> shared_student(new Student());
    auto shared_student = std::make_shared<Student>("Tom", 22);

    std::shared_ptr<Student> shared_student2 = shared_student;
    std::cout << "After shared_student2 = shared_student, the use count is: " << std::endl;
    std::cout << shared_student.use_count() << std::endl;
    std::cout << shared_student2.use_count() << std::endl;

    std::unique_ptr<Student> ptr1(new Student("Tom", 22));
    std::unique_ptr<Student> ptr2 = std::move(ptr1);

    std::unique_ptr<Student> ptr3 = std::make_unique<Student>("Jack", 29);

    {
        std::cout << "----------------" << std::endl;
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();

        std::cout << a.use_count() << std::endl;
        std::cout << b.use_count() << std::endl;

        a->ptrB = b;
        b->ptrA = a;

        std::cout << a.use_count() << std::endl;
        std::cout << b.use_count() << std::endl;

        std::cout << "----------------" << std::endl;
    }

    {
//        std::shared_ptr<FILE> file_ptr(fopen("test.txt", "w"), FileDeleter());
//        if(file_ptr){
//            std::cout << "File is opened" << std::endl;
//            fprintf(file_ptr.get(), "Hello World!\n");
//        }
    }

    {
        auto fileDeleter = [](FILE *fp){
            if(fp){
                std::cout << "File is closed" << std::endl;
                fclose(fp);
            }
        };
        std::unique_ptr<FILE, decltype(fileDeleter)> file_ptr(fopen("test.txt", "w"),fileDeleter);
        if(file_ptr){
            std::cout << "File is opened" << std::endl;
            fprintf(file_ptr.get(), "Hello World!");
        }
    }

    return 0;
}