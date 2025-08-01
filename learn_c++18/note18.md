## 1. 函数简介

### 定义

函数是执行特定任务的代码块，可以被程序中的多个地方调用。使用函数可以增加代码的可重用性、可读性和可维护性。

### 功能

- **封装**：将特定功能封装在函数中，便于管理和修改。
- **复用**：同一段功能代码可以在程序中多次调用，减少代码重复。
- **结构化**：通过函数组织代码，提高程序的结构清晰度。

### 基本语法

```cpp
return_type function_name(parameter_list) {
    // function body
}
```

**示例**：

```cpp
#include <iostream>

// 函数声明
int add(int a, int b);

int main() {
    int result = add(5, 3);
    std::cout << "5 + 3 = " << result << std::endl;
    return 0;
}

// 函数定义
int add(int a, int b) {
    return a + b;
}
```

**输出**：

```undefined
5 + 3 = 8
```

------

## 2. 函数的声明与定义

### 函数声明（Function Declaration）

告诉编译器函数的名称、返回类型和参数类型，但不包含函数体。通常放在头文件中或在使用函数前进行声明。

**语法**：

```cpp
return_type function_name(parameter_list);
```

**示例**：

```cpp
int multiply(int a, int b); // 函数声明
```

### 函数定义（Function Definition）

提供函数的具体实现，包括函数体。函数定义可以在源文件中或与声明一起在头文件中出现（推荐仅声明在头文件中）。

**语法**：

```cpp
return_type function_name(parameter_list) {
    // function body
}
```

**示例**：

```cpp
int multiply(int a, int b) { // 函数定义
    return a * b;
}
```

### 函数分离编译

- **声明**：放在头文件（如 `multiply.h`）。
- **定义**：放在源文件（如 `multiply.cpp`）。

**multiply.h**:

```cpp
#ifndef MULTIPLY_H
#define MULTIPLY_H

int multiply(int a, int b);

#endif
```

**multiply.cpp**:

```cpp
#include "multiply.h"

int multiply(int a, int b) {
    return a * b;
}
```

**main.cpp**:

```cpp
#include <iostream>
#include "multiply.h"

int main() {
    int result = multiply(4, 6);
    std::cout << "4 * 6 = " << result << std::endl;
    return 0;
}
```

**编译命令**（假设使用g++）：

```bash
g++ main.cpp multiply.cpp -o program
```

**输出**：

```undefined
4 * 6 = 24
```

------

## 3. 函数调用

### 基本调用

通过函数名称和必要的参数来调用函数。

**示例**：

```cpp
#include <iostream>

void greet() {
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    greet(); // 调用函数
    return 0;
}
```

**输出**：

```undefined
Hello, World!
```

### 多次调用

同一函数可以在程序中被调用多次。

**示例**：

```cpp
#include <iostream>

void sayHello() {
    std::cout << "Hello!" << std::endl;
}

int main() {
    sayHello();
    sayHello();
    sayHello();
    return 0;
}
```

**输出**：

```undefined
Hello!
Hello!
Hello!
```

------

## 4. 参数传递机制

C++中函数参数的传递方式主要有以下三种：

1. **传值调用（Pass by Value）**
2. **传引用调用（Pass by Reference）**
3. **传指针调用（Pass by Pointer）**

### 传值调用

**定义**：函数接收参数的副本，函数内对参数的修改不会影响原始数据。

**语法**：

```cpp
void function_name(int a) {
    a = 10; // 只修改副本
}
```

**示例**：

```cpp
#include <iostream>

void changeValue(int num) {
    num = 100;
    std::cout << "Inside function: " << num << std::endl;
}

int main() {
    int value = 50;
    changeValue(value);
    std::cout << "Outside function: " << value << std::endl;
    return 0;
}
```

**输出**：

```bash
Inside function: 100
Outside function: 50
```

**解释**：`changeValue`函数修改的是`num`的副本，原始变量`value`保持不变。

### 传引用调用

**定义**：函数接收参数的引用，函数内对参数的修改会影响原始数据。

**语法**：

```cpp
void function_name(int &a) {
    a = 10; // 修改原始数据
}
```

**示例**：

```cpp
#include <iostream>

void changeValue(int &num) {
    num = 100;
    std::cout << "Inside function: " << num << std::endl;
}

int main() {
    int value = 50;
    changeValue(value);
    std::cout << "Outside function: " << value << std::endl;
    return 0;
}
```

**输出**：

```bash
Inside function: 100
Outside function: 100
```

**解释**：`changeValue`函数通过引用修改了原始变量`value`的值。

### 传指针调用

**定义**：函数接收指向参数的指针，函数内通过指针可以修改原始数据。

**语法**：

