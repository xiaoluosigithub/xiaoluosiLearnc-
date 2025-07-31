//
// Created by lyx on 2025/7/31.
//
#include <iostream>
#include <vector>
#include <algorithm>

int *allocateArray(int size){
    int *arr = new int[size];
    for(int i = 0; i < size; i++){
        arr[i] = i * 2;
    }
    return arr;
}

int add(int a, int b){
    return a + b;
}

int add(int a, int b, int c){
    return a + b + c;
}

double add(double a, double b){
    return a + b;
}

void sayHello(){
    std::cout << "Hello World!" << std::endl;
}

void execute(void (* Pfunc)()){
    // 函数指针解引用调用
    (*Pfunc)();
    // 也可以不解引用
    Pfunc();
}

void execute2(void func()){
    func();
}

int main(){

    int * myArray = allocateArray(5);

    for(int i = 0; i < 5; i++){
        std::cout << myArray[i] << ' ';
    }
    std::cout << std::endl;

    delete[] myArray;

    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::for_each(numbers.begin(), numbers.end(), [](int x){
        std::cout << x << ' ';
    });
    std::cout << std::endl;
    int sum = 0;
    std::for_each(numbers.begin(), numbers.end(), [&sum](int x){
        sum += x;
    });
    std::cout << sum << std::endl;

    // 指向函数的指针
    int (* padd) (int a, int b) = &add;

    std::cout << (*padd)(100, 100) << std::endl;

    int add_result = add(100, 100);
    std::cout << add_result << std::endl;

    execute(sayHello);

    execute2(sayHello);




    return 0;
}