## `const`限定符

### 1 `const` 的定义与作用

`const` 是 C++ 关键字，用于指示变量的值不可修改。通过使用 `const`，可以提高代码的安全性与可读性，防止无意中修改变量的值。

### 2 `const` 在变量声明中的位置

`const` 关键字通常放在变量类型之前，例如：

```cpp
const int a = 10;
```

也可以放在类型之后，但这种用法较少见：

```cpp
int const a = 10;
```

可以用一个变量初始化常量， 也可以将一个常量赋值给一个变量

```cpp
//可以用一个变量初始化常量
int i1 = 10;
const int i2 = i1;
//也可以将一个常量赋值给一个变量
int i3 = i2;
```

`const`变量必须初始化

```cpp
//错误用法，const变量必须初始化
//const int i4;
```

### 3 编译器如何处理 `const` 修饰的变量

`const` 修饰的变量在编译时会被视为只读，尝试修改其值会导致编译错误。此外，编译器可能会对 `const` 变量进行优化，如将其存储在只读内存区域。

**注意**

> 默认状态下，`const`对象仅在文件内有效

当以编译时初始化的方式定义一个`const`对象时，就如对`bufSize`的定义一样：

```cpp
const int bufSize = 512;
```

编译器将在编译过程中把用到该变量的地方都替换成对应的值。也就是说，编译器会找到代码中所有用到`bufSize`的地方，然后用512替换。

为了执行上述替换，编译器必须知道变量的初始值。

如果程序包含多个文件，则每个用了`const`对象的文件都必须得能访问到它的初始值才行。要做到这一点，就必须在每一个用到变量的文件中都有对它的定义.

为了支持这一用法，同时避免对同一变量的重复定义，默认情况下，`const`对象被设定为仅在文件内有效。当多个文件中出现了同名的`const`变量时，其实等同于在不同文件中分别定义了独立的变量。

我们创建一个`global.h`文件和`global.cpp`文件, 我们知道头文件只做变量的声明，之前我们在头文件添加变量的定义会导致连接错误。

那如果我们添加`const`变量的定义

```cpp
#ifndef DAY08_CONST_GLOBAL_H
#define DAY08_CONST_GLOBAL_H
const int bufSize = 100;
#endif //DAY08_CONST_GLOBAL_H
```

在`main.cpp`和`global.cpp`中包含`global.h`，发现可以编译通过，虽然`main.cpp`和`global.cpp`中包含了同名的`bufSize`，但却是不同的变量，运行程序可以编译通过。

有时候我们不想定义不同的`const`变量，可以在`global.h`中用`extern`声明`bufSize`

```cpp
extern const int bufSize2;
```

在`global.cpp`中定义

```cpp
const int bufSize2 = 10;
```

同样可以编译通过。

为了验证我们的说法，我们可以在`global.h`中声明一个函数,用来打印两个变量的地址

```cpp
//打印bufSize地址和bufSize2地址
extern void PrintBufAddress();
```

在`global.cpp`中实现`PrintBufAddress()`

```cpp
void PrintBufAddress(){
    std::cout << "global.cpp buf address: " << &bufSize << std::endl;
    std::cout << "global.cpp buf2 address: " << &bufSize2 << std::endl;
}
```

然后我们在`main.cpp`中调用`PrintBufAddress()`函数，并且在`main.cpp`中打印两个变量地址

```cpp
PrintBufAddress();
//输出bufSize地址
std::cout << "main.cpp buf address is " << &bufSize << std::endl;
//输出bufSize2地址
std::cout << "main.cpp buf2 address is " << &bufSize2 << std::endl;
```

程序输出

```bash
global.cpp buf address: 0x7ff67a984040
global.cpp buf2 address: 0x7ff67a984044
main.cpp buf address is 0x7ff67a984000
main.cpp buf2 address is 0x7ff67a984044
```

可以看出`global.cpp`中的`bufSize`和`main.cpp`中的`bufSize`不是同一个变量

**技巧**

> 如果想在多个文件之间共享`const`对象，必须在变量的定义之前添加extern关键字。