## 避免内存泄漏

内存泄漏是指程序分配的内存未被释放，导致内存被浪费，甚至耗尽。避免内存泄漏的策略包括：

- **确保每个 `new` 有对应的 `delete`**。
- **使用 `RAII` 和智能指针**：自动管理资源，避免手动管理内存。
- **工具辅助**：使用工具如 `Valgrind` 检测内存泄漏。

**示例：内存泄漏**

```cpp
#include <iostream>
int main() {
    int* p = new int(10);
    // 忘记 delete p; 导致内存泄漏
    return 0;
}
```

**解决方法**：

```cpp
#include <iostream>

int main() {
    int* p = new int(10);
    // 正确释放内存
    delete p;
    return 0;
}
```

## `RAII`（资源获取即初始化）

`RAII` 是 C++ 中的一种编程惯用法，通过对象的生命周期管理资源，确保资源在对象构造时获取，析构时释放，避免泄漏。

**示例：`RAII` 实现类似于`shared_ptr`智能指针**

`std::shared_ptr` 是 C++ 标准库中功能强大的智能指针之一，提供了共享所有权的能力，使得多个指针可以共同管理同一个动态分配的对象。通过引用计数机制，`shared_ptr` 确保了对象在最后一个指针被销毁时自动释放，极大地简化了内存管理，防止了内存泄漏和悬挂指针问题。

### **`SimpleSharedPtr` 的基本概念**

`SimpleSharedPtr` 是一个简化版的 `shared_ptr` 实现，旨在帮助理解其核心机制。其基本功能包括：

- **共享所有权**：多个 `SimpleSharedPtr` 实例可以指向同一个对象，共享对该对象的所有权。
- **自动管理生命周期**：当最后一个 `SimpleSharedPtr` 被销毁或指向其他对象时，管理的对象被自动释放。
- **引用计数**：内部维护一个引用计数，记录有多少个 `SimpleSharedPtr` 实例指向同一个对象。

### **引用计数控制块的设计**

为了实现引用计数机制，`SimpleSharedPtr` 需要一个控制块（Control Block），它包含：

- **引用计数（`ref_count`）**：记录有多少个 `SimpleSharedPtr` 指向同一个对象。
- **指向对象的指针（`ptr`）**：指向实际管理的对象。

控制块通常与被管理对象一起被分配，但为了简化实现，本示例将它们独立管理。

```cpp
struct ControlBlock {
    int ref_count;    // 引用计数
    // 可以扩展为包含自定义删除器等

    ControlBlock() : ref_count(1) {}
};
```

### `SimpleSharedPtr` 的实现

**类结构**

`SimpleSharedPtr` 是一个模板类，模板参数 `T` 表示它所管理的对象类型。

```cpp
template <typename T>
class SimpleSharedPtr {
private:
    T* ptr;                // 指向管理的对象
    ControlBlock* control; // 指向控制块

public:
    // 构造函数、析构函数、拷贝与移动操作、操作符重载等
};
```

**构造函数与析构函数**

- **默认构造函数**：初始化指针和控制块为空。
- **参数化构造函数**：接受一个裸指针，初始化控制块，并引用计数为1。
- **析构函数**：减少引用计数，若引用计数为0，则释放对象和控制块。

```cpp
// 默认构造函数
SimpleSharedPtr() : ptr(nullptr), control(nullptr) {}

// 参数化构造函数
explicit SimpleSharedPtr(T* p) : ptr(p) {
    if (p) {
        control = new ControlBlock();
    } else {
        control = nullptr;
    }
}

// 析构函数
~SimpleSharedPtr() {
    release();
}
```

**辅助函数 `release`**：

```cpp
private:
void release() {
    if (control) {
        control->ref_count--;
        if (control->ref_count == 0) {
            delete ptr;
            delete control;
        }
    }
    ptr = nullptr;
    control = nullptr;
}
```

### 拷贝构造与拷贝赋值

拷贝构造函数和拷贝赋值操作符允许多个 `SimpleSharedPtr` 实例共享同一个对象，共享相同的控制块。

```cpp
// 拷贝构造函数
SimpleSharedPtr(const SimpleSharedPtr& other) : ptr(other.ptr), control(other.control) {
    if (control) {
        control->ref_count++;
    }
}

// 拷贝赋值操作符
SimpleSharedPtr& operator=(const SimpleSharedPtr& other) {
    if (this != &other) {
        // 释放当前资源
        release();

        // 复制新的资源和控制块
        ptr = other.ptr;
        control = other.control;
        if (control) {
            control->ref_count++;
        }
    }
    return *this;
}
```

### 移动构造与移动赋值

移动语义允许资源所有权从一个 `SimpleSharedPtr` 转移到另一个，而不增加引用计数。

```cpp
// 移动构造函数
SimpleSharedPtr(SimpleSharedPtr&& other) noexcept : ptr(other.ptr), control(other.control) {
    other.ptr = nullptr;
    other.control = nullptr;
}

// 移动赋值操作符
SimpleSharedPtr& operator=(SimpleSharedPtr&& other) noexcept {
    if (this != &other) {
        // 释放当前资源
        release();

        // 接管 `other` 的资源
        ptr = other.ptr;
        control = other.control;

        // 置 `other` 为空
        other.ptr = nullptr;
        other.control = nullptr;
    }
    return *this;
}
```

### 操作符重载

重载 `*` 和 `->` 操作符，以便像使用原生指针一样使用 `SimpleSharedPtr`。

