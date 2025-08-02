//
// Created by lyx on 2025/8/1.
//
#include <iostream>
#include <vector>
void demo1(){
    const int n = 10;
    for(int i = 1; i < n; ++i){
        for(int j = 1; j < n; ++j){
            std::cout << i << '*' << j << '=' << i*j << '\t';
        }
        std::cout << std::endl;
    }
}
void BubbleSort(std::vector<int> &arr, int size){
    std::cout << "Before Sort:" << std::endl;
    for(int i = 0; i < size; ++i){
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
    for(int i = 0; i < size; ++i){
        for(int j = i; j < size; ++j){
            if(arr[i] > arr[j]) std::swap(arr[i], arr[j]);
        }
    }
    std::cout << "After Sort:" << std::endl;
    for(int i = 0; i < size; ++i){
        std::cout << arr[i] << ' ';
    }
    std::cout << std::endl;
}


// 冒泡排序函数
void bubble_sort(int arr[], int n){
    bool swapped;
    for(int i = 0; i < n - 1; ++i){
        swapped = false;
        for(int j = 0; j < n - i - 1; ++j){
            if(arr[j] > arr[j + 1]){
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

void print_array(int arr[], int n){
    for(int i = 0; i < n; ++i){
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void demo2(){
    int n;
    std::cout << "Enter the size of the array: ";
    std::cin >> n;
    int *arr = new int[n];
    std::cout << "请输入" << n << "个数字：" << std::endl;
    for(int i = 0; i < n; ++i){
        std::cin >> arr[i];
    }
    std::cout << "排序前的数组:" << std::endl;
    print_array(arr, n);
    bubble_sort(arr, n);
    std::cout << "排序后的数组:" << std::endl;
    print_array(arr, n);
    delete[] arr;
}

void demo3(){
    std::cout << "请输入斐波那契数列的数量 : " << std::endl;
    int n;
    std::cin >> n;
    std::cout << "斐波那契数列:" << std::endl;
    int fir = 0, sec = 1;
    for(int i = 0; i < n; ++i){
        std::cout << fir << " ";
        int temp = fir;
        fir = sec;
        sec = temp + sec;
    }
    std::cout << "\n--------------" << std::endl;

}

int main(){
    system("chcp 65001");
    //demo1();
    //demo2();
    demo3();
    return 0;
}