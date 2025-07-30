//
// Created by lyx on 2025/7/30.
//
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <algorithm>

int main() {
    system("chcp 65001");
    //默认构造函数 构造一个空串
    std::string str;
    std::string str2 = "Hello";
    std::string str3(str2);
    // 使用部分初始化
    std::string str4(str2, 0, 4);
    // 使用重复字符初始化
    std::string str5(5, 'a');
    std::cout << "str1 = " << str << std::endl;
    std::cout << "str2 = " << str2 << std::endl;
    std::cout << "str3 = " << str3 << std::endl;
    std::cout << "str4 = " << str4 << std::endl;
    std::cout << "str5 = " << str5 << std::endl;

    std::string input;
    std::cout << "请输入字符串：";
    // std::cin >> input;
    std::cout << "输入的字符串是：" << input << std::endl;

    // os 表示输出流对象

    std::string first = "Hello, ";
    std::string second = "World!";
    std::string combined = first + second;
    std::cout << combined << std::endl;

    std::string str1 = "Hello,";
    str1.append(" World!");
    std::cout << str1 << std::endl;

    str = "Data";
    str += " Structures";
    std::cout << str << std::endl;

    std::string aa = "apple";
    std::string bb = "Apple";
    if(aa < bb){
        std::cout << "aa < bb" << std::endl;
    }else if(aa > bb){
        std::cout << "aa > bb" << std::endl;
    }else if(aa == bb){
        std::cout << "aa == bb" << std::endl;
    }

    std::string text = "The quick brown fox jumps over the lazy dog.";
    std::string word = "fox";
    size_t pos = text.find(word);
    if (pos != std::string::npos) {
        std::cout << "Word found at position: " << pos << std::endl;
    } else {
        std::cout << "Word not found." << std::endl;
    }

    text = "I like cats.";
    std::string from = "cats";
    std::string to = "dogs";

    pos = text.find(from);
    if(pos != std::string::npos){
        text.replace(pos, from.length(), to);
        std::cout << "Replaced text: " << text << std::endl;
    } else {
        std::cout << "Word not found." << std::endl;
    }

    str = "Hello World!";
    std::string sub = str.substr(7, 5);
    std::cout << "Substring: " << sub << std::endl;

    std::cout << "字符串容量" << str.capacity() << std::endl;
    str += "abcd";
    std::cout << "字符串容量" << str.capacity() << std::endl;

    str = "ABCDE";
    std::cout << str[0] << std::endl;
    if(isupper(str[0])){
        std::cout << "大写字母" << std::endl;
    } else {
        std::cout << "小写字母" << std::endl;
    }

    for(size_t i = 0; i < str.length(); ++i){
        std::cout << "下标为" << i << "的字符是" << str[i] << std::endl;
    }



    try{
        //越界访问
        std::cout << str.at(100) << std::endl;
    }catch (const std::out_of_range e){
        std::cout << "越界访问" << std::endl;
    }

    str = "hello world";
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){return std::toupper(c);}
                   );
    std::cout << str << std::endl;

    for(auto iter = str.begin(); iter != str.end(); ++iter){
        *iter = std::tolower(*iter);
    }
    std::cout << str << std::endl;



    return 0;
}