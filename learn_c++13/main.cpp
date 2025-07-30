//
// Created by lyx on 2025/7/30.
//
#include <iterator>
#include <iostream>
#include <vector>
int main(){
    {
        std::vector<int> vec{1,2,3,4,5,6,7,8,9};
        auto iter_begin = vec.begin();
        auto iter_end = vec.end();
        auto first_elem = *iter_begin;
        std::cout << first_elem << std::endl;

    }

    {
        std::vector<int> vec_empty;
        auto iter_begin = vec_empty.begin();
        auto iter_end = vec_empty.end();
        if(iter_begin == iter_end){
            std::cout << "vec_empty is empty" << std::endl;
        } else {
            std::cout << "vec_empty is not empty" << std::endl;
        }

    }

    {
        // 定义一个只读迭代器
        std::vector<int>::const_iterator cit;
        std::vector<int> vec = {1, 2, 3};
        for(cit = vec.cbegin(); cit != vec.cend(); ++cit){
            std::cout << *cit << std::endl;
        }

        const std::vector<int> numbers = {10, 20, 30};
        cit = numbers.begin();
        cit = vec.begin();
        auto iter2 = numbers.begin();
        auto iter3 = vec.begin();
    }




    return 0;
}