```cpp
void function_name(int *a) {
    *a = 10; // 修改原始数据
}
```

**示例**：

```cpp
#include <iostream>

void changeValue(int *num) {
    *num = 100;
    std::cout << "Inside function: " << *num << std::endl;
}

int main() {
    int value = 50;
    changeValue(&value);
    std::cout << "Outside function: " << value << std::endl;
    return 0;
}
```

**输出**：

```bash
Inside function: 100
Outside function: 100
```

**解释**：`changeValue`函数通过指针修改了原始变量`value`的值。

### 选择合适的传递方式

- **传值调用**：适用于不需要修改原始数据且数据量较小的情况。
- **传引用调用**：适用于需要修改原始数据或传递大型数据结构以提高效率。
- **传指针调用**：类似传引用调用，但更灵活，可用于传递`nullptr`或指向动态分配的内存。

------

## 5. 返回值

函数可以通过`return`语句将结果返回给调用者。返回值的类型可以是基本数据类型、引用、指针、对象等。

### 5.1 返回基本数据类型

**示例**：

```cpp
#include <iostream>

int add(int a, int b) {
    return a + b;
}

int main() {
    int sum = add(3, 4);
    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
```

**输出**：

```makefile
Sum: 7
```

### 5.2 返回引用

**注意**：返回引用需要确保引用的对象在返回后依然有效（避免悬垂引用）。

**示例**：

```cpp
#include <iostream>

int& getMax(int &a, int &b) {
    if(a > b)
        return a;
    else
        return b;
}

int main() {
    int x = 10;
    int y = 20;
    int &max = getMax(x, y);
    std::cout << "Max: " << max << std::endl;
    max = 30; // 修改引用
    std::cout << "After modification, y: " << y << std::endl;
    return 0;
}
```

**输出**：

```yaml
Max: 20
After modification, y: 30
```

**解释**：`getMax`函数返回较大的变量的引用，修改`max`实际上修改了`y`。

### 5.3 返回指针

**示例**：

```cpp
#include <iostream>

int* allocateArray(int size) {
    int* arr = new int[size];
    for(int i = 0; i < size; ++i)
        arr[i] = i * 2;
    return arr;
}

int main() {
    int size = 5;
    int* myArray = allocateArray(size);
    for(int i = 0; i < size; ++i)
        std::cout << myArray[i] << " ";
    std::cout << std::endl;
    delete[] myArray; // 释放内存
    return 0;
}
```

**输出**：

```undefined
0 2 4 6 8
```

**解释**：`allocateArray`函数动态分配一个数组并返回指向数组的指针。调用者需负责释放内存。

### 5.4 返回对象

**示例**：

```cpp
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;

    Person(std::string n, int a) : name(n), age(a) {}
};

Person createPerson(std::string name, int age) {
    Person p(name, age);
    return p; // 返回对象
}

int main() {
    Person person = createPerson("Alice", 25);
    std::cout << "Name: " << person.name << ", Age: " << person.age << std::endl;
    return 0;
}
```

**输出**：

```yaml
Name: Alice, Age: 25
```

**解释**：`createPerson`函数返回一个`Person`对象。现代编译器通过返回值优化（RVO）减少对象拷贝，提高效率。

------

## 6. 函数重载

### 定义

函数重载允许在同一个作用域内定义多个名称相同但参数列表不同的函数。编译器通过参数列表的不同来区分调用哪个函数。

### 规则

- 函数名相同。
- 参数列表（类型、数量或顺序）不同。
- 返回类型不参与重载的区分。

### 示例

```cpp
#include <iostream>

// 重载函数：不同参数数量
int add(int a, int b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

// 重载函数：不同参数类型
double add(double a, double b) {
    return a + b;
}

int main() {
    std::cout << "add(2, 3) = " << add(2, 3) << std::endl;
    std::cout << "add(2, 3, 4) = " << add(2, 3, 4) << std::endl;
    std::cout << "add(2.5, 3.5) = " << add(2.5, 3.5) << std::endl;
    return 0;
}
```

**输出**：

```csharp
add(2, 3) = 5
add(2, 3, 4) = 9
add(2.5, 3.5) = 6
```

### 注意事项

- 仅返回类型不同的重载是非法的。
- 默认参数可能会与重载产生冲突，使用时需谨慎。

**非法示例**：

```cpp
double add(int a, int b) {
    return a + b + 0.0;
}

// 冲突重载，仅返回类型不同
// 会导致编译错误
// double add(int a, int b);
```

------

## 7. 默认参数

### 定义

函数参数可以指定默认值，调用函数时可以省略这些参数，默认值将被使用。

### 规则

- 默认参数从右到左设置，不能部分设置。
- 函数声明和定义中默认参数只需在声明中指定。

