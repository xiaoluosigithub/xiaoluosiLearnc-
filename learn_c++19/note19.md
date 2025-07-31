## 1. 类与对象简介

### 1.1 什么是类和对象

- **类（Class）**是C++中创建用户自定义类型的一种方式，它将数据（成员变量）和操作数据的函数（成员函数）封装在一起。
- **对象（Object）**是类的实例化，拥有类定义的所有属性和行为。
- **类**更像是汽车图纸，**对象**更像是造出来的汽车。

### 1.2 类的作用

- **封装（Encapsulation）**：将数据和操作数据的代码绑定在一起，保护数据不被外界直接访问。
- **抽象（Abstraction）**：通过类定义抽象出具有共同特性的对象，提高代码的可重用性和可维护性。
- **继承（Inheritance）和多态（Polymorphism）**：实现代码的复用与动态绑定。

------

## 2. 类的定义

### 2.1 基本语法

```cpp
class ClassName {
public:
    // 公有成员
private:
    // 私有成员
protected:
    // 受保护成员
};
```

### 2.2 示例

创建一个表示学生的类：

```cpp
#include <string>

class Student {
public:
    // 公有构造函数
    Student(const std::string& name, int age);

    // 公有成员函数
    void setName(const std::string& name);
    std::string getName() const;

    void setAge(int age);
    int getAge() const;

private:
    // 私有成员变量
    std::string name_;
    int age_;
};
```

------

## 3. 成员变量与成员函数

### 3.1 成员变量

- **成员变量（Member Variables）**：用于存储对象的状态信息。
- **命名约定**：常用下划线结尾（例如 `name_`）表示成员变量，避免与局部变量混淆。

### 3.2 成员函数

- **成员函数（Member Functions）**：定义对象的行为，可以访问和修改成员变量。
- **常成员函数（Const Member Functions）**：保证函数不会修改对象的状态。

### 3.3 示例实现

```cpp
// Student.cpp
#include "Student.h"

Student::Student(const std::string& name, int age)
    : name_(name), age_(age) {}

void Student::setName(const std::string& name) {
    name_ = name;
}

std::string Student::getName() const {
    return name_;
}

void Student::setAge(int age) {
    if (age > 0)
        age_ = age;
}

int Student::getAge() const {
    return age_;
}
```

------

## 4. 访问控制

### 4.1 访问修饰符

- **public**：公有成员，可以被所有代码访问。
- **private**：私有成员，仅能被类的成员函数和友元访问。
- **protected**：受保护成员，仅能被类的成员函数、友元和派生类访问。

### 4.2 例子

```cpp
class Sample {
public:
    void publicFunction();

private:
    int privateVar_;
    void privateFunction();

protected:
    int protectedVar_;
};
```

------

## 5. 构造函数与析构函数

### 5.1 构造函数

- **默认构造函数**：没有参数的构造函数。
- **参数化构造函数**：接受参数以初始化对象。
- **拷贝构造函数**：用一个对象初始化另一个对象。
- **移动构造函数（C++11）**：从临时对象“移动”资源。

### 5.2 析构函数

- **析构函数（Destructor）**：在对象生命周期结束时调用，用于释放资源。

### 5.3 示例

```cpp
#include <iostream>

class Example {
public:
    // 默认构造函数
    Example() : data_(0) {
        std::cout << "Default constructor called.\n";
    }

    // 参数化构造函数
    Example(int data) : data_(data) {
        std::cout << "Parameterized constructor called with data = " << data_ << ".\n";
    }

    // 拷贝构造函数
    Example(const Example& other) : data_(other.data_) {
        std::cout << "Copy constructor called.\n";
    }

    // 移动构造函数
    Example(Example&& other) noexcept : data_(other.data_) {
        other.data_ = 0;
        std::cout << "Move constructor called.\n";
    }

    // 析构函数
    ~Example() {
        std::cout << "Destructor called for data = " << data_ << ".\n";
    }

private:
    int data_;
};
```

### 5.4 使用示例

```cpp
int main() {
    Example ex1;               // 调用默认构造函数
    Example ex2(42);           // 调用参数化构造函数
    Example ex3 = ex2;         // 调用拷贝构造函数
    Example ex4 = std::move(ex2); // 调用移动构造函数
    return 0;
}
```

**输出示例：**

```kotlin
Default constructor called.
Parameterized constructor called with data = 42.
Copy constructor called.
Move constructor called.
Destructor called for data = 0.
Destructor called for data = 42.
Destructor called for data = 42.
```

## 6. 拷贝控制

**拷贝构造函数与拷贝赋值运算符**

### 6.1 拷贝构造函数

