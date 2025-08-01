## 1. 类继承（Class Inheritance）

### 1.1 概述

**类继承** 是面向对象编程（OOP）中的一个核心概念，允许一个类（派生类）从另一个类（基类）继承属性和行为。通过继承，派生类可以重用基类的代码，并根据需要添加新的成员或重写现有成员。

### 1.2 语法

```cpp
class Base {
public:
    void baseFunction();
protected:
    int protectedMember;
private:
    int privateMember;
};

class Derived : public Base { // 公有继承
public:
    void derivedFunction();
};
```

### 1.3 代码示例

```cpp
#include <iostream>

// 基类
class Animal {
public:
    void eat() const {
        std::cout << "Animal eats." << std::endl;
    }

protected:
    int age;
};

// 派生类
class Dog : public Animal {
public:
    void bark() const {
        std::cout << "Dog barks." << std::endl;
    }

    void setAge(int a) {
        age = a; // 访问受保护成员
    }

    int getAge() const {
        return age;
    }
};

int main() {
    Dog myDog;
    myDog.eat();    // 继承自Animal
    myDog.bark();   // Dog特有

    myDog.setAge(5);
    std::cout << "Dog's age: " << myDog.getAge() << std::endl;

    return 0;
}
```

### 1.4 执行结果

```rust
Animal eats.
Dog barks.
Dog's age: 5
```

## 2. 虚函数（Virtual Functions）

### 2.1 概述

**虚函数** 允许派生类重新定义基类中的函数，以实现多态性。在运行时，根据对象的实际类型调用相应的函数版本。

### 2.2 语法

```cpp
class Base {
public:
    virtual void display();
};
```

### 2.3 代码示例

```cpp
#include <iostream>

class Shape {
public:
    virtual void draw() const { // 虚函数
        std::cout << "Drawing a shape." << std::endl;
    }

    virtual ~Shape() {} // 虚析构函数
};

class Circle : public Shape {
public:
    void draw() const override { // 重写虚函数
        std::cout << "Drawing a circle." << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() const override { // 重写虚函数
        std::cout << "Drawing a square." << std::endl;
    }
};

void render(const Shape& shape) {
    shape.draw(); // 动态绑定，根据实际对象类型调用对应的draw()
}

int main() {
    Circle c;
    Square s;
    Shape genericShape;

    render(c);           // 输出: Drawing a circle.
    render(s);           // 输出: Drawing a square.
    render(genericShape); // 输出: Drawing a shape.

    return 0;
}
```

### 2.4 执行结果

```css
Drawing a circle.
Drawing a square.
Drawing a shape.
```

------

## 3. 纯虚类与抽象基类（Pure Virtual Classes and Abstract Base Classes） 

### 3.1 概述

**纯虚函数** 是在基类中声明但不提供实现的虚函数。包含至少一个纯虚函数的类称为 **抽象基类**（Abstract Base Class，ABC）。抽象基类不能被实例化，要求派生类必须实现所有纯虚函数才能被实例化。

### 3.2 语法

```cpp
class Base {
public:
    virtual void pureVirtualFunction() = 0; // 纯虚函数
    virtual void printm() = 0;
};
```

### 3.3 代码示例

```cpp
#include <iostream>

// 抽象基类
class Vehicle {
public:
    virtual void startEngine() = 0; // 纯虚函数

    virtual ~Vehicle() {} // 虚析构函数
};

class Car : public Vehicle {
public:
    void startEngine() override {
        std::cout << "Car engine started." << std::endl;
    }
};

class Motorcycle : public Vehicle {
public:
    void startEngine() override {
        std::cout << "Motorcycle engine started." << std::endl;
    }
};

int main() {
    // Vehicle v; // 错误: 不能实例化抽象类

    Car car;
    Motorcycle bike;

    car.startEngine();     // 输出: Car engine started.
    bike.startEngine();    // 输出: Motorcycle engine started.

    Vehicle* v1 = &car;
    Vehicle* v2 = &bike;

    v1->startEngine(); // 动态绑定，输出: Car engine started.
    v2->startEngine(); // 动态绑定，输出: Motorcycle engine started.

    return 0;
}
```

