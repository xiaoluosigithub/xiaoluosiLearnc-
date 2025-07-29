#include <iostream>

void init_variable() {
    // 声明一个整型变量age，未初始化
    int age;
    // 声明并初始化一个整型变量height
    int height = 175;
    // 声明并初始化一个双精度浮点型变量weight
    double weight = 65.5;
    // 声明并初始化一个字符型变量gender
    char gender = 'M';
}

void use_variable() {
    //初始化变量a和b
    int a = 5, b = 10;
    //a+b的值赋值给sum
    int sum = a + b;
    //输出求和的结果
    std::cout << "The sum of " << a << " and "
              << b << " is " << sum << std::endl;
}

void use_cout() {
    // 输出字符串
    std::cout << "Hello, World!" << std::endl;

    // 输出数字
    int number = 42;
    std::cout << "The number is: " << number << std::endl;

    // 输出浮点数
    double pi = 3.14159;
    std::cout << "The value of pi is approximately: " << pi << std::endl;

    // 输出字符
    char ch = 'A';
    std::cout << "The character is: " << ch << std::endl;

    // 输出布尔值（C++11及以后）
    bool truth = 0;
    std::cout << std::boolalpha; // 启用布尔值的true/false输出
    std::cout << "The truth is: " << truth << std::endl;
}

int main() {
    use_cout();
    return 0;
}
