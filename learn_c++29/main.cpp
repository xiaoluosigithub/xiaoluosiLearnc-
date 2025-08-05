//
// Created by lyx on 2025/8/5.
//
#include <iostream>
#include <map>
#include <string>

int main(){
    std::map<int, std::string> my_map = {
            {1, "apple"},
            {20,"banana"},
            {3,"orange"},
    };
    for(auto & x : my_map){
        std::cout << x.first << " " << x.second << std::endl;
    }

    my_map.insert(std::pair<int, std::string>(56, "peach"));
    my_map.insert(std::make_pair(44, "pear"));
    my_map.insert({104, "grape"});
    my_map[104] = "blackberry";

    auto fruit = my_map[104];
    std::cout << fruit << std::endl;


    std::cout << "-----------------" << std::endl;
    for(auto it = my_map.begin(); it != my_map.end(); ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }

    my_map.erase(3);

    auto it = my_map.find(20);
    if(it != my_map.end()){
        my_map.erase(it);
    }else{
        std::cout << "not found" << std::endl;
    }

    std::cout << "****************" << std::endl;
    for(auto it = my_map.begin(); it != my_map.end(); ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }

    auto beg = my_map.find(56);
    my_map.erase(my_map.begin(), beg);

    std::cout << "****************" << std::endl;
    for(auto it = my_map.begin(); it != my_map.end(); ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }
    std::cout << "****************" << std::endl;

    my_map.clear();
    std::cout << my_map.size() << std::endl;

    return 0;
}