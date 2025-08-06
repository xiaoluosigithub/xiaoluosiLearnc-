//
// Created by lyx on 2025/8/6.
//
#include <iostream>
#include "template.h"
#include <list>
int main(){
//    std::cout << maxValue(1, 2) << std::endl;
//    std::cout << maxValue(2.2, 4.9) << std::endl;
//    std::cout << maxValue('A', 'B') << std::endl;
//    std::cout << maxValue("ABC", "GJK") << std::endl;
    Pair<int, int>  p1(1, 2);
    p1.print();

    Pair<double, std::string> p2(2.2, "ABC");
    p2.print();

    FixedArray<int, 10> arr;
    for(int i = 0; i < 5; ++i){
        arr[i] = i * 10;
    }
    arr.print();


    ContainerPrinter<std::vector, int> vecPrinter;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    vecPrinter.print(vec);

    ContainerPrinter<std::list, int> listPrinters;
    std::list<int> list = {10, 20, 30, 40, 55};
    listPrinter.print(list);

    return 0;
}