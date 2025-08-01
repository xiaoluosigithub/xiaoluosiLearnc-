## 指针基础

在C++中，指针是一种特殊的变量，它存储的是另一个变量的内存地址，而不是数据本身。通过使用指针，我们可以直接访问和操作内存中的数据。指针也叫做地址。

### 和引用的区别

指针（pointer）是“指向（point to）”另外一种类型的复合类型。与引用类似，指针也实现了对其他对象的间接访问。然而指针与引用相比又有很多不同点。

其一，指针本身就是一个对象，允许对指针赋值和拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象。

其二，指针无须在定义时赋初值。和其他内置类型一样，在块作用域内定义的指针如果没有被初始化，也将拥有一个不确定的值。

```cpp
//声明一个指向整数的指针，可以不赋初值
int *ptr;
//ip1和ip2都是指向int类型对象的指针
int *ip1, *ip2;
//dp2是指向double类型对象的指针,dp是double型对象
double dp, *dp2;
```

这里，`ptr` 是一个指针变量，它可以存储一个整数的内存地址。

### 指针赋值

我们可以通过如下方式(&变量)获取一个变量的地址

```cpp
变量地址 = &变量名
```

指针可以通过两种方式赋值：

1. **直接赋值内存地址**：这通常不是常规做法，因为直接操作内存地址可能会导致未定义行为。
2. **赋值变量的地址**：这是更常见的做法，使用取地址运算符（&）来获取变量的地址，并将其赋值给指针。

```cpp
//定义ptr2并且赋值，指向var地址
int var = 10;
int *ptr2 = &var;
```

这里，`ptr` 被赋值为 `var` 的内存地址。

我们对上述代码进行图解：