### 示例

```cpp
#include <iostream>

// 函数声明时指定默认参数
void displayInfo(std::string name, int age = 18, std::string city = "Unknown");

int main() {
    displayInfo("Bob", 25, "New York"); // 全部参数传递
    displayInfo("Charlie", 30);         // 省略city
    displayInfo("Diana");               // 省略age和city
    return 0;
}

// 函数定义
void displayInfo(std::string name, int age, std::string city) {
    std::cout << "Name: " << name 
              << ", Age: " << age 
              << ", City: " << city << std::endl;
}
```

**输出**：

```yaml
Name: Bob, Age: 25, City: New York
Name: Charlie, Age: 30, City: Unknown
Name: Diana, Age: 18, City: Unknown
```

### 注意事项

- 默认参数必须从右端开始，不能跳过中间参数。
- 如果同时使用默认参数和重载，可能会产生歧义，需谨慎设计。

------

## 8. 内联函数

### 定义

内联函数通过在函数前加`inline`关键字，建议编译器将函数代码嵌入到调用处，减少函数调用的开销。

### 使用场景

适用于函数体积小、调用频繁的函数，如访问器（getter）和修改器（setter）等。

### 示例

```cpp
#include <iostream>

// 内联函数
inline int square(int x) {
    return x * x;
}

int main() {
    std::cout << "Square of 5: " << square(5) << std::endl;
    return 0;
}
```

**输出**：

```scss
Square of 5: 25
```

### 优点

- 减少函数调用的开销（如栈操作）。
- 可能提高程序性能。

### 缺点

- 使得代码体积增大，可能影响缓存性能。
- 编译器可能忽略内联请求，特别是对于复杂函数。

### 注意事项

- 编译器对`inline`关键字的处理是建议性质，最终是否内联由编译器决定。
- 过度使用内联函数可能导致代码膨胀。

------

## 9. 递归函数

### 定义

递归函数是指在函数体内调用自身的函数。递归通常用于解决可以分解为相似子问题的问题，如阶乘、斐波那契数列、树的遍历等。

### 基本结构

递归函数通常包含两个部分：

1. **基准情形（Base Case）**：直接返回结果，避免无限递归。
2. **递归情形（Recursive Case）**：将问题分解为更小的子问题并调用自身。

### 示例：计算阶乘

```cpp
#include <iostream>

// 递归函数计算阶乘
long long factorial(int n) {
    if(n < 0)
        return -1; // 错误情况
    if(n == 0 || n == 1)
        return 1; // 基准情形
    return n * factorial(n - 1); // 递归情形
}

int main() {
    int number = 5;
    long long result = factorial(number);
    if(result != -1)
        std::cout << number << "! = " << result << std::endl;
    else
        std::cout << "Invalid input!" << std::endl;
    return 0;
}
```

**输出**：

```undefined
5! = 120
```

### 示例：斐波那契数列

```cpp
#include <iostream>

// 递归函数计算斐波那契数
int fibonacci(int n) {
    if(n <= 0)
        return 0;
    if(n == 1)
        return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int term = 10;
    std::cout << "Fibonacci(" << term << ") = " << fibonacci(term) << std::endl;
    return 0;
}
```

**输出**：

```undefined
Fibonacci(10) = 55
```

### 注意事项

- **基准情形**：必须正确设置，避免无限递归导致栈溢出（Stack Overflow）。
- **效率问题**：一些递归实现可能效率低下（如斐波那契数列），可以通过“记忆化”或改用迭代方法优化。
- **堆栈深度**：递归深度过大可能导致栈溢出，需避免深度递归。

### 递归优化：尾递归

尾递归是指递归调用在函数的最后一步，可以被编译器优化为循环，减少堆栈消耗。

**示例：尾递归阶乘**

```cpp
#include <iostream>

// 辅助函数，用于尾递归
long long factorialHelper(int n, long long accumulator) {
    if(n == 0)
        return accumulator;
    return factorialHelper(n - 1, n * accumulator);
}

// 尾递归函数
long long factorial(int n) {
    return factorialHelper(n, 1);
}

int main() {
    int number = 5;
    std::cout << number << "! = " << factorial(number) << std::endl;
    return 0;
}
```

**输出**：

```undefined
5! = 120
```

**解释**：`factorialHelper`函数的递归调用是函数的最后一步，编译器可以将其优化为迭代，减少堆栈消耗。

------



## 10. Lambda表达式

### 定义

Lambda表达式是C++11引入的匿名函数，便于在需要函数对象的地方快速定义和使用函数。它允许定义内联的、小型的可调用对象，无需单独定义函数。

### 语法

```cpp
[ capture_list ] ( parameter_list ) -> return_type {
    // function body
}
```

