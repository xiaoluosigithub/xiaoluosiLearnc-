//
// Created by lyx on 2025/8/2.
//
#include <iostream>
#include <cstdlib>
#include "Student.h"
#include "DynamicArray.h"
#include "MemoryPool.h"

int main(){
    // 分配一个整数内存
    int * p = (int *)malloc(sizeof(int));
    if(p == nullptr){
        std::cerr << "Memory allocation failed." << std::endl;
        return -1;
    }
    *p = 42;
    std::cout << "Value: " << *p << std::endl;

    free(p);

//    Student *st_p = (Student*)malloc(sizeof (Student));
//    if(st_p == nullptr){
//        std::cerr << "Memory allocation failed." << std::endl;
//        return -1;
//    }
//    std::cout << "Student age is" << st_p->age << std::endl;
//    std::cout << "Name is" << st_p->name << std::endl;
//
//    free(st_p);

    int *array_p = (int *)malloc(5 * sizeof(int));
    if(array_p == nullptr){
        std::cerr << "Memory allocation failed." << std::endl;
        return -1;
    }
    for(int i = 0; i < 5; ++i){
        array_p[i] = i * 2;
        *(array_p + i) = i * 2;
    }

    for(int i = 0; i < 5; ++i){
        std::cout << "array_p[" << i << "] = " << array_p[i] << std::endl;
    }
    free(array_p);


    Student *p_stu = new Student("Tom", 20);

    std::cout << "Student age is " << p_stu->age << std::endl;
    std::cout << "Name is " << p_stu->name << std::endl;

    delete p_stu;

    auto pst_array = new Student[2]{
        Student("Tom", 20),
        Student("Jerry", 18)
    };
    for(int i = 0; i < 2; ++i){
        std::cout << "------------------" << std::endl;
        std::cout << "Student age is " << pst_array[i].age << std::endl;
        std::cout << "Name is " << pst_array[i].name << std::endl;
        std::cout << "------------------" << std::endl;
    }
    delete[] pst_array;

    int * arr = (int *) malloc(3 * sizeof(int));
    if(arr == nullptr){
        std::cout << "Memory allocation failed." << std::endl;
        return -1;
    }
    for(int i = 0; i < 3; ++i){
        arr[i] = i * 2;
    }
    for(int i = 0; i < 3; ++i){
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    std::cout << "---------------" << std::endl;

    int * temp = (int *)realloc(arr, 5 * sizeof(int));
    if(temp == nullptr){
        std::cout << "Memory allocation failed." << std::endl;
        free(arr);
        return -1;
    }
    arr = temp;
    for(int i = 3; i < 5; ++i){
        arr[i] = i * 2;
    }
    for(int i = 0; i < 5; ++i){
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    std::cout << "---------------" << std::endl;

    try{
        DynamicArray arr;
        arr.add(10);
        arr.add(20);
        arr.add(30);
        std::cout << "DynamicArray :" << std::endl;
        for(size_t i = 0; i < arr.getSize(); ++i){
            std::cout << "[" << i << "] = " << arr.get(i) << std::endl;
        }
        std::cout << std::endl;
    }catch(const std::bad_alloc & e){
        std::cerr << "Memory allocation failed." << e.what() << std::endl;
        return 1;
    }catch(const std::out_of_range & e){
        std::cerr << "Out of range: " << e.what() << std::endl;
        return 1;
    }catch (const std::exception & e){
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    try{
        MemoryPool pool(sizeof(Student), 3);
        void * mem1 = pool.allocate();
        void * mem2 = pool.allocate();
        void * mem3 = pool.allocate();
        void * mem4 = pool.allocate();


        auto *obj1 = new(mem1) Student("Tom", 20);
        auto *obj2 = new(mem2) Student("Jerry", 18);
        auto *obj3 = new(mem3) Student("Mike", 16);
        auto *obj4 = new(mem4) Student("Lucy", 14);

        std::cout << "-----------------" << std::endl;
        std::cout << "obj1 age is " << obj1->age << "Name is " << obj1->name << std::endl;
        std::cout << "obj2 age is " << obj2->age << "Name is " << obj2->name << std::endl;
        std::cout << "obj3 age is " << obj3->age << "Name is " << obj3->name << std::endl;
        std::cout << "-----------------" << std::endl;

        // 显示调用析构
        obj1 -> ~Student();
        obj2 -> ~Student();
        obj3 -> ~Student();
        obj4 -> ~Student();

        pool.deallocate(mem1);
        pool.deallocate(mem2);
        pool.deallocate(mem3);
        pool.deallocate(mem4);

    }catch(const std::bad_alloc & e){
        std::cerr << "Memory allocation failed." << e.what() << std::endl;
        return 1;
    }


    return 0;
}