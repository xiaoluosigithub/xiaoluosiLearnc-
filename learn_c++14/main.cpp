//
// Created by lyx on 2025/7/30.
//

#include <iostream>
#include <cassert>
int main(){
    {
        int array[10] = {1,2,3,4,5,6,7,8,9,10};
        int(*ptr)[10] = & array;
        std::cout << (*ptr)[1] << std::endl;
        int (&ref_array)[10] = array;
        std::cout << ref_array[1] << std::endl;
    }

    {
        int array[10] = {1,2,3,4};
        for(size_t i = 0; i < sizeof array / sizeof array[0]; i++){
            std::cout << array[i] << ' ';
        }
        std::cout << std::endl;
    }

    {
        int array[10] = {1,2,3,4};
        std::cout << "first element : address is : " << &array[0] << std::endl;
        std::cout << "array address : " << array << std::endl;
        std::cout << "array address : " << &array << std::endl;
    }

    {
        int array[] = {1,2,3,4};
        //  将数组名字给到了一个指针，就相当于将数组第一个元素的地址给到了这个指针。
        int * first_addr = array;
        int * first_addr2 = &array[0];
        assert(first_addr == first_addr2);

    }

    {
        int array[] = {1,2,3,4};
        auto it2(array);
        decltype(array) it3 = {1,2,3,4};

    }

    {
        int array[10] = {1,2,3,4};
        int *p = array;
        ++p;
    }


    {
        int array[] = {1,2,3,4};
        int * p = array + 4;
        for(int *b = array; b != p; ++b){
            std::cout << *b << ' ';
        }
    }
    std::cout << std::endl;
    {
        int array[] = {1,2,3,4};
        int *beg = std::begin(array);
        int *end = std::end(array);
        for( ;beg != end; ++beg){
            std::cout << *beg << ' ';
        }
    }
    std::cout << std::endl;
    {
        constexpr int sz = 3;
        int array[sz] = {1,2,3};
        int *begin = array;
        int *last = array + 2;
        std::cout << *last << std::endl;
    }

    //std::cout << "Hello World!" << std::endl;
    return 0;
}