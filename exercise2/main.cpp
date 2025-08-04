//
// Created by lyx on 2025/8/2.
//
#include <iostream>
#include "DynamicArray.h"
#include "MemoryPool.h"

class MyClass{
public:
    int value;
    MyClass(int val) : value(val){
        std::cout << "MyClass constructor value: " << value << std::endl;
    }
    ~MyClass(){
        std::cout << "MyClass destructor value: " << value << std::endl;
    }
};

int main(){
    {
//        DynamicArray arr;
//
//        arr.add(1);
//        arr.add(2);
//        arr.add(3);
//        arr.add(4);
//
//        std::cout << "Arr size : " << arr.getSize() << std::endl;
//        std::cout << "Arr[0] : " << arr.get(0) << std::endl;
    }

    {
        try{
            // 创建内存池 容纳3个 MyClass 对象的内存池
            MemoryPool pool(sizeof(MyClass), 3);

            // 对 mem1 申请内存池指针
            void * mem1 = pool.allocate();
            void * mem2 = pool.allocate();


            /* 在一块原始的内存上直接调用构造函数
             * 不要求这块内存之前有一个有效的对象
             * 用于首次构造（构造对象实例）*/
            MyClass* obj1 = new(mem1) MyClass(100);
            MyClass* obj2 = new(mem2) MyClass(200);

            std::cout << "obj1 value: " << obj1->value << std::endl;
            std::cout << "obj2 value: " << obj2->value << std::endl;

            obj1 -> ~MyClass();
            obj2 -> ~MyClass();

            pool.deallocate(mem1);
            pool.deallocate(mem2);
        } catch (const std::bad_alloc & e){
            std::cerr << "Memory pool allocation error : " << e.what() << std::endl;
            return 1;
        }
    }


    return 0;
}