//
// Created by lyx on 2025/8/5.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include "MyMap.h"

int main(){
    MyMap<int, std::string> my_map;
    my_map.insert(150, "apple");
    my_map.insert(130, "banana");
    my_map.insert(170, "orange");
    my_map.insert(165, "peach");
    for(auto it = my_map.begin(); it != my_map.end(); ++it){
        std::cout << it->first << ": " << it->second << std::endl;
    }
    my_map.erase(150);
    my_map.insert(170, "apple");
    std::cout << "After erase:" << std::endl;
    for(auto it = my_map.begin(); it != my_map.end(); ++it){
        std::cout << it->first << ": " << it->second << std::endl;
    }
    my_map.clear();

    return 0;
}