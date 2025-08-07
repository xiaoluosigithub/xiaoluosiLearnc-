//
// Created by lyx on 2025/8/7.
//

#include <iostream>
#include <string>
#include "template2.h"

int main(){
    Printer<int> intPrinter;
    intPrinter.print(10);
    Printer<std::string> strPrinter;
    strPrinter.print("Hello");

    double value = 10.5;
    Pair<std::string, double* > p2("ABC", &value);

    printValue(42);

    printAll(10, 20.5, "abc");

    coutAll(11, 20.3, "abdd");

    std::cout << sumAll(1, 3.3, 666) << std::endl;

    return 0;
}