## 模板特化（Template Specialization）

模板特化允许开发者为特定类型或类型组合提供专门的实现。当通用模板无法满足特定需求时，特化模板可以调整行为以处理特定的情况。C++ 支持**全特化（Full Specialization）\**和**偏特化（Partial Specialization）**，但需要注意的是，**函数模板不支持偏特化**，只能进行全特化。

### 全特化（Full Specialization）

全特化是针对模板参数的完全特定类型组合。它提供了模板的一个特定版本，当模板参数完全匹配特化类型时，编译器将优先使用该特化版本。

#### 语法

```cpp
// 通用模板
template <typename T>
class MyClass {
    // 通用实现
};

// 全特化
template <>
class MyClass<SpecificType> {
    // 针对 SpecificType 的实现
};
```

#### 示例：类模板全特化

```cpp
#include <iostream>
#include <string>

// 通用类模板
template <typename T>
class Printer {
public:
    void print(const T& value) {
        std::cout << "General Printer: " << value << std::endl;
    }
};

// 类模板全特化
template <>
class Printer<std::string> {
public:
    void print(const std::string& value) {
        std::cout << "String Printer: " << value << std::endl;
    }
};

int main() {
    Printer<int> intPrinter;
    intPrinter.print(100); // 输出：General Printer: 100

    Printer<std::string> stringPrinter;
    stringPrinter.print("Hello, World!"); // 输出：String Printer: Hello, World!

    return 0;
}
```

**输出：**

```yaml
General Printer: 100
String Printer: Hello, World!
```

#### 解析

- **通用模板**适用于所有类型，在`print`函数中以通用方式输出值。
- **全特化模板**针对`std::string`类型进行了专门化，实现了不同的`print`函数。
- 当实例化`Printer<std::string>`时，编译器选择全特化版本而非通用模板。

### 偏特化（Partial Specialization）

偏特化允许模板对部分参数进行特定类型的处理，同时保持其他参数的通用性。对于**类模板**而言，可以针对模板参数的某些特性进行偏特化；对于**函数模板**，则仅支持全特化，不支持偏特化。

#### 语法

```cpp
// 通用模板
template <typename T, typename U>
class MyClass {
    // 通用实现
};

// 偏特化：当 U 是指针类型时
template <typename T, typename U>
class MyClass<T, U*> {
    // 针对 U* 的实现
};
```

#### 示例：类模板偏特化

```cpp
#include <iostream>
#include <string>

// 通用 Pair 类模板
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

// 类模板偏特化：当第二个类型是指针时
template <typename T, typename U>
class Pair<T, U*> {
public:
    T first;
    U* second;

    Pair(T a, U* b) : first(a), second(b) {}

    void print() const {
        std::cout << "Pair with pointer: " << first << ", " << *second << std::endl;
    }
};

int main() {
    Pair<int, double> p1(1, 2.5);
    p1.print(); // 输出：Pair: 1, 2.5

    double value = 3.14;
    Pair<std::string, double*> p2("Pi", &value);
    p2.print(); // 输出：Pair with pointer: Pi, 3.14

    return 0;
}
```

**输出：**

```vbnet
Pair: 1, 2.5
Pair with pointer: Pi, 3.14
```

#### 解析

- **通用模板**处理非指针类型对。
- **偏特化模板**处理第二个类型为指针的情况，打印指针指向的值。
- 使用偏特化提升了模板的灵活性，使其能够根据部分参数类型进行不同处理。

### 函数模板的特化

与类模板不同，**函数模板不支持偏特化**，只能进行全特化。当对函数模板进行全特化时，需要显式指定类型。

#### 示例：函数模板全特化

```cpp
#include <iostream>
#include <string>

// 通用函数模板
template <typename T>
void printValue(const T& value) {
    std::cout << "General print: " << value << std::endl;
}

// 函数模板全特化
template <>
void printValue<std::string>(const std::string& value) {
    std::cout << "Specialized print for std::string: " << value << std::endl;
}

int main() {
    printValue(42); // 调用通用模板，输出：General print: 42
    printValue(3.14); // 调用通用模板，输出：General print: 3.14
    printValue(std::string("Hello")); // 调用全特化模板，输出：Specialized print for std::string: Hello
    return 0;
}
```

