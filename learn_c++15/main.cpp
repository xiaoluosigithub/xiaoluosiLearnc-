//
// Created by lyx on 2025/7/31.
//
#include <iostream>

int main(){

    {
        // 数组长度为3每一个元素是长度为4的数组
        int ia[3][4] = {
                {1, 2, 3, 4},
                {4, 5, 6, 7},
                {8, 9, 10, 11},
        };
    }
    int ia [3][4] = {
            {1, 2, 3, 4},
            {4, 5, 6, 7},
            {8, 9, 10, 11},
    };

    typedef int int_array_t [4];

    for(int_array_t *p = ia; p != ia + 3; ++p){
        for(int *q = *p; q != *p + 4; ++q){
            std::cout << *q << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}