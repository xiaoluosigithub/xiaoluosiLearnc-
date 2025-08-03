

## c++类

## 1、基本定义

1. 类的作用
   - 封装：将数据和操作数据的代码绑定在一起，保护数据不被外界直接访问。
   - 抽象：通过类定义抽象出具有共同特性的对象，提高代码的可重用性和可维护性。
   - 继承和多态：实现代码的复用与动态绑定。
2. 基本语法

~~~c++
class Student{
public:
	// 公有成员
private:
	// 私有成员
protected:
    //受保护成员
};
~~~



## 2、成员变量和成员函数



## 3、访问控制符

- **public**：公有成员，可以被所有代码访问。
- **private**：私有成员，仅能被类的成员函数和友元访问。
- **protected**：受保护成员，仅能被类的成员函数、友元和派生类访问。



## 4、构造函数

- 默认构造函数：没有参数的构造函数
- 参数化构造函数：接收参数以初始化对象
- 拷贝构造函数：用一个对象初始化另一个对象
- 移动构造函数（c++11）：从临时对象”移动“资源

### 1、默认构造函数

~~~c++
class Example{
public:
    // 什么都不写 编译器会隐式生成一个默认构造函数(前提是没有手动定义其他函数)
    
    // 显示声明
    Example(){} // 手动写一个空的默认构造函数
    
    // 显式 =default c++11起
    // 可以让类在声明了其它构造函数后，依然保留默认构造函数。
    Example() = default; // 显示要求编译器生成
    
    // 在类外用 =default 定义
    Example(); // 只做声明
};

Example::Example() = default //类外要求编译器生成
~~~

### 2、参数化构造函数

~~~cpp
class Example{
public:
	// 参数化构造函数
    Example(int a, int b){
        _a = a;
        _b = b;
    }
    
    // 初始化列表形式
    // 比在构造函数体内赋值更高效，直接在成员对象构造时初始化，而不是先默认构造再赋值。
    // const形式的变量，必须使用初始化列表进行初始化
    Example(int a, int b) : _a(a), _b(b){}
    
    // 带默认参数的参数化构造函数
    Example(int a = 0, int b = 0) : _a(a), _b(b){}
    
    // 构造函数的重载
    // 函数重载原理:编译器根据实参个数和类型匹配最合适的构造函数。规则和普通函数重载一样。
    Example(int x){std::cout << "int" << x << '\n';}
    Example(double x){std::cout << "double" << x << '\n';}
    Example(char x){std::cout << "char" << x << '\n';}
    
private:
    int _a, _b;
};
~~~



### 3、拷贝构造函数

~~~cpp
class Example{
public:
    
	// 如果没有显式定义拷贝构造函数，编译器会生成一个默认的浅拷贝版本
    // 成员逐个拷贝（浅拷贝）。 对于指针成员，仅拷贝指针值，不会复制所指向的内容。
    // 编译器自动生成
    // Example(const Example & other){_data = other._data;}
    
    // 显示定义(手写实现)
    // 自己实现拷贝构造函数，可以做深拷贝
    Example(const Example & other){
        _data = new int(*other._data);
    }
    
    // =default (c++11起) 
    // 显示要求编译器生成默认拷贝构造
    // 当类中有其它构造函数时，如果想保留拷贝构造，必须显式 = default。
    Example(const Example &) = default;
    
    
private:
    int * _data;
};
~~~

### 4、移动构造函数 （c++11）

参数是**右值引用** `&&`。

从一个**临时对象**（右值）中**“转移”资源**，而不是拷贝。

转移后通常要让源对象进入一个**安全的空状态**（如 `nullptr`）。

~~~cpp
class Example{
public:
    // 手动定义
    Example(Example && other) noexcept{
        _data = other._data;	// 接管资源
        other._data = nullptr;	// 让源对象安全可析构
    }
    
