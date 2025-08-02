## 内存管理简介

C++ 提供了多种内存管理方式，包括传统的 C 风格的 `malloc` 和 `free`，以及 C++ 专用的 `new` 和 `delete`。

理解这些内存管理方法对于编写高效、安全的 C++ 程序至关重要。 

本文将详细介绍这些内存管理方法，包含基本用法、复杂操作（如 `realloc`），并配以实际案例和代码示例。

## 内存管理基础

在 C++ 程序中，内存主要分为以下几个区域：

- **栈（Stack）**：自动管理内存，存储局部变量和函数调用信息。内存分配和释放速度快，但空间有限。
- **堆（Heap）**：手动管理内存，用于动态分配内存。内存分配和释放由程序员控制，灵活但易出错（如内存泄漏、悬挂指针）。
- **全局/静态区（`Data/BSS Segment`）**：存储全局变量和静态变量。

了解栈和堆的区别，以及如何有效地在堆上分配和管理内存，是编写高效且安全的 C++ 程序的基础。

## C 风格内存管理

### `malloc` 函数

`malloc`（memory allocation）用于在堆上分配指定字节数的内存。其原型如下：

```cpp
#include <cstdlib>

void* malloc(size_t size);
```

- **参数**：`size` - 要分配的内存字节数。
- **返回值**：指向分配内存的指针，如果分配失败则返回 `nullptr`。

### `free` 函数

`free` 用于释放之前由 `malloc`、`calloc` 或 `realloc` 分配的内存。其原型如下：

```cpp
void free(void* ptr);
```

- **参数**：`ptr` - 要释放的内存指针。

### 示例代码

```cpp
#include <iostream>
#include <cstdlib> // 包含 malloc 和 free

int main() {
    // 分配一个整数的内存
    int* p = (int*)malloc(sizeof(int));
    if (p == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
        return 1;
    }

    *p = 42;
    std::cout << "Value: " << *p << std::endl;

    // 释放内存
    free(p);
    return 0;
}
```

### 注意事项

- **类型转换**：`malloc` 返回 `void*`，需要显式转换为所需类型的指针。
- **初始化**：`malloc` 分配的内存未初始化，内容不确定。
- **释放对应性**：由 `malloc` 分配的内存必须使用 `free` 释放，避免使用 `delete`。

## C++ 内存管理

C++ 提供了更高层次的内存管理操作符：`new` 和 `delete`，它们不仅分配和释放内存，还调用构造函数和析构函数，提供类型安全。

### **`new` 操作符**

用于在堆上分配对象，并调用其构造函数。

**单个对象**

```cpp
Type* ptr = new Type(parameters);
```

- **例子**：

```cpp
#include <iostream>

class MyClass {
public:
    MyClass(int val) : value(val) {
        std::cout << "Constructor called with value: " << value << std::endl;
    }
    ~MyClass() {
        std::cout << "Destructor called for value: " << value << std::endl;
    }
    int value;
};

int main() {
    MyClass* obj = new MyClass(10);
    std::cout << "Object value: " << obj->value << std::endl;
    delete obj; // 调用析构函数并释放内存
    return 0;
}
```

**输出**：

```sql
Constructor called with value: 10
Object value: 10
Destructor called for value: 10
```

**数组**

```cpp
Type* array = new Type[size];
```

- **例子**：

```cpp
#include <iostream>

int main() {
    int* arr = new int[5]; // 分配5个整数
    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 10;
    }
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    delete[] arr; // 释放数组内存
    return 0;
}
```

**输出**：

```undefined
arr[0] = 0
arr[1] = 10
arr[2] = 20
arr[3] = 30
arr[4] = 40
```

**`delete` 操作符**

用于释放由 `new` 分配的内存，并调用析构函数。

### 释放单个对象

```cpp
delete ptr;
```

### 释放数组

```cpp
delete[] ptr;
```

### 区别于 `malloc` 和 `free`

- **类型安全**：`new` 返回正确类型的指针，免去了强制类型转换。
- **构造/析构**：`new` 和 `delete` 自动调用构造函数和析构函数。
- **异常处理**：在分配失败时，`new` 默认抛出 `std::bad_alloc` 异常，而 `malloc` 返回 `nullptr`。

### 异常安全的 `new`

可以通过 `nothrow` 参数防止 `new` 抛出异常，改为返回 `nullptr`。

```cpp
#include <iostream>
#include <new> // 包含 std::nothrow

int main() {
    int* p = new(std::nothrow) int;
    if (p == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
        return 1;
    }
    *p = 100;
    std::cout << "Value: " << *p << std::endl;
    delete p;
    return 0;
}
```

------

## 总结和对比

了解 `malloc/free` 与 `new/delete` 的区别，有助于在编写 C++ 程序时正确选择内存管理方法。

| 特性                 | malloc/free                                | new/delete                                |
| -------------------- | ------------------------------------------ | ----------------------------------------- |
| 类型安全             | 需要显式类型转换                           | 自动类型转换，无需显式转换                |
| 构造/析构函数        | 不调用对象的构造/析构函数                  | 调用对象的构造/析构函数                   |
| 返回值               | `void*`，需要转换为目标类型                | 返回目标类型指针，类型安全                |
| 错误处理             | 分配失败返回 `nullptr`                     | 分配失败抛出 `std::bad_alloc` 异常        |
| 多态行为             | 无                                         | 支持多态，通过虚函数正确调用析构函数      |
| 内存分配与释放对应性 | 必须使用 `free` 释放由 `malloc` 分配的内存 | 必须使用 `delete` 释放由 `new` 分配的内存 |

