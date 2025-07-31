//
// Created by lyx on 2025/7/31.
//
#include <iostream>

// 自定义的字符串复制函数
char* my_strcpy(char* dest, const char* src) {
    // 在此实现函数逻辑
    char *p = dest;
    for(const char* i = src; *i != '\0'; i++, p++){
        *p = *i;
    }
    *p = '\0';
    return dest;
}

// 自定义的字符串连接函数
char* my_strcat(char* dest, const char* src) {
    // 在此实现函数逻辑
    char * ret = dest;
    while(*dest != '\0'){
        dest++;
    }
    for(const char* i = src; *i != '\0'; i++, dest++){
        *dest = *i;
    }
    *dest = '\0';
    return ret;
}

int main() {
    {
        const char* source = "Hello, World!";
        char destination[50]; // 确保目标有足够的空间

        my_strcpy(destination, source);

        std::cout << "Source: " << source << std::endl;
        std::cout << "Destination: " << destination << std::endl;
    }

    {
        char destination[100] = "Hello, "; // 初始内容
        const char* source = "World!";

        my_strcat(destination, source);

        std::cout << "After concatenation: " << destination << std::endl;
    }

    return 0;
}