    // 如果没有写拷贝/移动构造, 编译器会生成一个逐成员移动的版本
    // 编译器会自动生成 
    // Example(Example && other){_data = std::move(other._data);}
    
    // =default(显示要求生成)
    // 如果你写了其他构造函数，但仍希望保留移动构造
    //强制生成默认移动构造。 会按成员顺序调用它们的移动构造。
    Example(Example && other) = default;
    
    // 禁止移动
    // 如果类不能安全移动，显示禁用
    // 资源不可转移（如 std::mutex）。避免移动后对象处于不可预测状态。
    Example(Example && other) = delete; // 禁止移动构造    
private:
    int * _data;
};
~~~



~~~cpp
class A {
    std::string s;
public:
    // 构造时直接移动
    // 普通构造函数，参数是一个字符串，直接“移动”进去初始化成员 s
    A(std::string str) : s(std::move(str)) {}

    // 移动构造函数，使用初始化列表将 other.s 移动到当前对象的 s
    A(A&& other) noexcept : s(std::move(other.s)) {}
};
~~~

假设改成下面这样：

```cpp
A(A&& other) noexcept {
    s = std::move(other.s); // 这是赋值操作，不是构造
}
```

- 先调用成员变量 `s` 的**默认构造函数**，初始化一个空字符串。
- 然后在构造函数体里调用赋值运算符，将 `other.s` 移动给 `s`。
- 这样产生了两次操作，效率较低。

而用初始化列表：

```cpp
A(A&& other) noexcept : s(std::move(other.s)) {}
```

- 直接调用 `std::string` 的移动构造函数，**一步到位**完成初始化，效率最高。



## 5、析构函数

- **析构函数（Destructor）**：在对象生命周期结束时调用，用于释放资源。

  **无参数**、**无返回值**（不能有 `void`）。

  每个类最多只能有一个析构函数（不能重载）。

  自动在对象生命周期结束时调用，释放资源。

~~~cpp
class Example{
public:
    // 默认版本
    ~Example();
    
    // 自己写析构函数,释放动态资源
    ~Example(){delete _data;}
    
    // 显式要求默认行为
    ~Example() = default;
    
    // 禁止析构
    ~Example() = delete;
    
    // 虚析构
    virtual ~Example(){}
    
    // 纯虚析构 让类变成抽象类。
    virtual ~Example() = 0;
private:
    int * _data;
    
}；
~~~



## 示例

~~~cpp
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
~~~



## 6、拷贝控制

拷贝构造函数与拷贝控制运算符

### 拷贝构造函数

- **定义**：用于创建一个新对象，并复制现有对象的成员。
- **语法**：`ClassName(const ClassName& other);`

### 拷贝赋值运算符

- **定义**：用于将一个已有对象的值赋给另一个已有对象。
- **语法**：`ClassName& operator=(const ClassName& other);`

~~~cpp
class Example{
public:
	// 构造函数
    Example(const char * str = nullptr){
        // 如果传入指针非空
        if(str){
            // _size 大小初始化为传入字符串大小的长度
            _size = std::strlen(str);
            // _data 指针申请空间
            _data = new char[_size + 1];
            // 将字符串进行拷贝
            std::strcpy(_data, str);
        } else {	// 传入指针为空指针
            _size = 0;	// 长度设置为零
            _data = new char[1]; 
            _data = '\0';
        }
        std::cout << "Construct called \n";
    }
    
    // 拷贝构造函数
    Example(const Example & other) : _size(other._size) {
        _data = new char[_size + 1]; // 指针申请空间 size使用初始化列表进行直接构造
        std::strcpy(_data, other._data); // 拷贝赋值
        std::cout << "Copy constructor called \n";
    }
    
    // 拷贝赋值运算符
    Example & operator = (const Example & other){
        std::cout << "Copy assignment operator called\n";
        if(this == & other){ // 如果自拷贝
            return *this; // 返回自身
        }
        
        delete[] _data; // 释放现有资源
        
        _size = other._size;
        _data = new char[_size + 1];
        std::strcpy(_data, other._data);
        return *this;
    }
    
