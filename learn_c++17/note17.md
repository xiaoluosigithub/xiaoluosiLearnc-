## 1. 简单语句

### 1.1 表达式语句

**描述**：在 C++ 中，最常见的简单语句是表达式语句。它由一个表达式组成，并以分号结束。表达式语句可以包括函数调用、赋值操作、增减操作等。

**示例代码**：

```cpp
#include <iostream>

int main() {
    int a = 5;          // 赋值表达式语句
    a = a + 10;         // 赋值表达式语句
    std::cout << a;     // 函数调用表达式语句
    return 0;           // return 表达式语句
}
```

**讲解**：

- `int a = 5;` 初始化变量 `a`，这是一个赋值表达式语句。
- `a = a + 10;` 更新变量 `a` 的值。
- `std::cout << a;` 调用了输出流对象的 `<<` 运算符函数。
- `return 0;` 从 `main`  函数返回，结束程序。

### 1.2 声明语句

**描述**：声明语句用于声明变量、函数、类等标识符。

**示例代码**：

```cpp
#include <iostream>

// 函数声明
int add(int x, int y);

int main() {
    int result = add(3, 4); // 调用函数
    std::cout << "Result: " << result;
    return 0;
}

// 函数定义
int add(int x, int y) {
    return x + y;
}
```

**讲解**：

- `int add(int x, int y);` 是一个函数声明语句。
- `int result = add(3, 4);` 在 `main` 中调用函数并声明变量。
- `int add(int x, int y) { ... }` 是函数定义，提供了函数的实现。

------

## 2. 语句作用域

### 2.1 作用域的基本概念

**描述**：作用域定义了变量或其他标识符在程序中的可见范围。C++ 中主要有以下几种作用域：

- **局部作用域 (Local Scope)**：在函数或代码块内部定义的变量，仅在其所在的块内可见。
- **全局作用域 (Global Scope)**：在所有函数外部定义的变量，在整个文件中可见。
- **命名空间作用域 (Namespace Scope)**：在命名空间内部定义的标识符。

### 2.2 代码示例

```cpp
#include <iostream>

// 全局变量
int globalVar = 10;

void display() {
    // 局部变量
    int localVar = 5;
    std::cout << "Inside display() - globalVar: " << globalVar << ", localVar: " << localVar << std::endl;
}

int main() {
    std::cout << "In main() - globalVar: " << globalVar << std::endl;
    // 局部变量
    int mainVar = 20;
    std::cout << "In main() - mainVar: " << mainVar << std::endl;

    display();

    // 尝试访问 display() 中的局部变量（将导致编译错误）
    // std::cout << localVar; // 错误：未定义标识符

    return 0;
}
```

**预期输出**：

```yaml
In main() - globalVar: 10
In main() - mainVar: 20
Inside display() - globalVar: 10, localVar: 5
```

**讲解**：

- `globalVar` 在所有函数中都可见。
- `mainVar` 仅在 `main` 函数内部可见。
- `localVar` 仅在 `display` 函数内部可见。
- 尝试在 `main` 中访问 `display` 函数的 `localVar` 将导致编译错误，因为它不在作用域内。

### 2.3 代码块作用域

**描述**：通过使用花括号 `{}`，可以创建新的代码块，从而定义局部作用域。

**示例代码**：

```cpp
#include <iostream>

int main() {
    int x = 10;
    std::cout << "x before block: " << x << std::endl;

    {
        // 新的代码块
        int x = 20; // 局部变量 x，隐藏外部的 x
        std::cout << "x inside block: " << x << std::endl;
    }

    std::cout << "x after block: " << x << std::endl; // 访问外部的 x

    return 0;
}
```

**预期输出**：

```wasm
x before block: 10
x inside block: 20
x after block: 10
```

**讲解**：

- 在内部代码块中重新声明了变量 `x`，该 `x` 只在代码块内有效，隐藏了外部的 `x`。
- 离开代码块后，内部的 `x` 不再可见，外部的 `x` 依然有效。

------

## 3. 条件语句

C++ 提供了多种条件语句，用于根据不同的条件执行不同的代码块。

### 3.1 `if` 语句

**描述**：`if` 语句用于在条件为真时执行特定的代码块。

**语法**：

```cpp
if (condition) {
    // code to execute if condition is true
}
```

**示例代码**：

```cpp
#include <iostream>

int main() {
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;

    if (number > 0) {
        std::cout << "The number is positive." << std::endl;
    }

    return 0;
}
```

**讲解**：

- 用户输入一个数字，如果 `number` 大于 `0`，则输出 "The number is positive."。

### 3.2 `if-else` 语句

**描述**：`if-else` 语句在条件为假时执行另一个代码块。

**语法**：

```cpp
if (condition) {
    // code to execute if condition is true
} else {
    // code to execute if condition is false
}
```