### 3.4 执行结果

```undefined
Car engine started.
Motorcycle engine started.
Car engine started.
Motorcycle engine started.
```

## 4. 继承后的访问控制（Access Control in Inheritance）

### 4.1 概述

继承时的 **访问控制** 决定了基类成员在派生类中的可访问性。继承方式主要有三种：`public`、`protected` 和 `private`。它们影响继承成员的访问级别。

### 4.2 语法与影响

- **公有继承** ：

  - 基类的 `public` 成员在派生类中保持 `public`。
  - 基类的 `protected` 成员在派生类中保持 `protected`。
  - 基类的 `private` 成员在派生类中不可访问。

- **保护继承（受保护的继承）** ：

  - 基类的 `public` 和 `protected` 成员在派生类中都变为 `protected`。

- **私有继承** ：
  - 基类的 `public` 和 `protected` 成员在派生类中都变为 `private`。

### 4.3 代码示例

```cpp
#include <iostream>

class Base {
public:
    int publicMember;
protected:
    int protectedMember;
private:
    int privateMember;
};

class PublicDerived : public Base {
public:
    void accessMembers() {
        publicMember = 1;      // 可访问
        protectedMember = 2;   // 可访问
        // privateMember = 3;  // 错误：privateMember 在派生类中不可访问
    }
};

class ProtectedDerived : protected Base {
public:
    void accessMembers() {
        publicMember = 1;      // 转为 protected
        protectedMember = 2;   // 转为 protected
        // privateMember = 3;  // 错误
    }
};

class PrivateDerived : private Base {
public:
    void accessMembers() {
        publicMember = 1;      // 转为 private
        protectedMember = 2;   // 转为 private
        // privateMember = 3;  // 错误
    }
};

int main() {
    PublicDerived pubDer;
    pubDer.publicMember = 10; // 可访问

    // ProtectedDerived protDer;
    // protDer.publicMember = 10; // 错误：publicMember 在 ProtectedDerived 中为 protected

    // PrivateDerived privDer;
    // privDer.publicMember = 10; // 错误：publicMember 在 PrivateDerived 中为 private

    return 0;
}
```

## 5. 继承中类的作用域（Scope of Classes in Inheritance）

### 5.1 概述

在继承关系中，类的作用域决定了成员名称的可见性和访问方式。派生类可以访问基类的成员，根据访问控制的不同，还可能需要使用 **作用域解析符** 来访问隐藏的成员。

### 5.2 代码示例

```cpp
#include <iostream>

class Base {
public:
    void display() const {
        std::cout << "Display from Base" << std::endl;
    }

    virtual void show() const {
        std::cout << "Show from Base" << std::endl;
    }
};

class Derived : public Base {
public:
    void display() const { // 隐藏基类的 display
        std::cout << "Display from Derived" << std::endl;
    }

    void callBaseDisplay() const {
        Base::display(); // 使用作用域解析符调用基类的 display
    }

    void show() const { // 重写 show， show 是虚函数可实现多态
        std::cout << "Show from Derived" << std::endl;
    }
};

int main() {
    Derived d;
    d.display();          // 调用 Derived::display
    d.callBaseDisplay();  // 调用 Base::display
    d.show();             // 调用 Derived::show

    Base* bPtr = &d;
    bPtr->display(); // 调用 Base::display，因为 display 不是虚函数
    bPtr->show();    // show 是虚函数，调用 Derived::show；否则调用 Base::show

    return 0;
}
```

### 5.3 执行结果

```sql
Display from Derived
Display from Base
Show from Derived
Display from Base
Show from Base // show 是虚函数则输出: Show from Derived
```

## 6. 构造函数与拷贝控制（Constructors and Copy Control in Inheritance）

### 6.1 概述

在继承体系中，类的构造函数和拷贝控制函数（拷贝构造函数、拷贝赋值运算符、析构函数）的调用顺序和行为需要注意。基类的构造函数在派生类之前调用，析构函数则在派生类之后调用。

### 6.2 构造函数的调用顺序

1. 基类的 **默认构造函数** 首先被调用，除非派生类在初始化列表中显式调用其他基类构造函数。
2. 派生类的成员按照声明顺序被构造。
3. 派生类的构造函数体被执行。

