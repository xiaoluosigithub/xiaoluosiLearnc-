## 重定义问题如何解决

### 产生原因

前文我们说过头文件只能用来做文件的声明，源文件用来做文件的实现。如果我们在头文件中定义变量会怎么样呢？

假设我们在`global.h`中定义了两个变量

```cpp
#ifndef DAY05_EXTERN_GLOBAL_H
#define DAY05_EXTERN_GLOBAL_H
#include <string>
int global_age = 10;
std::string global_name = "llfc";
#endif //DAY05_EXTERN_GLOBAL_H
```

然后我们创建`global.cpp`包含`global.h`

```cpp
#include "global.h"
```

然后我们在`main.cpp`中包含`global.h`

```cpp
#include <iostream>
#include "global.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "globbal name is" << global_name << std::endl;
    std::cout << "global age is " << global_age << std::endl;
    return 0;
}
```

我们运行上述代码, 程序编译并未产生问题,但是链接产生问题了

```bash
[1/3] Building CXX object CMakeFiles/day05_extern.dir/global.cpp.obj
[2/3] Building CXX object CMakeFiles/day05_extern.dir/main.cpp.obj
[3/3] Linking CXX executable day05_extern.exe
FAILED: day05_extern.exe
```

再往下看

```cpp
multiple definition of `global_age'; CMakeFiles/day05_extern.dir/main.cpp.obj: /global.h:8: first defined here
multiple definition of `global_name[abi:cxx11]'; CMakeFiles/day05_extern.dir/main.cpp.obj:/global.h:9: first defined here
```

上述报错的意思是在链接`main.cpp.obj`时发现`global_age`重定义，第一次定义在`global.h`这里。

同样链接`mian.cpp.obj`时发现global_name重定义，第一次定义在`global.h`。

因为`global.h`中定义了`global_age`，根据我们之前学习的预编译知识，只要是包含`global.h`的文件都会展开`global.h`，`main.cpp`展开了一次，`global.cpp`展开了一次

### 解决办法

#### extern的作用

在C++中，`extern` 关键字用于声明一个变量或函数是在另一个文件或同一个文件的其他位置定义的。这主要用于处理全局变量或函数声明，确保在多个源文件中能够正确地链接到这些全局变量或函数的定义。

#### 解决办法

可以采用**extern**关键字声明变量，然后将变量的定义放在`global.cpp`中, 这样`main.cpp`包含`global.h`就只会展开声明。声明可以重复声明，不会有问题。

在`global.h`中用extern声明两个变量

```cpp
#ifndef DAY05_EXTERN_GLOBAL_H
#define DAY05_EXTERN_GLOBAL_H
#include <string>
extern int global_age ;
extern std::string global_name ;
#endif //DAY05_EXTERN_GLOBAL_H
```

在`global.cpp`中定义这些变量

```cpp
#include "global.h"
#include <string>
// 定义全局变量
std::string global_name = "John Doe";
int global_age = 30;
```

在`main.cpp`中包含`global.h`

```cpp
#include <iostream>
#include "global.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "globbal name is" << global_name << std::endl;
    std::cout << "global age is " << global_age << std::endl;
    return 0;
}
```

再次编译，运行成功

```bash
Hello, World!
globbal name isJohn Doe
global age is 30
```

### 总结

- 头文件只做变量的声明，不能做变量的定义
- 头文件声明变量可以采用extern的方式