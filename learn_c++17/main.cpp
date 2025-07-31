//
// Created by lyx on 2025/7/31.
//
#include <iostream>
#include <stdexcept>

// 函数，计算除法
double divide(double numerator, double denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero."); // 抛出异常
    }
    return numerator / denominator;
}

int main() {
    double num, denom;

    std::cout << "Enter numerator: ";
    std::cin >> num;
    std::cout << "Enter denominator: ";
    std::cin >> denom;

    try {
        double result = divide(num, denom);
        std::cout << "Result: " << result << std::endl;
    } catch (std::invalid_argument &e) { // 捕获 std::invalid_argument 异常
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "Program continues after try-catch." << std::endl;
    return 0;
}