### 示例

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用Lambda表达式打印每个元素
    std::for_each(numbers.begin(), numbers.end(), [](int x) {
        std::cout << x << " ";
    });
    std::cout << std::endl;

    // 使用Lambda表达式计算总和
    int sum = 0;
    std::for_each(numbers.begin(), numbers.end(), [&sum](int x) {
        sum += x;
    });
    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
```

**输出**：

```makefile
1 2 3 4 5 
Sum: 15
```

### 组件说明

1. 捕获列表（Capture List）

   ：指定如何访问外部变量。

   - `[ ]`：不捕获任何外部变量。
   - `[&]`：按引用捕获所有外部变量。
   - `[=]`：按值捕获所有外部变量。
   - `[x, &y]`：按值捕获`x`，按引用捕获`y`。

2. **参数列表（Parameter List）**：类似普通函数的参数列表，可以省略类型（C++14及以上支持自动类型推断）。

3. **返回类型（Return Type）**：可指定返回类型，也可省略，编译器自动推断。

4. **函数体（Function Body）**：Lambda的具体实现。

### 高级示例：捕获并排序

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> data = {5, 2, 9, 1, 5, 6};

    // 按降序排序，使用Lambda表达式
    std::sort(data.begin(), data.end(), [](int a, int b) -> bool {
        return a > b;
    });

    std::cout << "Sorted data: ";
    for(auto num : data)
        std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}
```

**输出**：

```kotlin
Sorted data: 9 6 5 5 2 1
```

### 使用Lambda表达式与标准库

C++标准库中的许多算法（如`std::for_each`、`std::sort`、`std::transform`等）常用Lambda表达式作为参数，以实现自定义的操作。

------

## 11. 函数指针与回调函数

### 函数指针

**定义**：指向函数的指针变量，保存函数的地址，可以通过指针调用函数。

### 声明与使用

```cpp
#include <iostream>

// 普通函数
void greet() {
    std::cout << "Hello from greet!" << std::endl;
}

int main() {
    // 定义函数指针
    void (*funcPtr)() = greet;

    // 通过指针调用函数
    funcPtr();

    return 0;
}
```

**输出**：

```csharp
Hello from greet!
```

### 函数指针作为参数

**示例**：

```cpp
#include <iostream>

// 高阶函数，接受函数指针作为参数
void execute(void (*func)()) {
    func(); // 调用传入的函数
}

// 被调用的函数
void sayHi() {
    std::cout << "Hi!" << std::endl;
}

int main() {
    execute(sayHi);
    return 0;
}
```

**输出**：

```undefined
Hi!
```

### 回调函数

**定义**：通过函数指针传递的函数，通常用于在特定事件发生时执行自定义操作。

**示例**：基于函数指针的回调

```cpp
#include <iostream>

// 回调类型定义
typedef void (*Callback)();

// 函数接收回调
void registerCallback(Callback cb) {
    std::cout << "Before callback" << std::endl;
    cb(); // 执行回调
    std::cout << "After callback" << std::endl;
}

// 回调函数
void myCallback() {
    std::cout << "Callback executed!" << std::endl;
}

int main() {
    registerCallback(myCallback);
    return 0;
}
```

**输出**：

```undefined
Before callback
Callback executed!
After callback
```

### 与Lambda表达式结合

函数指针也可以指向Lambda表达式，但仅限于不捕获外部变量的Lambda。

**示例**：

```cpp
#include <iostream>

// 回调类型定义
typedef void (*Callback)();

void executeCallback(Callback cb) {
    cb();
}

int main() {
    // 不捕获外部变量的Lambda
    Callback cb = []() {
        std::cout << "Lambda callback!" << std::endl;
    };

    executeCallback(cb);
    return 0;
}
```

**输出**：

```undefined
Lambda callback!
```

**注意**：捕获外部变量的Lambda无法转换为普通函数指针。

------

## 12. 总结与练习

### 课程总结

- **函数的基本概念**：了解函数的作用、基本结构及使用方法。
- **函数声明与定义**：掌握在头文件和源文件中分离声明与定义的方法。
- **参数传递机制**：理解传值、传引用和传指针的区别及应用场景。
- **返回值**：学习不同类型的返回值及其使用方法。
- **函数重载**：掌握函数名相同但参数不同的重载机制。
- **默认参数**：学习设定和使用函数的默认参数。
- **内联函数**：了解内联函数的概念、优缺点及使用场景。
- **递归函数**：理解递归的基本原理、编写方法及优化技巧。
- **Lambda表达式**：掌握定义和使用Lambda表达式的方法，及其在标准库中的应用。
- **函数指针与回调函数**：了解函数指针的声明、使用以及如何实现回调机制。