- **定义**：用于创建一个新对象，并复制现有对象的成员。
- **语法**：`ClassName(const ClassName& other);`

### 6.2 拷贝赋值运算符

- **定义**：用于将一个已有对象的值赋给另一个已有对象。
- **语法**：`ClassName& operator=(const ClassName& other);`

### 6.3 示例

```cpp
#include <iostream>
#include <cstring>

class MyString {
public:
    // 构造函数
    MyString(const char* str = nullptr) {
        if (str) {
            size_ = std::strlen(str);
            data_ = new char[size_ + 1];
            std::strcpy(data_, str);
        } else {
            size_ = 0;
            data_ = new char[1];
            data_[0] = '\0';
        }
        std::cout << "Constructor called.\n";
    }

    // 拷贝构造函数
    MyString(const MyString& other) : size_(other.size_) {
        data_ = new char[size_ + 1];
        std::strcpy(data_, other.data_);
        std::cout << "Copy constructor called.\n";
    }

    // 拷贝赋值运算符
    MyString& operator=(const MyString& other) {
        std::cout << "Copy assignment operator called.\n";
        if (this == &other)
            return *this; // 自赋值检查

        delete[] data_; // 释放现有资源

        size_ = other.size_;
        data_ = new char[size_ + 1];
        std::strcpy(data_, other.data_);
        return *this;
    }

    // 析构函数
    ~MyString() {
        delete[] data_;
        std::cout << "Destructor called.\n";
    }

    void print() const {
        std::cout << data_ << "\n";
    }

private:
    char* data_;
    std::size_t size_;
};
```

### 6.4 使用示例

```cpp
int main() {
    MyString s1("Hello");
    MyString s2 = s1;        // 调用拷贝构造函数
    MyString s3;
    s3 = s1;                  // 调用拷贝赋值运算符

    s1.print();
    s2.print();
    s3.print();
    return 0;
}
```

**输出示例：**

```kotlin
Constructor called.
Copy constructor called.
Constructor called.
Copy assignment operator called.
Hello
Hello
Hello
Destructor called.
Destructor called.
Destructor called.
```

## 7. 移动语义

### 7.1 什么是移动语义

- **移动语义（Move Semantics）**：允许资源的所有权从一个对象转移到另一个对象，避免不必要的拷贝，提高性能。

### 7.2 移动构造函数与移动赋值运算符

- **移动构造函数**：`ClassName(ClassName&& other) noexcept;`
- **移动赋值运算符**：`ClassName& operator=(ClassName&& other) noexcept;`

### 7.3 示例

```cpp
#include <iostream>
#include <utility>

class MoveExample {
public:
    // 构造函数
    MoveExample(int size) : size_(size), data_(new int[size]) {
        std::cout << "Constructor called.\n";
    }

    // 拷贝构造函数
    MoveExample(const MoveExample& other) : size_(other.size_), data_(new int[other.size_]) {
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "Copy constructor called.\n";
    }

    // 移动构造函数
    MoveExample(MoveExample&& other) noexcept : size_(other.size_), data_(other.data_) {
        other.size_ = 0;
        other.data_ = nullptr;
        std::cout << "Move constructor called.\n";
    }

    // 拷贝赋值运算符
    MoveExample& operator=(const MoveExample& other) {
        std::cout << "Copy assignment operator called.\n";
        if (this == &other)
            return *this;

        delete[] data_;
        size_ = other.size_;
        data_ = new int[size_];
        std::copy(other.data_, other.data_ + size_, data_);
        return *this;
    }

    // 移动赋值运算符
    MoveExample& operator=(MoveExample&& other) noexcept {
        std::cout << "Move assignment operator called.\n";
        if (this == &other)
            return *this;

        delete[] data_;
        size_ = other.size_;
        data_ = other.data_;

        other.size_ = 0;
        other.data_ = nullptr;
        return *this;
    }

    // 析构函数
    ~MoveExample() {
        delete[] data_;
        std::cout << "Destructor called.\n";
    }

private:
    int size_;
    int* data_;
};
```

### 7.4 使用示例

```cpp
int main() {
    MoveExample ex1(100);                 // Constructor
    MoveExample ex2 = ex1;                // Copy Constructor
    MoveExample ex3 = MoveExample(200);   // Move Constructor

    MoveExample ex4(300);
    ex4 = ex1;                             // Copy Assignment
    ex4 = MoveExample(400);                // Move Assignment

    return 0;
}
```

**输出示例：**

```kotlin
Constructor called.
Copy constructor called.
Constructor called.
Move constructor called.
Destructor called.
Constructor called.
Copy assignment operator called.
Move constructor called.
Move assignment operator called.
Destructor called.
Destructor called.
Destructor called.
Destructor called.
```

------