### 示例对比

**使用 `malloc` 和 `free`**

```cpp
#include <iostream>
#include <cstdlib>

class MyClass {
public:
    MyClass(int val) : value(val) { std::cout << "Constructor called" << std::endl; }
    ~MyClass() { std::cout << "Destructor called" << std::endl; }
    int value;
};

int main() {
    // 使用 malloc 分配内存
    MyClass* obj = (MyClass*)malloc(sizeof(MyClass));
    if (obj == nullptr) {
        std::cerr << "malloc failed" << std::endl;
        return 1;
    }

    // 手动调用构造函数（不推荐）
    new(obj) MyClass(20); // 通过“定位 new”调用构造函数

    std::cout << "Value: " << obj->value << std::endl;

    // 手动调用析构函数
    obj->~MyClass();

    // 释放内存
    free(obj);
    return 0;
}
```

**注意**：使用 `malloc` 分配 C++ 对象时，需要手动调用构造函数和析构函数，这非常不便且易出错。因此，推荐使用 `new` 和 `delete`。

**使用 `new` 和 `delete`**

```cpp
#include <iostream>

class MyClass {
public:
    MyClass(int val) : value(val) { std::cout << "Constructor called" << std::endl; }
    ~MyClass() { std::cout << "Destructor called" << std::endl; }
    int value;
};

int main() {
    // 使用 new 分配内存并调用构造函数
    MyClass* obj = new MyClass(30);
    std::cout << "Value: " << obj->value << std::endl;

    // 使用 delete 释放内存并调用析构函数
    delete obj;
    return 0;
}
```

**输出**：

```sql
Constructor called
Value: 30
Destructor called
```

### 兼容性

- **C++ 类型特性**：`new` 和 `delete` 支持 C++ 的类型特性，包括构造函数、析构函数、多态等。
- **C 兼容性**：在需要兼容 C 代码或通过 C 接口分配内存时，仍可能需要使用 `malloc` 和 `free`。

## 高级内存管理

### 使用 realloc 进行内存重分配

`realloc` 用于调整之前分配的内存块大小。这在动态数组等数据结构中非常有用。

**原型**

```cpp
#include <cstdlib>

void* realloc(void* ptr, size_t new_size);
```

- 参数

  ：

  - `ptr`：指向之前分配的内存块。
  - `new_size`：新的内存大小（以字节为单位）。

- **返回值**：指向重新分配后的内存块的新指针。如果重新分配失败，返回 `nullptr`，原内存块保持不变。

**示例代码**

```cpp
#include <iostream>
#include <cstdlib>
#include <cstring> // 包含 memcpy

int main() {
    // 初始分配 3 个整数
    int* arr = (int*)malloc(3 * sizeof(int));
    if (arr == nullptr) {
        std::cerr << "Initial malloc failed" << std::endl;
        return 1;
    }

    // 初始化数组
    for (int i = 0; i < 3; ++i) {
        arr[i] = i + 1;
    }

    std::cout << "Initial array: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // 重新分配为 5 个整数
    int* temp = (int*)realloc(arr, 5 * sizeof(int));
    if (temp == nullptr) {
        std::cerr << "Realloc failed" << std::endl;
        free(arr); // 释放原内存
        return 1;
    }
    arr = temp;

    // 初始化新元素
    for (int i = 3; i < 5; ++i) {
        arr[i] = (i + 1) * 10;
    }

    std::cout << "Reallocated array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // 释放内存
    free(arr);
    return 0;
}
```

**输出**：

```sql
Initial array: 1 2 3 
Reallocated array: 1 2 3 40 50
```

### 动态数组管理

使用 `malloc` 和 `realloc` 来手动管理动态数组可以实现可变大小的数组，但需要处理内存分配、释放和数据复制。

**封装动态数组**

```cpp
#include <iostream>
#include <cstdlib>
#include <cstring>

class DynamicArray {
public:
    DynamicArray(size_t initial_size = 1)
        : size(initial_size), data((int*)malloc(size * sizeof(int))) {
        if (data == nullptr) {
            throw std::bad_alloc();
        }
    }

    ~DynamicArray() {
        free(data);
    }

    void resize(size_t new_size) {
        int* temp = (int*)realloc(data, new_size * sizeof(int));
        if (temp == nullptr) {
            throw std::bad_alloc();
        }
        data = temp;
        size = new_size;
    }

    int& operator[](size_t index) {
        return data[index];
    }

    size_t getSize() const { return size; }

private:
    size_t size;
    int* data;
};

int main() {
    try {
        DynamicArray arr(3);
        // 初始化
        for (size_t i = 0; i < arr.getSize(); ++i) {
            arr[i] = i + 1;
        }

        std::cout << "Initial array: ";
        for (size_t i = 0; i < arr.getSize(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;

        // 调整大小
        arr.resize(5);
        arr[3] = 40;
        arr[4] = 50;

        std::cout << "Resized array: ";
        for (size_t i = 0; i < arr.getSize(); ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;

    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```

**输出**：

```sql
Initial array: 1 2 3 
Resized array: 1 2 3 40 50
```

**注意**：这种方式需要手动管理内存和数组大小，且缺乏类型安全性和自动化。推荐使用 C++ 标准容器如 `std::vector` 来代替。

