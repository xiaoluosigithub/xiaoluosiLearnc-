

## c++类

## 基本定义

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



## 成员变量和成员函数



## 访问控制符

- **public**：公有成员，可以被所有代码访问。
- **private**：私有成员，仅能被类的成员函数和友元访问。
- **protected**：受保护成员，仅能被类的成员函数、友元和派生类访问。



## 构造函数

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



## 析构函数

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

