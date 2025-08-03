## 引言

C++ 提供了多种方式来表示和操作可调用对象，包括传统的函数指针、仿函数（Functors）、Lambda表达式、`std::function` 和 `std::bind` 等。这些工具极大地增强了C++的灵活性和表达能力，尤其在处理回调、事件驱动编程和函数式编程时表现尤为出色。

## 函数指针

函数指针是C++中最基本的可调用对象之一，用于指向普通函数和静态成员函数。

### 定义与使用

函数指针的定义涉及到函数的返回类型和参数列表。例如，定义一个指向返回 `int` 且接受两个 `int` 参数的函数指针：

```cpp
// 定义函数指针类型
int (*funcPtr)(int, int);

// 定义一个普通函数
int add(int a, int b) {
    return a + b;
}

int main() {
    // 给函数指针赋值
    funcPtr = &add;

    // 调用函数
    int result = funcPtr(3, 4);
    std::cout << "结果: " << result << std::endl; // 输出: 结果: 7

    return 0;
}
```

### 优点与局限性

**优点:**

- 简单直观，适用于简单的回调函数。

**局限性:**

- 不能捕获上下文（如lambda中的闭包）。
- 语法相对复杂，尤其是指针的声明和使用。

------

## 仿函数（Functors）

**仿函数（Functors）**，又称**函数对象（Function Objects）**，是在C++中重载了 `operator()` 的类或结构体实例。仿函数不仅可以像普通函数一样被调用，还能携带状态，提供更大的灵活性和功能性。

### 定义与使用

仿函数是通过定义一个类或结构体，并重载其调用运算符 `operator()` 来实现的。

```cpp
#include <iostream>

// 定义一个仿函数类
struct Adder {
    int to_add;

    // 构造函数
    Adder(int value) : to_add(value) {}

    // 重载()运算符
    int operator()(int x) const {
        return x + to_add;
    }
};

int main() {
    Adder add5(5); // 创建一个添加5的仿函数

    std::cout << "10 + 5 = " << add5(10) << std::endl; // 输出: 10 + 5 = 15

    return 0;
}
```

### 特点

1. **携带状态：** 仿函数可以拥有内部状态，通过成员变量存储数据，使其在调用时具备上下文信息。
2. **灵活性高：** 可以根据需要添加更多的成员函数和变量，扩展功能。
3. **性能优化：** 编译器可以对仿函数进行优化，例如内联展开，提高执行效率。

### 高级示例

仿函数不仅可以执行简单的计算，还可以进行复杂的操作。例如，实现一个可变的仿函数，用于累加多个值。

```cpp
#include <iostream>

// 可变累加器仿函数
struct Accumulator {
    int sum;

    Accumulator() : sum(0) {}

    // 重载()运算符
    void operator()(int x) {
        sum += x;
    }
};

int main() {
    Accumulator acc;

    acc(10);
    acc(20);
    acc(30);

    std::cout << "总和: " << acc.sum << std::endl; // 输出: 总和: 60

    return 0;
}
```

### 使用仿函数的标准库算法

许多标准库算法可以接受仿函数作为参数，使得算法的行为更加灵活和可定制。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// 仿函数：判断一个数是否大于某个阈值
struct IsGreaterThan {
    int threshold;

    IsGreaterThan(int t) : threshold(t) {}

    bool operator()(int x) const {
        return x > threshold;
    }
};

int main() {
    std::vector<int> numbers = {1, 5, 10, 15, 20};

    // 使用仿函数进行筛选
    IsGreaterThan greaterThan10(10);
    auto it = std::find_if(numbers.begin(), numbers.end(), greaterThan10);

    if(it != numbers.end()) {
        std::cout << "第一个大于10的数是: " << *it << std::endl; // 输出: 第一个大于10的数是: 15
    } else {
        std::cout << "没有找到大于10的数。" << std::endl;
    }

    return 0;
}
```

### 仿函数与模板

仿函数与模板相结合，可以实现高度通用和可复用的代码。例如，编写一个通用的比较仿函数。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

// 通用比较仿函数
template <typename T>
struct Compare {
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

int main() {
    std::vector<int> numbers = {5, 2, 8, 1, 9};

    // 使用仿函数进行排序
    std::sort(numbers.begin(), numbers.end(), Compare<int>());

    std::cout << "排序后的数字: ";
    for(auto num : numbers) {
        std::cout << num << " "; // 输出: 1 2 5 8 9
    }
    std::cout << std::endl;

    return 0;
}
```

