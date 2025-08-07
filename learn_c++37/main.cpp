//
// Created by lyx on 2025/8/7.
//
#include <iostream>
#include "sfinae.h"

int main(){
    int x = 10;
    print_type(x);
    double y = 3.14;
    print_type(y);
    const char * cstr = "Hello world!";
    print_type(cstr);
    std::string str = "Hello world";
    print_type(str);
    print_type(&x);

    cout_type(x);
    cout_type(y);
    cout_type(cstr);
    cout_type(str);
    cout_type(&x);
    cout_type(&y);

    std::cout << "**********" << std::endl;
    WithFoo wf;
    call_foo(wf);



    TypePrinter<WithValueType>::print();
    TypePrinter<WithoutValueType>::print();

    return 0;
}