**示例代码**：

```cpp
#include <iostream>

int main() {
    int number;
    std::cout << "Enter a number: ";
    std::cin >> number;

    if (number % 2 == 0) {
        std::cout << number << " is even." << std::endl;
    } else {
        std::cout << number << " is odd." << std::endl;
    }

    return 0;
}
```

**讲解**：

- 判断输入的数字是奇数还是偶数，并输出相应的结果。

### 3.3 `else if` 语句

**描述**：`else if` 允许在多重条件下执行不同的代码块。

**语法**：

```cpp
if (condition1) {
    // code if condition1 is true
} else if (condition2) {
    // code if condition1 is false and condition2 is true
} else {
    // code if both condition1 and condition2 are false
}
```

**示例代码**：

```cpp
#include <iostream>

int main() {
    int score;
    std::cout << "Enter your score (0-100): ";
    std::cin >> score;

    if (score >= 90) {
        std::cout << "Grade: A" << std::endl;
    } else if (score >= 80) {
        std::cout << "Grade: B" << std::endl;
    } else if (score >= 70) {
        std::cout << "Grade: C" << std::endl;
    } else if (score >= 60) {
        std::cout << "Grade: D" << std::endl;
    } else {
        std::cout << "Grade: F" << std::endl;
    }

    return 0;
}
```

**讲解**：

- 根据分数范围判断并输出相应的等级。

### 3.4 `switch` 语句

**描述**：`switch` 语句根据变量的值选择执行的代码块，适用于离散的值。

**语法**：

```cpp
switch (expression) {
    case constant1:
        // code
        break;
    case constant2:
        // code
        break;
    // ...
    default:
        // code
}
```

**示例代码**：

```cpp
#include <iostream>

int main() {
    char grade;
    std::cout << "Enter your grade (A, B, C, D, F): ";
    std::cin >> grade;

    switch (grade) {
        case 'A':
            std::cout << "Excellent!" << std::endl;
            break;
        case 'B':
            std::cout << "Good!" << std::endl;
            break;
        case 'C':
            std::cout << "Fair!" << std::endl;
            break;
        case 'D':
            std::cout << "Poor!" << std::endl;
            break;
        case 'F':
            std::cout << "Fail!" << std::endl;
            break;
        default:
            std::cout << "Invalid grade." << std::endl;
    }

    return 0;
}
```

**讲解**：

- 根据输入的字母等级输出相应的评价。
- `break` 语句防止代码“掉入”下一个 `case` 中。

------

## 4. 迭代语句

C++ 提供了多种循环结构，用于重复执行代码块。

### 4.1 `for` 循环

**描述**：`for` 循环用于已知循环次数的情况，结构紧凑。

**语法**：

```cpp
for (initialization; condition; increment) {
    // code to execute
}
```

**示例代码**：

```cpp
#include <iostream>

int main() {
    std::cout << "Counting from 1 to 5:" << std::endl;

    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
    return 0;
}
```

**预期输出**：

```css
Counting from 1 to 5:
1 2 3 4 5
```

**讲解**：

- 初始化 `int i = 1`。
- 条件 `i <= 5` 为真时执行循环体。
- 每次循环后执行 `++i`，增加 `i` 的值。
- 最终输出 1 到 5。

### 4.2 `while` 循环

**描述**：`while` 循环在循环前判断条件，适合未知循环次数的情况。

**语法**：

```cpp
while (condition) {
    // code to execute
}
```

**示例代码**：

```cpp
#include <iostream>

int main() {
    int count = 1;
    std::cout << "Counting from 1 to 5 using while loop:" << std::endl;

    while (count <= 5) {
        std::cout << count << " ";
        ++count;
    }

    std::cout << std::endl;
    return 0;
}
```

**预期输出**：

```vbnet
Counting from 1 to 5 using while loop:
1 2 3 4 5
```

**讲解**：

- 初始化 `count = 1`。
- 条件 `count <= 5` 为真时执行循环体。
- 每次循环后 `++count` 增加 `count` 的值。

### 4.3 `do-while` 循环

**描述**：`do-while` 循环在循环后判断条件，保证至少执行一次循环体。

**语法**：

```cpp
do {
    // code to execute
} while (condition);
```

**示例代码**：

```cpp
#include <iostream>

int main() {
    int count = 1;
    std::cout << "Counting from 1 to 5 using do-while loop:" << std::endl;

    do {
        std::cout << count << " ";
        ++count;
    } while (count <= 5);

    std::cout << std::endl;
    return 0;
}
```

**预期输出**：

```vbnet
Counting from 1 to 5 using do-while loop:
1 2 3 4 5
```

**讲解**：

