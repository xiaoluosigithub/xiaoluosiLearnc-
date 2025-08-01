//
// Created by lyx on 2025/8/1.
//
#include <iostream>
#include <vector>
#include <functional>

// 定义带参数的回调函数类型
using Callback = std::function<void(int)>;

// 事件系统类
class EventSystem{
private:
    std::vector<Callback> callbacks;

public:
    // 注册回调函数值
    void registerCallback(const Callback &cb){
        callbacks.push_back(cb);
    }

    // 触发事件，传递参数给回调函数
    void triggerEvent(int data){
        std::cout << "Event triggered with data = " << data << ". Executing callbacks..." << std::endl;
        for(auto &cb : callbacks){
            cb(data);
        }
    }
};

// 示例函数作为回调
void onEvent(int data){
    std::cout << "Function callback received data: " << data << std::endl;
}

// 回调函数就是一个作为参数传递给其他函数，并且由那个函数在合适的时机调用的函数。
int main(){
    EventSystem eventSystem;

    // 注册基于函数指针的回调
    eventSystem.registerCallback(onEvent);

    // 注册基于Lambda表达式的回调
    eventSystem.registerCallback([](int x){
        std::cout << "Lambda callback received: " << x * 2 << std::endl;
    });

    // 注册带捕获的Lambda表达式的回调
    int multiplier = 5;
    eventSystem.registerCallback([multiplier](int x){
        std::cout << "Lambda with capture received: " << x * multiplier << std:: endl;
    });

    // 触发事件，传递参数
    eventSystem.triggerEvent(10);

    return 0;
}











