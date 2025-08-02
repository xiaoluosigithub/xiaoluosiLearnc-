//
// Created by lyx on 2025/7/31.
//
#include <iostream>
#include <vector>

void demo1(){
    std::vector<int> numbers;
    int num;

    std::cout << "请输入一组整数 -1结束" << std::endl;
    while(std::cin >> num && num != -1){
        numbers.push_back(num);
    }

    std::cout << "相邻元素和: " << std::endl;
    for(auto it = numbers.begin(); it + 1 != numbers.end(); ++it){
        std::cout << *it + *(it + 1) << " ";
    }
    std::cout << std::endl;;
}

void demo2(){
    std::vector<int> numbers;
    int input;
    std::cout << "请输入一组整数 -1结束" << std::endl;
    while(std::cin >> input && input != -1){
        numbers.push_back(input);
    }
    std::cout << "反向打印结果：";
    for(std::vector<int>::reverse_iterator it = numbers.rbegin(); it != numbers.rend(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void demo3(){
    std::vector<int> vector1, vector2, mergedVector;
    int input;
    std::cout << "请输入第一组整数 -1结束" << std::endl;
    while(std::cin >> input && input != -1){vector1.push_back(input);}
    std::cout << "请输入第二组整数 -1结束" << std::endl;
    while(std::cin >> input && input != -1){vector2.push_back(input);}

    // 合并两个向量
    mergedVector.insert(mergedVector.end(), vector1.begin(), vector1.end());
    mergedVector.insert(mergedVector.end(), vector2.begin(), vector2.end());

    std::cout << "合并后的向量是：" << std::endl;
    for(std::vector<int>::iterator it = mergedVector.begin(); it != mergedVector.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}


int main(){
    system("chcp 65001");
    // demo1();
    // demo2();
    // demo3();
    return 0;
}