- 无论条件是否为真，`do` 块中的代码至少执行一次。
- 在本例中，`count` 从 `1` 开始，逐步增加到 `5`。

### 4.4 嵌套循环

**描述**：一个循环内部嵌套另一个循环，常用于多维数据结构的遍历。

**示例代码**：

```cpp
#include <iostream>

int main() {
    for (int i = 1; i <= 3; ++i) {
        std::cout << "Outer loop iteration " << i << ":" << std::endl;
        for (int j = 1; j <= 2; ++j) {
            std::cout << "  Inner loop iteration " << j << std::endl;
        }
    }
    return 0;
}
```

**预期输出**：

```sql
Outer loop iteration 1:
  Inner loop iteration 1
  Inner loop iteration 2
Outer loop iteration 2:
  Inner loop iteration 1
  Inner loop iteration 2
Outer loop iteration 3:
  Inner loop iteration 1
  Inner loop iteration 2
```

**讲解**：

- 外层 `for` 循环控制外层迭代次数。
- 内层 `for` 循环在每次外层循环中执行，控制内层迭代次数。

------

## 5. 跳转语句

跳转语句用于改变程序的执行流。C++ 中主要有 `break`、`continue`、`return` 和 `goto`。

### 5.1 `break` 语句

**描述**：`break` 用于立即终止最近的循环或 `switch` 语句。

**示例代码（在循环中使用 `break`）**：

```cpp
#include <iostream>

int main() {
    for (int i = 1; i <= 10; ++i) {
        if (i == 5) {
            break; // 结束循环
        }
        std::cout << i << " ";
    }
    std::cout << "\nLoop exited when i == 5." << std::endl;
    return 0;
}
```

**预期输出**：

```vbnet
1 2 3 4 
Loop exited when i == 5.
```

**讲解**：

- 当 `i` 达到 `5` 时，`break` 终止循环，停止进一步的迭代。

### 5.2 `continue` 语句

**描述**：`continue` 用于跳过当前的循环迭代，继续下一次循环。

**示例代码**：

```cpp
#include <iostream>

int main() {
    std::cout << "Even numbers between 1 and 10:" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        if (i % 2 != 0) {
            continue; // 跳过奇数
        }
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}
```

**预期输出**：

```sql
Even numbers between 1 and 10:
2 4 6 8 10
```

**讲解**：

- 当 `i` 是奇数时，`continue` 跳过本次循环，避免执行 `std::cout` 语句。
- 仅输出偶数。

### 5.3 `return` 语句

**描述**：`return` 用于从函数中返回一个值或结束函数执行。

**示例代码**：

```cpp
#include <iostream>

// 函数，返回两个数中的较大者
int max(int a, int b) {
    if (a > b) {
        return a; // 返回 a，退出函数
    }
    return b; // 返回 b，退出函数
}

int main() {
    int x = 10, y = 20;
    std::cout << "The maximum of " << x << " and " << y << " is " << max(x, y) << "." << std::endl;
    return 0;
}
```

**预期输出**：

```csharp
The maximum of 10 and 20 is 20.
```

**讲解**：

- `max` 函数根据条件返回较大的数，并退出函数执行。

### 5.4 `goto` 语句

**描述**：`goto` 允许无条件跳转到程序中指定的标签。虽然 `goto` 有时能简化代码，但不推荐频繁使用，因为它会使程序流程难以理解和维护。

**示例代码**：

```cpp
#include <iostream>

int main() {
    int number;
    std::cout << "Enter a positive number (negative to quit): ";
    std::cin >> number;

    if (number < 0) {
        goto end; // 跳转到 end 标签，结束程序
    }

    std::cout << "You entered: " << number << std::endl;

end:
    std::cout << "Program ended." << std::endl;
    return 0;
}
```

**预期输出**（输入为负数）：

```css
Enter a positive number (negative to quit): -5
Program ended.
```

**讲解**：

- 当输入负数时，`goto end;` 跳转到 `end` 标签，结束程序。
- 尽管可以使用 `goto`，但建议使用更结构化的控制流，如循环和条件语句。

------

## 6. 异常处理语句

异常处理用于应对程序运行过程中可能出现的错误情况，确保程序的健壮性和可靠性。

### 6.1 `try`, `catch`, 和 `throw` 语句

**描述**：

- `try` 块用于包含可能引发异常的代码。
- `throw` 用于抛出异常。
- `catch` 块用于捕获并处理异常。

**基本语法**：

```cpp
try {
    // code that may throw an exception
} catch (ExceptionType1 e1) {
    // handler for ExceptionType1
} catch (ExceptionType2 e2) {
    // handler for ExceptionType2
}
// ...
```

**示例代码**：

