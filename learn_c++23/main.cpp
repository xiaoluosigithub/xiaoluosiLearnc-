//
// Created by lyx on 2025/8/2.
//

#include <iostream>
#include "SimpleSharedPtr.h"
#include "../learn_c++22/Student.h"


int main(){
    std::cout << "Creating default shared pointer" << std::endl;
    SimpleSharedPtr<Student> ptr1;
    std::cout << "Ptr1 use_count : " << ptr1.use_count() << std::endl;

    std::cout << "Creating shared pointer with Student" << std::endl;
    SimpleSharedPtr<Student> ptr2(new Student("Tom", 20));
    std::cout << "Ptr2 use_count : " << ptr2.use_count() << std::endl;

    std::cout << "Creating shared from another shared pointer" << std::endl;
    SimpleSharedPtr<Student> ptr3(ptr2);
    std::cout << "Ptr3 use_count : " << ptr3.use_count() << std::endl;
    std::cout << "Ptr2 use_count : " << ptr2.use_count() << std::endl;

    std::cout << "-----------------" << std::endl;
    ptr1 = ptr3;
    std::cout << "Ptr1 use_count : " << ptr1.use_count() << std::endl;
    std::cout << "Ptr3 use_count : " << ptr3.use_count() << std::endl;
    std::cout << "Ptr2 use_count : " << ptr2.use_count() << std::endl;
    std::cout << "-----------------" << std::endl << std::endl;

    ptr2.reset(new Student("Ray", 23));
    std::cout << "Ptr2 use_count : " << ptr2.use_count() << std::endl;
    std::cout << "Ptr3 use_count : " << ptr3.use_count() << std::endl;
    std::cout << "Ptr1 use_count : " << ptr1.use_count() << std::endl;



    return 0;
}