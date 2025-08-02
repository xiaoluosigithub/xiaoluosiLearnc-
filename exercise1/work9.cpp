//
// Created by lyx on 2025/8/1.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
int main(){
    //system("chcp 65001");
    std::vector<std::string> vec;
    std::cout << "请输入多个字符串：" << std::endl;
    for(std::string str; std::cin >> str; ){
        vec.push_back(str);
    }
    std::sort(vec.begin(), vec.end(), [](std::string &s1, std::string &s2){
       return s1.size() < s2.size();
    });
    std::cout << "按长度排序后的结果为：" << std::endl;
    for(auto &s : vec){
        std::cout << s << std::endl;
    }

}