### 6.3 代码示例

```cpp
#include <iostream>
#include <string>

class Base {
public:
    Base() {
        std::cout << "Base default constructor" << std::endl;
    }

    Base(const std::string& name) : name_(name) {
        std::cout << "Base parameterized constructor: " << name_ << std::endl;
    }

    Base(const Base& other) : name_(other.name_) {
        std::cout << "Base copy constructor" << std::endl;
    }

    Base& operator=(const Base& other) {
        std::cout << "Base copy assignment" << std::endl;
        if (this != &other) {
            name_ = other.name_;
        }
        return *this;
    }

    virtual ~Base() {
        std::cout << "Base destructor" << std::endl;
    }

protected:
    std::string name_;
};

class Derived : public Base {
public:
    Derived() : Base("Default Derived") {
        std::cout << "Derived default constructor" << std::endl;
    }

    Derived(const std::string& name, int value) : Base(name), value_(value) {
        std::cout << "Derived parameterized constructor: " << value_ << std::endl;
    }

    Derived(const Derived& other) : Base(other), value_(other.value_) {
        std::cout << "Derived copy constructor" << std::endl;
    }

    Derived& operator=(const Derived& other) {
        std::cout << "Derived copy assignment" << std::endl;
        if (this != &other) {
            Base::operator=(other);
            value_ = other.value_;
        }
        return *this;
    }

    ~Derived() override {
        std::cout << "Derived destructor" << std::endl;
    }

private:
    int value_;
};

int main() {
    std::cout << "Creating d1:" << std::endl;
    Derived d1;

    std::cout << "\nCreating d2:" << std::endl;
    Derived d2("Custom Derived", 42);

    std::cout << "\nCopy constructing d3 from d2:" << std::endl;
    Derived d3 = d2;

    std::cout << "\nAssigning d1 = d2:" << std::endl;
    d1 = d2;

    std::cout << "\nExiting main..." << std::endl;
    return 0;
}
```

### 6.4 执行结果

```sql
Creating d1:
Base parameterized constructor: Default Derived
Derived default constructor

Creating d2:
Base parameterized constructor: Custom Derived
Derived parameterized constructor: 42

Copy constructing d3 from d2:
Base copy constructor
Derived copy constructor

Assigning d1 = d2:
Derived copy assignment
Base copy assignment

Exiting main...
Derived destructor
Base destructor
Derived destructor
Base destructor
Derived destructor
Base destructor
```

## 7. 容器与继承（Containers and Inheritance）

### 7.1 概述

**C++ 容器（如 `std::vector`、`std::list` 等）** 通常存储对象的副本，而非指向对象的指针。因此，当与继承结合使用时，可能导致 **切片（Object Slicing）** 问题，即仅存储基类部分，丢失派生类特有的信息。为了实现多态性，推荐使用指针或智能指针存储对象。

### 7.2 切片问题示例

```cpp
#include <iostream>
#include <vector>

class Base {
public:
    virtual void show() const { std::cout << "Base show" << std::endl; }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void show() const override { std::cout << "Derived show" << std::endl; }
};

int main() {
    std::vector<Base> vec;
    Derived d;
    vec.push_back(d); // 切片发生，派生类特有部分被丢弃

    vec[0].show(); // 输出: Base show

    return 0;
}
```

### 7.3 使用指针避免切片

```cpp
#include <iostream>
#include <vector>
#include <memory>

class Base {
public:
    virtual void show() const { std::cout << "Base show" << std::endl; }
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void show() const override { std::cout << "Derived show" << std::endl; }
};

int main() {
    std::vector<std::unique_ptr<Base>> vec;
    vec.emplace_back(std::make_unique<Derived>());

    vec[0]->show(); // 输出: Derived show

    return 0;
}
```

### 7.5 智能指针选择

- `std::unique_ptr`：
  - 独占所有权，不可复制，只能移动。
  - 适用于明确的单一所有权场景。
- `std::shared_ptr`：
  - 共享所有权，可以被多个指针共享和引用计数。
  - 适用于需要多个所有者的场景。