//
// Created by lyx on 2025/8/3.
//
#include <iostream>
#include <functional>

int add(int a, int b){
    return a + b;
}

struct Multiply{
    int operator()(int a, int b) const{
        return a * b;
    }
};

// 定义回调类型
using Callback = std::function<void(int)>;

// 触发事件函数
void triggerEvent(Callback cb, int value){
    // 事件发生调用回调
    cb(value);
}

void print(int a, int b, int c){
    std::cout << a << ' ' << b << ' ' << c << std::endl;
}

class Calculator{
public:
    Calculator(): result(0){}
    int result;
    int multiply(int a, int b){
        result = a * b;
        return result;
    }
};

int main(){

    // 封装普通函数
    std::function<int(int, int)> func1 = add;
    std::cout << "add(1, 2) = " <<func1(1, 2) << std::endl;

    // 封装lambda表达式
    std::function<int(int, int)> func2 = [](int a, int b) -> int{
        return a - b;
    };
    std::cout << "func2(1, 2) = " << func2(10, 4) << std::endl;

    // 封装函数对象
    Multiply multiply;
    std::function<int(int, int)> fun3 = multiply;
    std::cout << "multiply(1, 2) = " << fun3(1, 2) << std::endl;

    triggerEvent([](int x){
        std::cout << "事件触发,值为 : " << x << std::endl;
    }, 42);

    struct Printer{
        void operator()(int x) const{
            std::cout << "Printer: " << x << std::endl;
        }
    } printer;

    triggerEvent(printer, 42);

    std::vector<std::function<int(int, int)>> operations;
    operations.emplace_back(add);
    operations.emplace_back(Multiply());
    operations.emplace_back([](int a, int b){
        return a - b;
    });

    for(auto &op : operations){
        std::cout << op(10, 5) << std::endl;
    }

    std::cout << "------------" << std::endl;

    auto new_add = std::bind(add, 10, std::placeholders::_1);
    std::cout << new_add(5) << std::endl;

    auto new_fun = std::bind(print, std::placeholders::_3, std::placeholders::_2, std::placeholders::_1);
    new_fun(1, 2, 3);

    std::cout << "------------------" << std::endl;

    auto new_add2 = [](int b) -> int{
        return add(10, b);
    };
    std::cout << new_add2(5) << std::endl;

    std::cout << "------------------" << std::endl;

    Calculator calc;
    auto new_mul = std::bind(&Calculator::multiply, &calc, 5, std::placeholders::_1);
    std::cout << new_mul(10) << std::endl;

    auto new_mul2 = [&calc](int a) {
        return calc.multiply(5, a);
    };
    std::cout << new_mul2(3) << std::endl;

    return 0;
}