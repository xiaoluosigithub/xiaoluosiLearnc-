//
// Created by lyx on 2025/8/1.
//
#include <iostream>
#include <vector>

void demo1(){
    int x = 27;
    int y = 15;
    std::cout << "Before swap x = " << x << " y = " << y << std::endl;
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
    std::cout << "After swap x = " << x << " y = " << y << std::endl;
}

void ChangeNum(int &x){
    std::cout << "Before change x = " << x << std::endl;
    x = x * x;
    std::cout << "After change x = " << x << std::endl;
}
void ChangeNum(int *x){
    std::cout << "Before change x = " << *x << std::endl;
    (*x) = (*x) * (*x);
    std::cout << "After change x = " << *x << std::endl;
}

int sumRange(std::vector<int>::iterator start, std::vector<int>::iterator end){
    int ret = 0;
    for(auto i = start; i != end; i++){
        ret += *i;
    }
    return ret;
}

int main(){
    demo1();
    int num = 3;
    ChangeNum(num);
    ChangeNum(&num);
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::cout << "sumRange = " << sumRange(vec.begin(), vec.end()) << std::endl;

    return 0;
}



