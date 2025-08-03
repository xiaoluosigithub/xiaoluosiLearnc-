## `std::function` 对象

`std::function` 是C++11提供的一个通用的可调用包装器，能够封装任何可调用对象，包括普通函数、Lambda表达式、函数对象以及绑定表达式。它实现了类型擦除，使得不同类型的可调用对象可以通过统一的接口进行操作。

### 定义与使用

```cpp
#include <iostream>
#include <functional>

// 普通函数
int add(int a, int b) {
    return a + b;
}

// 函数对象
struct Multiply {
    int operator()(int a, int b) const {
        return a * b;
    }
};

int main() {
    // 封装普通函数
    std::function<int(int, int)> func1 = add;
    std::cout << "Add: " << func1(3, 4) << std::endl; // 输出: Add: 7

    // 封装Lambda表达式
    std::function<int(int, int)> func2 = [](int a, int b) -> int {
        return a - b;
    };
    std::cout << "Subtract: " << func2(10, 4) << std::endl; // 输出: Subtract: 6

    // 封装函数对象
    Multiply multiply;
    std::function<int(int, int)> func3 = multiply;
    std::cout << "Multiply: " << func3(3, 4) << std::endl; // 输出: Multiply: 12

    return 0;
}
```

### 特点

- **类型擦除：** 可以存储任何符合签名的可调用对象。
- **灵活性：** 支持动态改变存储的可调用对象。
- **性能开销：** 相比于直接使用函数指针或Lambda，`std::function` 可能带来一定的性能开销，尤其是在频繁调用时。

### 用法场景

- **回调函数的传递。**
- **事件处理系统。**
- **策略模式的实现。**

### 示例：回调机制

```cpp
#include <iostream>
#include <functional>

// 定义回调类型
using Callback = std::function<void(int)>;

// 触发事件的函数
void triggerEvent(Callback cb, int value) {
    // 事件发生，调用回调
    cb(value);
}

int main() {
    // 使用Lambda作为回调
    triggerEvent([](int x) {
        std::cout << "事件触发，值为: " << x << std::endl;
    }, 42); // 输出: 事件触发，值为: 42

    // 使用仿函数作为回调
    struct Printer {
        void operator()(int x) const {
            std::cout << "Printer打印值: " << x << std::endl;
        }
    } printer;

    triggerEvent(printer, 100); // 输出: Printer打印值: 100

    return 0;
}
```

### 存储和调用不同类型的可调用对象

`std::function` 可以在容器中存储各种不同类型的可调用对象，只要它们符合指定的签名。

```cpp
#include <iostream>
#include <functional>
#include <vector>

int add(int a, int b) {
    return a + b;
}

struct Multiply {
    int operator()(int a, int b) const {
        return a * b;
    }
};

int main() {
    std::vector<std::function<int(int, int)>> operations;

    // 添加不同类型的可调用对象
    operations.emplace_back(add); // 普通函数
    operations.emplace_back(Multiply()); // 仿函数
    operations.emplace_back([](int a, int b) -> int { return a - b; }); // Lambda

    // 执行所有操作
    for(auto& op : operations) {
        std::cout << op(10, 5) << " "; // 输出: 15 50 5
    }
    std::cout << std::endl;

    return 0;
}
```

------

## `std::bind` 操作

`std::bind` 是C++11中提供的一个函数适配器，用于绑定函数或可调用对象的部分参数，生成一个新的可调用对象。它允许提前固定某些参数，简化函数调用或适应接口需求。

### 基本用法

```cpp
#include <iostream>
#include <functional>

// 普通函数
int add(int a, int b) {
    return a + b;
}

int main() {
    // 绑定第一个参数为10，生成新的函数对象
    auto add10 = std::bind(add, 10, std::placeholders::_1);

    std::cout << "10 + 5 = " << add10(5) << std::endl; // 输出: 10 + 5 = 15

    return 0;
}
```

### 占位符 (`std::placeholders`)

`std::bind` 使用占位符来表示未绑定的参数，这些占位符决定了在生成的新函数对象中如何传递参数。

常用的占位符包括：

- `std::placeholders::_1`
- `std::placeholders::_2`
- `std::placeholders::_3`
- 等等，根据需要传递的参数数量。

### 示例

```cpp
#include <iostream>
#include <functional>

void display(const std::string& msg, int count) {
    for(int i = 0; i < count; ++i) {
        std::cout << msg << std::endl;
    }
}

int main() {
    // 绑定消息为"Hello"，生成新的函数对象，只需要传递次数
    auto sayHello = std::bind(display, "Hello", std::placeholders::_1);

    sayHello(3);
    /*
    输出:
    Hello
    Hello
    Hello
    */

    // 绑定次数为2，生成新的函数对象，只需要传递消息
    auto sayTwice = std::bind(display, std::placeholders::_1, 2);
    sayTwice("Hi");
    /*
    输出:
    Hi
    Hi
    */

    return 0;
}
```

### 与Lambda表达式的对比

`std::bind` 曾在C++11中广泛使用，但随着Lambda表达式的普及，很多情况下Lambda更为直观和高效。不过，在某些复杂的参数绑定场景下，`std::bind` 依然有其独特优势。

**使用 `std::bind`:**

```cpp
#include <iostream>
#include <functional>

int multiply(int a, int b) {
    return a * b;
}

int main() {
    // 绑定第一个参数为2，生成新的函数对象
    auto multiplyBy2 = std::bind(multiply, 2, std::placeholders::_1);

    std::cout << "2 * 5 = " << multiplyBy2(5) << std::endl; // 输出: 2 * 5 = 10

    return 0;
}
```

**使用 Lambda 表达式:**

```cpp
#include <iostream>
#include <functional>

int multiply(int a, int b) {
    return a * b;
}

int main() {
    // 使用Lambda表达式绑定第一个参数为2
    auto multiplyBy2 = [](int b) -> int {
        return multiply(2, b);
    };

    std::cout << "2 * 5 = " << multiplyBy2(5) << std::endl; // 输出: 2 * 5 = 10

    return 0;
}
```

**总结：**

- **可读性：** Lambda表达式通常更具可读性，语法更直观。
- **灵活性：** Lambda更易于捕获和使用外部变量。
- **性能：** Lambda通常比`std::bind`更高效，因为`std::bind`可能引入额外的间接层。

------