### 仿函数的优势

- **可扩展性：** 能够根据需要添加更多功能和状态。
- **与Lambda的互补性：** 在需要携带复杂状态或多次调用时，仿函数比Lambda更适合。
- **类型安全：** 仿函数是具体的类型，可以在编译期进行类型检查。

### 何时使用仿函数

- **需要携带状态时：** 当**回调函数需要维护内部状态时**，仿函数是理想选择。
- **复杂操作：** 当简单的函数指针或Lambda难以表达复杂逻辑时。
- **性能关键场景：** 由于仿函数可以被编译器优化，适用于性能敏感的代码。

------

## Lambda表达式

Lambda表达式是C++11引入的一种轻量级函数对象，允许在代码中定义匿名函数。它们可以捕获周围的变量，具有更强的表达能力。

### 基本语法

```cpp
[captures](parameters) -> return_type {
    // 函数体
}
```

- **captures**: 捕获外部变量的方式，可以是值捕获、引用捕获或者混合捕获。
- **parameters**: 参数列表。
- **return_type**: 返回类型，可以省略，编译器会自动推导。
- **函数体**: 实际执行的代码。

### 示例

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int threshold = 5;
    std::vector<int> numbers = {1, 6, 3, 8, 2, 7};

    // 使用lambda表达式进行过滤
    numbers.erase(std::remove_if(numbers.begin(), numbers.end(),
        [threshold](int n) -> bool {
            return n < threshold;
        }), numbers.end());

    // 输出结果
    for(auto n : numbers) {
        std::cout << n << " "; // 输出: 6 8 7
    }

    return 0;
}
```

### 捕获方式

1. **值捕获 (`[=]`)**: 捕获所有外部变量的副本。
2. **引用捕获 (`[&]`)**: 捕获所有外部变量的引用。
3. **混合捕获**: 指定部分变量按值捕获，部分按引用捕获，如 `[=, &var]` 或 `[&, var]`。
4. **无捕获 (`[]`)**: 不捕获任何外部变量。

### 可变Lambda

默认情况下，Lambda表达式是不可变的（`const`）。通过`mutable`关键字，可以允许修改捕获的变量副本。

```cpp
#include <iostream>

int main() {
    int count = 0;

    auto increment = [count]() mutable {
        count++;
        std::cout << "Count inside Lambda: " << count << std::endl;
    };

    increment(); // 输出: Count inside Lambda: 1
    increment(); // 输出: Count inside Lambda: 2

    std::cout << "Count outside Lambda: " << count << std::endl; // 输出: Count outside Lambda: 0

    return 0;
}
```

### 捕获成员函数和类变量

Lambda表达式可以捕获类的成员变量和成员函数，使其在类的上下文中更加灵活。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

class Processor {
public:
    Processor(int threshold) : threshold(threshold) {}

    void process(std::vector<int>& data) {
        std::cout << "处理前数据: ";
        for(auto num : data) std::cout << num << " ";
        std::cout << std::endl;

        // 使用Lambda表达式进行过滤
        data.erase(std::remove_if(data.begin(), data.end(),
            [this](int n) -> bool {
                return n < threshold;
            }), data.end());

        std::cout << "处理后数据: ";
        for(auto num : data) std::cout << num << " ";
        std::cout << std::endl;
    }

private:
    int threshold;
};

int main() {
    std::vector<int> numbers = {1, 6, 3, 8, 2, 7};
    Processor proc(5);
    proc.process(numbers);
    /*
    输出:
    处理前数据: 1 6 3 8 2 7 
    处理后数据: 6 8 7 
    */

    return 0;
}
```

### Lambda与标准库算法

Lambda表达式与标准库算法紧密结合，提供了更简洁和直观的代码书写方式。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {4, 2, 5, 1, 3};

    // 使用Lambda表达式进行排序
    std::sort(numbers.begin(), numbers.end(),
        [](int a, int b) -> bool {
            return a < b;
        });

    std::cout << "排序后的数字: ";
    for(auto num : numbers) {
        std::cout << num << " "; // 输出: 1 2 3 4 5
    }
    std::cout << std::endl;

    return 0;
}
```

### Lambda表达式的优势

- **简洁性：** 代码更加紧凑，易于理解。
- **灵活性：** 能够捕获外部变量，适应更多场景。
- **性能优化：** 编译器可以对Lambda进行优化，如内联展开。
- **与标准库的良好集成：** 与STL算法无缝结合，简化代码逻辑。

------