    // 析构函数
    ~Example(){
        delete[] _data;
        std::cout << "Destructor called \n";
    }
private:
    char * _data;
    std::size_t _size;
};
~~~



## 7、移动语义 移动构造&&移动赋值

### 什么是移动语义

- **移动语义（Move Semantics）**：允许资源的所有权从一个对象转移到另一个对象，避免不必要的拷贝，提高性能。

### 移动构造函数与移动赋值运算符

- **移动构造函数**：`ClassName(ClassName&& other) noexcept;`
- **移动赋值运算符**：`ClassName& operator=(ClassName&& other) noexcept;`

~~~cpp
class Example{
public:
	// 构造函数 
    Example(int size) : _size(size), _data(new int[size]){
        std::cout << "Constructor called \n";
    }
    
    // 拷贝构造函数
    Example(const Example & other) : _size(other._size), _data(new int[other._size]) {
        std::copy(other._data, other._data + _size, _data);
        std::cout << "Copy constructor called\n";
    }
    
    // 移动构造函数
    Example(Example && other) noexcept : _size(other._size), _data(other._data) {
        // 将原变量进行置空
        other._size = 0;
        other._data = nullptr;
        std::cout << "Move constructor called\n";
    }
    
    // 拷贝赋值运算符
    Example & operator = (const Example & other){
        std::cout << "Copy assignment operator called \n";
        if(this == &other){
            return *this;
        }
        
        delete[] _data;
        _size = other._size;
        _data = new int[_size];
        std::copy(other._data, other._data + _size, _data);
        return *this;
    }
    
    // 移动赋值运算符
    Example & operator = (Example && other) noexcept {
        if(this == &other){
            return *this;
        }
        delete[] _data;
        _size = other._size; 
        _data = other._data; // 指针资源转移
        
        other._size = 0;
        other._data = nullptr;
        return *this;
    }
    
private:
    int _size;
    int * _data;
};
~~~



## 8、类的友元

### 什么是友元

- **友元（Friend）**：可以访问类的私有和保护成员的非成员函数或另一个类。

### 类型

- **友元函数**：单个函数可以被声明为友元。
- **友元类**：整个类可以被声明为友元。

~~~cpp
class Example{
public:
    friend void func(const Example & b);
    friend class Friend_Example;
private:
    int a;
};

// 友元函数定义
void func(const Example & b){
    std::cout << b.a << std::endl;
}

// 友元类定义
class Friend_Example{
public:
    void func(const Example & c){
        std::cout << c.a << std::endl;
    }
}
~~~



## 9、运算符重载

### 什么是运算符重载

- **运算符重载（Operator Overloading）**：允许对自定义类型使用C++运算符，如 `+`, `-`, `<<` 等。

### 重载运算符的规则

- 只能对已有运算符进行重载，不能创建新运算符。
- 至少有一个操作数必须是用户定义的类型。
- 不能改变运算符的优先级或结合性。

~~~cpp
class Example{
public:
    Example(int x, int y) : _x(x), _y(y){}
    
    // 重载运算符
    Example operator + (const Example & other) const{
        return Example(_x + other._x, _y + other._y);
    }
    // 声明友元函数，在函数体外重载
    friend Example operator - (const Example & a, const Example & b);
    
    // 重载 << 运算符
    friend std::ostream & operator << (std::ostream & os, const Example & example);
    
    void print() const{
        std::cout << "(" << _x << "," << _y << ")" << std::endl;
    }
private:
    int _x;
    int _y;
};

// 定义重载的减号运算符
Example operator - (const Example & a, const Example & b){
    return Example(a._x - b._x, a._y - b._y);
}

// 定义重载的 << 运算符
std::ostream & operator << (std::ostream & os, const Example & example){
    os << "Example x : " << example._x << " y :" << example._y << std::endl;
    return os;
}

~~~