```cpp
// 解引用操作符
T& operator*() const {
    return *ptr;
}

// 箭头操作符
T* operator->() const {
    return ptr;
}
```

### 其他成员函数

- **`use_count`**：返回当前引用计数。
- **`get`**：返回裸指针。
- **`reset`**：重置指针，指向新对象或 `nullptr`。

```cpp
// 获取引用计数
int use_count() const {
    return control ? control->ref_count : 0;
}

// 获取裸指针
T* get() const {
    return ptr;
}

// 重置指针
void reset(T* p = nullptr) {
    // 释放当前资源
    release();

    // 指向新资源
    ptr = p;
    if (p) {
        control = new ControlBlock();
    } else {
        control = nullptr;
    }
}
```

### 完整代码示例

以下是 `SimpleSharedPtr` 的完整实现及其使用示例。

```cpp
#include <iostream>

// 控制块结构
struct ControlBlock {
    int ref_count;

    ControlBlock() : ref_count(1) {}
};

// 简化版的 shared_ptr 实现
template <typename T>
class SimpleSharedPtr {
private:
    T* ptr;                // 指向管理的对象
    ControlBlock* control; // 指向控制块

    // 释放当前资源
    void release() {
        if (control) {
            control->ref_count--;
            std::cout << "Decremented ref_count to " << control->ref_count << std::endl;
            if (control->ref_count == 0) {
                delete ptr;
                delete control;
                std::cout << "Resource and ControlBlock destroyed." << std::endl;
            }
        }
        ptr = nullptr;
        control = nullptr;
    }

public:
    // 默认构造函数
    SimpleSharedPtr() : ptr(nullptr), control(nullptr) {
        std::cout << "Default constructed SimpleSharedPtr (nullptr)." << std::endl;
    }

    // 参数化构造函数
    explicit SimpleSharedPtr(T* p) : ptr(p) {
        if (p) {
            control = new ControlBlock();
            std::cout << "Constructed SimpleSharedPtr, ref_count = " << control->ref_count << std::endl;
        } else {
            control = nullptr;
        }
    }

    // 拷贝构造函数
    SimpleSharedPtr(const SimpleSharedPtr& other) : ptr(other.ptr), control(other.control) {
        if (control) {
            control->ref_count++;
            std::cout << "Copied SimpleSharedPtr, ref_count = " << control->ref_count << std::endl;
        }
    }

    // 拷贝赋值操作符
    SimpleSharedPtr& operator=(const SimpleSharedPtr& other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            if (control) {
                control->ref_count++;
                std::cout << "Assigned SimpleSharedPtr, ref_count = " << control->ref_count << std::endl;
            }
        }
        return *this;
    }

    // 移动构造函数
    SimpleSharedPtr(SimpleSharedPtr&& other) noexcept : ptr(other.ptr), control(other.control) {
        other.ptr = nullptr;
        other.control = nullptr;
        std::cout << "Moved SimpleSharedPtr." << std::endl;
    }

    // 移动赋值操作符
    SimpleSharedPtr& operator=(SimpleSharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ptr = other.ptr;
            control = other.control;
            other.ptr = nullptr;
            other.control = nullptr;
            std::cout << "Move-assigned SimpleSharedPtr." << std::endl;
        }
        return *this;
    }

    // 析构函数
    ~SimpleSharedPtr() {
        release();
    }

    // 解引用操作符
    T& operator*() const {
        return *ptr;
    }

    // 箭头操作符
    T* operator->() const {
        return ptr;
    }

    // 获取引用计数
    int use_count() const {
        return control ? control->ref_count : 0;
    }

    // 获取裸指针
    T* get() const {
        return ptr;
    }

    // 重置指针
    void reset(T* p = nullptr) {
        release();
        ptr = p;
        if (p) {
            control = new ControlBlock();
            std::cout << "Reset SimpleSharedPtr, ref_count = " << control->ref_count << std::endl;
        } else {
            control = nullptr;
        }
    }
};

// 测试类
class Test {
public:
    Test(int val) : value(val) {
        std::cout << "Test Constructor: " << value << std::endl;
    }
    ~Test() {
        std::cout << "Test Destructor: " << value << std::endl;
    }
    void show() const {
        std::cout << "Value: " << value << std::endl;
    }

private:
    int value;
};

int main() {
    std::cout << "Creating default constructed shared_ptr..." << std::endl;
    SimpleSharedPtr<Test> ptr1; // 默认构造
    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;

    std::cout << "\nCreating shared_ptr with resource..." << std::endl;
    SimpleSharedPtr<Test> ptr2(new Test(100)); // 非默认构造
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
    ptr2->show();

    std::cout << "\nCopying ptr2 to ptr3..." << std::endl;
    SimpleSharedPtr<Test> ptr3 = ptr2; // 拷贝构造
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
    std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;
    ptr3->show();

    std::cout << "\nAssigning ptr3 to ptr1..." << std::endl;
    ptr1 = ptr3; // 拷贝赋值
    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
    std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;

    std::cout << "\nResetting ptr2..." << std::endl;
    ptr2.reset(new Test(200)); // 重新指向新的对象
    std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl;
    ptr2->show();
    std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl;
    std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl;

    std::cout << "\nExiting scope..." << std::endl;
    } // ptr2, ptr1, ptr3 离开作用域

    std::cout << "End of main." << std::endl;
    return 0;
}
```