//
// Created by lyx on 2025/8/3.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <thread>

// 定义函数指针类型变量
int (* func_ptr)(int , int);

// 定义一个普通函数
int add(int a, int b){
    return a + b;
}

struct Adder{
    int to_add;
    Adder(int value) : to_add(value){}
    int operator()(int x){
        return x + to_add;
    }
    void add(int x, int y){
        std::cout << x + y << " ====" << std::endl;
    }
};

struct IsGreaterThan{
    int threshold;
    explicit IsGreaterThan(int value) : threshold(value){}
    bool operator()(int x) const{
        return x > threshold;
    }
};

template<typename T>
struct Compare{
    bool operator()(const T & a, const T & b){
        return a < b;
    }
};


class Processor{
public:
    Processor(int threshold) : _threshold(threshold){}

    void process(std::vector<int> & data){
        std::cout << "Before process data : " << std::endl;
        for(auto & it : data){
            std::cout << it << ' ';
        }
        std::cout << std::endl;
        auto new_end = std::remove_if(data.begin(), data.end(), [this](int n) -> bool{
            return n < _threshold;
        });
        data.erase(new_end,data.end());
        std::cout << "After process data : " << std::endl;
        for(auto & it : data){
            std::cout << it << ' ';
        }
        std::cout << std::endl;
    }

private:
    int _threshold;
};


int main(){
    // 函数指针指向函数
    //func_ptr = add;
    func_ptr = &add;

    //int result = func_ptr(1, 2);
    int result = (*func_ptr)(1, 2);
    std::cout << result << std::endl;

    Adder adder(5);
    std::cout << "adder(10) =" << adder(10) << std::endl;

    {
        std::cout << "-------------" << std::endl;
        IsGreaterThan isGreaterThan(10);
        std::vector<int> arr = {1, 5, 10, 15, 20, 25};
        auto it = std::find_if(arr.begin(), arr.end(), isGreaterThan);
        if (it != arr.end()) {
            std::cout << *it << " is greater than 10" << std::endl;
        } else {
            std::cout << "No element is greater than 10" << std::endl;
        }
        std::cout << "-------------" << std::endl;
    }

    {
        std::vector<int> arr = {2, 1, 3, 5, 4};
        Compare<int> cmp;
        std::sort(arr.begin(), arr.end(),cmp);
        for(auto it : arr){
            std::cout << it << ' ';
        }
        std::cout << std::endl;
        std::cout << "-------------" << std::endl;
    }

    {
        int thresold = 5;
        std::vector<int> num = {1, 6, 3, 8, 2, 7};
        auto new_end = std::remove_if(num.begin(), num.end(), [thresold](int x) -> bool{
           return x < thresold;
        });
        num.erase(new_end, num.end());
        for(auto & it : num){
            std::cout << it << ' ';
        }
        std::cout << "\n-------------" << std::endl;
    }

    {
        auto add_ptr = std::make_shared<Adder>(10);
        // 传入智能指针，即使当前局部变量被销毁，由于智能指针仍被使用，所指空间依然可以使用
        // 形成了闭包函数的作用
        auto lambda = [add_ptr](int x){
            std::cout << add_ptr.use_count() << std::endl;
        };
        std::thread t1(lambda, 5);
        t1.detach();
    }

    {
        std::cout << "\n=============\n";
        Processor pro(10);
        std::vector<int> arr = {1, 5, 10, 15, 20, 25};
        pro.process(arr);
        std::cout << "============\n";
    }

    return 0;
}