```cpp
#include <iostream>
#include <stdexcept>

// 函数，计算除法
double divide(double numerator, double denominator) {
    if (denominator == 0) {
        throw std::invalid_argument("Denominator cannot be zero."); // 抛出异常
    }
    return numerator / denominator;
}

int main() {
    double num, denom;

    std::cout << "Enter numerator: ";
    std::cin >> num;
    std::cout << "Enter denominator: ";
    std::cin >> denom;

    try {
        double result = divide(num, denom);
        std::cout << "Result: " << result << std::endl;
    } catch (std::invalid_argument &e) { // 捕获 std::invalid_argument 异常
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "Program continues after try-catch." << std::endl;
    return 0;
}
```

**预期输出**：

```javascript
Enter numerator: 10
Enter denominator: 0
Error: Denominator cannot be zero.
Program continues after try-catch.
```

**讲解**：

- `divide` 函数在分母为零时抛出 `std::invalid_argument` 异常。
- `try` 块尝试执行 `divide` 函数。
- 当异常发生时，执行对应的 `catch` 块，输出错误信息。
- 程序在异常处理后继续执行，而不会异常终止。

### 6.2 多重 `catch` 块

**描述**：可以为 `try` 块指定多个 `catch` 块，以处理不同类型的异常。

**示例代码**：

```cpp
#include <iostream>
#include <stdexcept>

int main() {
    try {
        // 模拟不同类型的异常
        int choice;
        std::cout << "Choose exception to throw (1: bad_alloc, 2: invalid_argument): ";
        std::cin >> choice;

        if (choice == 1) {
            throw std::bad_alloc();
        } else if (choice == 2) {
            throw std::invalid_argument("Invalid argument provided.");
        } else {
            std::cout << "No exception thrown." << std::endl;
        }
    } catch (std::bad_alloc &e) { // 处理 bad_alloc 异常
        std::cerr << "Caught std::bad_alloc: " << e.what() << std::endl;
    } catch (std::invalid_argument &e) { // 处理 invalid_argument 异常
        std::cerr << "Caught std::invalid_argument: " << e.what() << std::endl;
    }

    std::cout << "Program continues after try-catch." << std::endl;
    return 0;
}
```

**预期输出**（选择 `1`）：

```php
Choose exception to throw (1: bad_alloc, 2: invalid_argument): 1
Caught std::bad_alloc: std::bad_alloc
Program continues after try-catch.
```

**讲解**：

- 根据用户输入抛出不同类型的异常。
- 对应的 `catch` 块分别处理不同的异常类型。
- 如果未匹配的异常被抛出且没有对应的 `catch` 块，将导致程序终止（未在此示例中展示）。

### 6.3 `throw` 通常位置

**描述**：`throw` 语句可以在任何需要引发异常的位置使用，包括函数内部、嵌套调用中等。

**示例代码**：

```cpp
#include <iostream>
#include <stdexcept>

// 函数，检查数组索引
int getElement(int arr[], int size, int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index is out of range."); // 抛出异常
    }
    return arr[index];
}

int main() {
    int myArray[5] = {10, 20, 30, 40, 50};
    int index;

    std::cout << "Enter array index (0-4): ";
    std::cin >> index;

    try {
        int value = getElement(myArray, 5, index);
        std::cout << "Element at index " << index << " is " << value << "." << std::endl;
    } catch (std::out_of_range &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```

**预期输出**（输入为 `3`）：

```perl
Enter array index (0-4): 3
Element at index 3 is 40.
```

**预期输出**（输入为 `5`）：

```csharp
Enter array index (0-4): 5
Error: Index is out of range.
```

**讲解**：

- `getElement` 函数检查索引是否有效，如果无效则抛出 `std::out_of_range` 异常。
- `main` 函数中的 `try` 块调用 `getElement`，并在 `catch` 块中处理异常。

### 6.4 `rethrow` 异常

**描述**：可以在 `catch` 块中使用 `throw` 语句重新抛出捕获的异常，以便其他部分处理。

**示例代码**：

```cpp
#include <iostream>
#include <stdexcept>

// 函数，抛出异常
void func1() {
    throw std::runtime_error("Error in func1.");
}

// 函数，调用 func1 并重新抛出异常
void func2() {
    try {
        func1();
    } catch (...) { // 捕获所有异常
        std::cout << "func2() caught an exception and is rethrowing it." << std::endl;
        throw; // 重新抛出当前异常
    }
}

int main() {
    try {
        func2();
    } catch (std::exception &e) { // 在 main 中捕获异常
        std::cerr << "Main caught: " << e.what() << std::endl;
    }
    return 0;
}
```

**预期输出**：

```scss
func2() caught an exception and is rethrowing it.
Main caught: Error in func1.
```

**讲解**：

- `func1` 抛出异常。
- `func2` 调用 `func1`，捕获异常后重新抛出。
- `main` 最终捕获并处理异常。