**输出：**

```go
General print: 42
General print: 3.14
Specialized print for std::string: Hello
```

#### 解析

- **通用函数模板**适用于所有类型，提供通用的`printValue`实现。
- **全特化函数模板**专门处理`std::string`类型，提供不同的输出格式。
- 调用`printValue`时，编译器根据实参类型选择适当的模板版本。

#### 注意事项

- **优先级**：全特化版本的优先级高于通用模板，因此当特化条件满足时，总是选择特化版本。
- **显式指定类型**：函数模板特化需要在调用时显式指定类型，或者确保类型推导可以正确匹配特化版本。
- **不支持偏特化**：无法通过偏特化对函数模板进行部分特化，需要通过其他方法（如重载）实现类似功能。

### 总结

- **全特化**适用于为具体类型或类型组合提供专门实现，适用于类模板和函数模板。
- **偏特化**仅适用于类模板，允许针对部分参数进行特定处理，同时保持其他参数的通用性。
- **函数模板**仅支持全特化，不支持偏特化；类模板支持全特化和偏特化。
- **特化模板**提升了模板的灵活性和适应性，使其能够根据不同类型需求调整行为。

------

## 变参模板（Variadic Templates）

变参模板允许模板接受可变数量的参数，提供极高的灵活性，是实现诸如 `std::tuple`、`std::variant` 等模板库组件的基础。

### 定义与语法

变参模板使用 **参数包（Parameter Pack）**，通过 `...` 语法来表示。

**语法：**

```cpp
template <typename... Args>
class MyClass { /* ... */ };

template <typename T, typename... Args>
void myFunction(T first, Args... args) { /* ... */ }
```

### 递归与展开（Recursion and Expansion）

变参模板通常与递归相结合，通过递归地处理参数包，或者使用 **折叠表达式（Fold Expressions）** 来展开发参数包。

**递归示例：打印所有参数**

```cpp
#include <iostream>

// 基础情况：无参数
void printAll() {
    std::cout << std::endl;
}

// 递归情况：至少一个参数
template <typename T, typename... Args>
void printAll(const T& first, const Args&... args) {
    std::cout << first << " ";
    printAll(args...); // 递归调用
}

int main() {
    printAll(1, 2.5, "Hello", 'A'); // 输出：1 2.5 Hello A 
    return 0;
}
```

**输出：**

```css
1 2.5 Hello A
```

**折叠表达式版本**

```cpp
#include <iostream>

// 使用折叠表达式的printAll
template <typename... Args>
void printAll(const Args&... args) {
    // 使用左折叠展开参数包，并在每个参数之后输出一个空格
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}

int main() {
    printAll(1, 2.5, "Hello", 'A'); // 输出：1 2.5 Hello A 
    return 0;
}
```

**折叠表达式示例：计算总和**

C++17 引入了折叠表达式，简化了参数包的处理。

```cpp
#include <iostream>

template <typename... Args>
auto sum(Args... args) -> decltype((args + ...)) {
    return (args + ...); // 左折叠
}

int main() {
    std::cout << sum(1, 2, 3, 4) << std::endl; // 输出：10
    std::cout << sum(1.5, 2.5, 3.0) << std::endl; // 输出：7
    return 0;
}
```

**输出：**

```undefined
10
7
```

### 应用示例

**示例：日志记录器**

```cpp
#include <iostream>
#include <string>

// 基础情况：无参数
void log(const std::string& msg) {
    std::cout << msg << std::endl;
}

// 递归情况：至少一个参数
template <typename T, typename... Args>
void log(const std::string& msg, const T& first, const Args&... args) {
    std::cout << msg << ": " << first << " ";
    log("", args...); // 递归调用，省略消息前缀
}

int main() {
    log("Error", 404, "Not Found");
    // 输出：Error: 404 Not Found 

    log("Sum", 10, 20, 30);
    // 输出：Sum: 10 20 30 
    return 0;
}
```

**输出：**

```makefile
Error: 404 Not Found 
Sum: 10 20 30
```

**要点：**

- 变参模板极大地提升了模板的灵活性。
- 使用递归或折叠表达式处理参数包。
- 常用于实现通用函数、容器类和元编程工具。