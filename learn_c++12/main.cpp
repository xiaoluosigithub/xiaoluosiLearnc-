//
// Created by lyx on 2025/7/30.
//
#include <iostream>
#include <vector>

int main(){

    std::vector<int> vec(10, 10);
    vec.clear();
    // 立即回收容量机制
    {
        std::vector<int> empty_vec;
        empty_vec.swap(vec);
        std::cout << "After swap vec capacity : " << vec.capacity() << std::endl;
        std::cout << "After swap empty_vec capacity : " << empty_vec.capacity() << std::endl;
    }

    std::vector<std::string> fruits = {"apple", "orange", "pear", "banana"};
    std::cout << "first fruit : " << fruits[0] << std::endl;
    std::cout << "Second fruit : " << fruits[1] << std::endl;

    try{
        std::cout << "invalid index : " << fruits.at(10086) << std::endl;
    }catch(const std::out_of_range& e){
        std::cerr << "Exception : " << e.what() << std::endl;
    }

    return 0;
}