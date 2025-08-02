//
// Created by lyx on 2025/8/1.
//
#include <iostream>


void demo1(){
    const int ROW = 2;
    const int COL = 3;
    int matrix1[ROW][COL];
    int matrix2[ROW][COL];
    int sum[ROW][COL];

    // 输入第一个矩阵
    std::cout << "请输入第一个2*3矩阵的元素 : " << std::endl;
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            std::cin >> matrix1[i][j];
        }
    }

    std::cout << "请输入第二个2*3矩阵的元素 : " << std::endl;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            std::cin >> matrix2[i][j];
        }
    }
    std::cout << "两个矩阵的和为 : " << std::endl;
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            std::cout << matrix1[i][j] + matrix2[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void demo2(){
    const int SIZE = 3;
    int matrix[SIZE][SIZE];
    int transpose[SIZE][SIZE];

    // 输入原始矩阵
    std::cout << "请输入3*3矩阵的元素 : " << std::endl;
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            std::cin >> matrix[i][j];

    for(int i = 0; i < SIZE; ++i){
        for(int j = i; j < SIZE; ++j){
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }

    // 输出转置矩阵
    std::cout << "转置矩阵为 : " << std::endl;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int main(){
    system("chcp 65001");
    demo1();
    demo2();

    return 0;
}