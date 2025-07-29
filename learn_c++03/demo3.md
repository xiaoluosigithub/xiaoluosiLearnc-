## 头文件和源文件

在C++中，头文件（.h 或 .hpp 文件）和源文件（.cpp 文件）是组织代码的重要部分，它们共同工作以构建程序。这种分离有助于模块化和代码重用，同时也使得编译过程更加高效。

### 头文件（.h 或 .hpp）

头文件主要用于**声明**（declarations），包括：

- 类（class）的声明
- 函数（functions）的原型（prototypes）
- 模板（templates）的声明
- 宏定义（#define）
- 外部变量（extern variables）的声明
- 内联函数（inline functions）

头文件通常包含预处理指令如 `#ifndef`、`#define` 和 `#endif`，这些指令用于防止头文件被重复包含（也称为“头文件保护”或“包含卫士”）。