[![https://cdn.llfc.club/fb06f3724d53b3d9f9157aa9e0062a9.png](https://cdn.llfc.club/fb06f3724d53b3d9f9157aa9e0062a9.png)](https://cdn.llfc.club/fb06f3724d53b3d9f9157aa9e0062a9.png)

`ptr2`指向`var`的地址，也就是`ptr2`存储的是`var`的地址`0x2be3`。因为`ptr2`也是对象，所以计算机也会为它开辟空间，`ptr2`自己的地址为`0x3f2b`.

所以指针的地址也可以用另一个指针变量存储

```cpp
//定义ptr2并且赋值，指向var地址
int var = 10;
int *ptr2 = &var;
//ptr_address 存储ptr2的地址
int** ptr_address = &ptr2;
std::cout << "var 的地址为: " << &var << std::endl;
std::cout << "ptr2 存储的值为: " << ptr2 << std::endl;
std::cout << "ptr2 地址为: " << &ptr2 << std::endl;
std::cout << "ptr_address 的值为: " << ptr_address << std::endl;
```

上述代码打印结果为

```bash
var 的地址为: 0xad6a5ffc24
ptr2 存储的值为: 0xad6a5ffc24
ptr2 地址为: 0xad6a5ffc18
ptr_address 的值为: 0xad6a5ffc18
```

可以看到我们通过`ptr_address` 可以存储`ptr2`的地址, `ptr_address`存储的是指针的地址，所以它是一个指针的指针类型(`int**`)，也叫做二级指针。

### 类型匹配

因为在声明语句中指针的类型实际上被用于指定它所指向的对象的类型，所以二者必须匹配。

如果指针指向了一个其他类型的对象，那么会产生错误。

```cpp
double dval = 3.14;
//正确，初始值是double类型的对象的地址
double *pd = &dval;
//正确，初始值是指向double对象的指针
double *pd2 = pd;
//错误,pi的类型和pd类型不匹配
//int * pi = pd;
//错误，视图把double型对象的地址赋值给int型指针
//int * pi = &dval;
```



### 指针值

指针的值（即地址）应属下列4种状态之一：

1.指向一个对象。

2.指向紧邻对象所占空间的下一个位置。

3.空指针，意味着指针没有指向任何对象。

4.无效指针，也就是上述情况之外的其他值。

试图拷贝或以其他方式访问无效指针的值都将引发错误。编译器并不负责检查此类错误，这一点和试图使用未经初始化的变量是一样的。

访问无效指针的后果无法预计，因此程序员必须清楚任意给定的指针是否有效。

尽管第2种和第3种形式的指针是有效的，但其使用同样受到限制。显然这些指针没有指向任何具体对象，所以试图访问此类指针（假定的）对象的行为不被允许。如果这样做了，后果也无法预计。

### 利用指针访问对象

我们可以利用`*`(解引用操作符)获取指针所指向的对象的数据，写法如下

```cpp
数据变量 = *指针
```

[![https://cdn.llfc.club/1726532931384.jpg](https://cdn.llfc.club/1726532931384.jpg)](https://cdn.llfc.club/1726532931384.jpg)

我们看下这个例子

```cpp
//访问对象
int ival = 42;
//p_int存放着ival的地址，或者说p_int是指向变量ival的指针
int * p_int = &ival;
//由符号*得到指针p所指向的对象，输出42
std::cout << *p_int ;
```

上面的例子通过`*p_int`获取`p_int`所指向的对象`ival`的值。输出42

### 利用指针修改对象

因为指针存储的是对象的地址，通过解引用获取对象的数据，我们也可以通过解引用修改对象的值，基本格式为

```cpp
//访问对象
int ival = 42;
//p_int存放着ival的地址，或者说p_int是指向变量ival的指针
int * p_int = &ival;
//由符号*得到指针p所指向的对象，输出42
std::cout << *p_int << std::endl;
//由符号*得到指针p所指向的对象，即可经由p_int为变量ival赋值
*p_int = 0;
std::cout << * p_int << std::endl;
//打印ival的值
std::cout << "ival 的值为" << ival << std::endl;
```

**注意**

解引用操作仅适用于那些确实指向了某个对象的有效指针

```cpp
//初始化一个空指针
int* empty_pointer = nullptr;
//打印空指针数据,非法
//std::cout << "空指针指向数据是 " << *empty_pointer << std::endl;
```

## 符号的多重含义

像&和＊这样的符号，既能用作表达式里的运算符，也能作为声明的一部分出现，符号的上下文决定了符号的意义：

```cpp
//符号的多重含义
int ival2 = 42;
//& 紧跟着类型名出现，因此是声明的一部分，r是一个引用
int &r = ival2;
//* 紧跟着类型名出现，因此是声明的一部分，p是一个指针
int *p;
// &出现在表达式中，是一个取地址符号
p = &ival2;
// * 出现在表达式中，是一个解引用符号
*p = ival2;
//& 是声明的一部分，*是一个解引用符号
int &r2 = *p;
```

## 空指针

空指针包含几种定义方式

```cpp
//空指针定义方式
//C++11 最推荐方式
int *p1 = nullptr;
//直接将p2初始化为字面量0
int *p2 = 0;
//需要使用#include<cstdlib>
//等价于int * p3 = 0;
int *p3 = NULL;
std::cout << "p1: " << p1 << std::endl;
std::cout << "p2: " << p2 << std::endl;
std::cout << "p3: " << p3 << std::endl;
```

得到空指针最直接的办法就是用字面值`nullptr`来初始化指针，这也是C++11新标准刚刚引入的一种方法。

`nullptr`是一种特殊类型的字面值。

另一种办法就如对`p2`的定义一样，也可以通过将指针初始化为字面值0来生成空指针。

过去的程序还会用到一个名为NULL的预处理变量（preprocessor variable）来给指针赋值，这个变量在头文件`cstdlib`中定义，它的值就是0。

**注意事项**

把int变量直接赋给指针是错误的操作，即使int变量的值恰好等于0也不行

```cpp
int zero = 0;
pi = zero;
```

## 地址变换

我们可以修改指针指向的地址，进而达到指向其他变量的目的.

指针和引用都能提供对其他对象的间接访问，然而在具体实现细节上二者有很大不同，其中最重要的一点就是引用本身并非一个对象。

一旦定义了引用，就无法令其再绑定到另外的对象，之后每次使用这个引用都是访问它最初绑定的那个对象。

指针和它存放的地址之间就没有这种限制了。和其他任何变量（只要不是引用）一样，给指针赋值就是令它存放一个新的地址，从而指向一个新的对象：

```cpp
int ival3 = 42;
//pval3 被初始化，但没有指向任何对象
int *pval3 = 0;
//pval4被初始化，指向ival3的地址
int* pval4 = &ival3;
//将pval3的指向改为pval4的指向，二者同时指向ival3
pval3 = pval4;
std::cout <<"ival3 的地址为：" << &ival3 << std::endl;
std::cout <<"pval3 指向的地址为 " << pval3 << std::endl;
std::cout <<"pval4 指向的地址为 " << pval4 << std::endl;
```

运行上述程序可以看到输出

```bash
ival3 的地址为：0xf8329ff7a4
pval3 指向的地址为 0xf8329ff7a4
pval4 指向的地址为 0xf8329ff7a4
```

## 指针判空

有时候我们需要判断指针是否为空，可以通过`if`判断，`if`大家没学，此处仅作演示和理解。

在C++ 中0为false，非0为true，所以一个空指针通过`if`判断，是false， 非空指针为true

```cpp
//空指针判断
int * empty_pointer2 = nullptr;
if(!empty_pointer){
    std::cout << "empty_pointer is empty" << std::endl;
}

int test = 100;
int * normal_pointer2 = &test;
if(normal_pointer2){
    std::cout << "normal pointer is not empty" << std::endl;
}
```

指针同样可以支持比较运算,判断相等（==），判断不等(!=)。

```cpp
//判断指针是否相等
if(normal_pointer2 != empty_pointer){
    std::cout << "normal_pointer 和 empty_pointer 不相等"<< std::endl;
}
```

## 万能指针

void＊是一种特殊的指针类型，可用于存放任意对象的地址。一个void＊指针存放着一个地址，这一点和其他指针类似。不同的是，我们对该地址中到底是个什么类型的对象并不了解：

```cpp
//万能指针
double obj = 3.14, *obj_pd = &obj;
//void 可以存放任何类型的对象的地址
void * pv = &obj;
//pv 可以存储任意类型的地址
pv = obj_pd;
```

利用void＊指针能做的事儿比较有限：

拿它和别的指针比较、作为函数的输入或输出，或者赋给另外一个void＊指针。

不能直接操作void＊指针所指的对象，因为我们并不知道这个对象到底是什么类型，也就无法确定能在这个对象上做哪些操作。

## 指向指针的指针

以指针为例，指针是内存中的对象，像其他对象一样也有自己的地址，因此允许把指针的地址再存放到另一个指针当中。通过＊的个数可以区分指针的级别。也就是说，＊＊表示指向指针的指针，＊＊＊表示指向指针的指针的指针，以此类推：

```cpp
//以指针为例，指针是内存中的对象，像其他对象一样也有自己的地址，
// 因此允许把指针的地址再存放到另一个指针当中。通过＊的个数可以区分指针的级别。
// 也就是说，＊＊表示指向指针的指针，＊＊＊表示指向指针的指针的指针，以此类推：
int ival4= 1024;
// pival4指向了int型的数
int *pival4 = &ival4;
//ppi指向了一个int型的指针
int ** ppi = &pival4;

std::cout << "The value of ival\n"
    << "direct value: " << ival4 << "\n"
    << "indirect value: " << *pival4 << "\n"
    << "doubly indirect value : " << **ppi
    << std::endl;
```

该程序使用三种不同的方式输出了变量ival的值：第一种直接输出；第二种通过int型指针pi输出；第三种两次解引用ppi，取得ival的值。

[![https://cdn.llfc.club/1726537605315.jpg](https://cdn.llfc.club/1726537605315.jpg)](https://cdn.llfc.club/1726537605315.jpg)

## 指向指针的引用

引用本身不是一个对象，因此不能定义指向引用的指针。但指针是对象，所以存在对指针的引用：

```cpp
//引用本身不是一个对象，因此不能定义指向引用的指针。
// 但指针是对象，所以存在对指针的引用
int init = 42;
// pinit是一个int型的指针
int *pinit;
// rpinit是一个对指针pinit的引用
int *& rpinit = pinit;
// rpinit引用了一个指针，因此给rpinit赋值&init就是令pinit指向init
rpinit = &init;
//解引用rpinit得到i,也就是p指向的对象，将init改为0
*rpinit = 0;
```

## 指针运算

指针可以进行算术运算，如递增（++）和递减（--），这些操作会改变指针所指向的内存地址。但是，这种操作仅限于指向数组元素的指针。

#### 指针和数组

在C++中，数组名在表达式中通常被当作指向数组首元素的指针。

```cpp
//指针可以进行算术运算，如递增（++）和递减（--），
// 这些操作会改变指针所指向的内存地址。但是，这种操作仅限于指向数组元素的指针。
int arr[5] = {1, 2, 3, 4, 5};
int *ptr_arr = arr;
std::cout << "ptr_arr is : " << ptr_arr << std::endl;
int firstElement = *ptr_arr;
std::cout << "firstElement is " << firstElement << std::endl;
// 递增指针
++ptr_arr; // ptr 现在指向 arr[1]
std::cout << "ptr_arr is : " << ptr_arr << std::endl;
// 访问新位置的值
int secondElement = *ptr_arr; // secondElement 等于 2
std::cout << "secondElement is " << secondElement;
```

上述程序输出 

```bash
ptr_arr is : 0x3160fffa30
firstElement is 1
ptr_arr is : 0x3160fffa34
secondElement is 2
```

[![https://cdn.llfc.club/1726537913155.jpg](https://cdn.llfc.club/1726537913155.jpg)](https://cdn.llfc.club/1726537913155.jpg)

## 注意事项

#### 

- 指针必须在使用前被初始化，否则它们可能包含垃圾值，导致未定义行为。
- 指针运算（如递增和递减）仅适用于指向数组元素的指针。
- 指针的解引用操作必须确保指针不是空指针（`nullptr`），否则会导致运行时错误。