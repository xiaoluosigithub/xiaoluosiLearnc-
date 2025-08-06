## 模板基础

C++ 模板（Templates）是现代 C++ 中强大而灵活的特性，支持泛型编程，使得代码更具复用性和类型安全性。模板不仅包括基本的函数模板和类模板，还涵盖了模板特化（全特化与偏特化）、模板参数种类、变参模板（Variadic Templates）、模板元编程（Template Metaprogramming）、SFINAE（Substitution Failure Is Not An Error）等高级内容。

### 函数模板

函数模板允许编写通用的函数，通过类型参数化，使其能够处理不同的数据类型。它通过模板参数定义与类型无关的函数。

**语法：**

```cpp
template <typename T>
T functionName(T param) {
    // 函数体
}
```

**示例：最大值函数**

```cpp
#include <iostream>

template <typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << maxValue(3, 7) << std::endl;         // int 类型
    std::cout << maxValue(3.14, 2.72) << std::endl;  // double 类型
    std::cout << maxValue('a', 'z') << std::endl;    // char 类型
    return 0;
}
```

**输出：**

```undefined
7
3.14
z
```

**要点：**

- **模板参数列表**以 `template <typename T>` 或 `template <class T>` 开头，两者等价。
- **类型推导**：编译器根据函数参数自动推导模板参数类型。

### 类模板

类模板允许定义通用的类，通过类型参数化，实现不同类型的对象。

**语法：**

```cpp
template <typename T>
class ClassName {
public:
    T memberVariable;
    // 构造函数、成员函数等
};
```

**示例：简单的 Pair 类**

```cpp
#include <iostream>
#include <string>

template <typename T, typename U>
class Pair {
public:
    T first;
    U second;

    Pair(T a, U b) : first(a), second(b) {}

    void print() const {
        std::cout << "Pair: " << first << ", " << second << std::endl;
    }
};

int main() {
    Pair<int, double> p1(1, 2.5);
    p1.print(); // 输出：Pair: 1, 2.5

    Pair<std::string, std::string> p2("Hello", "World");
    p2.print(); // 输出：Pair: Hello, World

    Pair<std::string, int> p3("Age", 30);
    p3.print(); // 输出：Pair: Age, 30

    return 0;
}
```

**输出：**

```makefile
Pair: 1, 2.5
Pair: Hello, World
Pair: Age, 30
```

**要点：**

- 类模板可以有多个类型参数。
- 模板参数可以被用于成员变量和成员函数中。
- 类模板实例化时指定具体类型，如 `Pair<int, double>`。

------

## 模板参数

模板参数决定了模板的泛用性与灵活性。C++ 模板参数种类主要包括类型参数、非类型参数和模板模板参数。

### 类型参数（Type Parameters）

类型参数用于表示任意类型，在模板实例化时被具体的类型替代。

**示例：**

```cpp
template <typename T>
class MyClass {
public:
    T data;
};
```

### 非类型参数（Non-Type Parameters）

非类型参数允许模板接受非类型的值，如整数、指针或引用。C++17 支持更多非类型参数类型，如 `auto`。

**语法：**

```cpp
template <typename T, int N>
class FixedArray {
public:
    T data[N];
};
```

**示例：固定大小的数组类**

```cpp
#include <iostream>

template <typename T, std::size_t N>
class FixedArray {
public:
    T data[N];

    T& operator[](std::size_t index) {
        return data[index];
    }

    void print() const {
        for(std::size_t i = 0; i < N; ++i)
            std::cout << data[i] << " ";
        std::cout << std::endl;
    }
};

int main() {
    FixedArray<int, 5> arr;
    for(int i = 0; i < 5; ++i)
        arr[i] = i * 10;
    arr.print(); // 输出：0 10 20 30 40 
    return 0;
}
```

**输出：**

```undefined
0 10 20 30 40
```

**注意事项：**

- 非类型参数必须是编译期常量。
- 允许的类型包括整型、枚举、指针、引用等，但不包括浮点数和类类型。

### 模板模板参数（Template Template Parameters）

模板模板参数允许模板接受另一个模板作为参数。这对于抽象容器和策略模式等场景非常有用。

**语法：**

```cpp
template <template <typename, typename> class Container>
class MyClass { /* ... */ };
```

**示例：容器适配器**

```cpp
#include <iostream>
#include <vector>
#include <list>

template <template <typename, typename> class Container, typename T>
class ContainerPrinter {
public:
    void print(const Container<T, std::allocator<T>>& container) {
        for(const auto& elem : container)
            std::cout << elem << " ";
        std::cout << std::endl;
    }
};

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<int> lst = {10, 20, 30};

    ContainerPrinter<std::vector, int> vecPrinter;
    vecPrinter.print(vec); // 输出：1 2 3 4 5 

    ContainerPrinter<std::list, int> listPrinter;
    listPrinter.print(lst); // 输出：10 20 30 

    return 0;
}
```

**输出：**

```undefined
1 2 3 4 5 
10 20 30
```

**要点：**

- 模板模板参数需要完全匹配被接受模板的参数列表。
- 可通过默认模板参数增强灵活性。

------