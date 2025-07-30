## 什么是结构体？

结构体（**structure**，简称 **struct**）是一种用户自定义的数据类型，用于将多个不同类型的数据组合在一起。它允许在一个单一的单元中存储多个相关的数据项，使代码更具组织性和可读性。

## 结构体在编程中的应用场景

- **数据组织**：将相关的数据组合，如学生信息、坐标点、日期等。
- **传递数据**：在函数之间传递多个相关的数据项。
- **复杂数据处理**：管理更复杂的数据结构，如链表、树、图等。

## 结构体的基本使用

### 定义和声明结构体

在 C++ 中，使用 `struct` 关键字定义一个结构体。基本语法如下：

```cpp
struct StructName {
    // 成员变量
    dataType1 member1;
    dataType2 member2;
    // ...
};
```

**示例：定义一个学生结构体**

```cpp
struct Student {
    int id;
    std::string name;
    float grade;
};
```

#### 创建结构体变量

定义结构体后，可以创建结构体类型的变量。

```cpp
Student student1;
Student student2;
```

#### 访问结构体成员

使用点运算符（`.`）访问结构体成员。

```cpp
student1.id = 1001;
student1.name = "Alice";
student1.grade = 89.5f;

std::cout << "学生ID: " << student1.id << std::endl;
std::cout << "学生姓名: " << student1.name << std::endl;
std::cout << "学生成绩: " << student1.grade << std::endl;
```

#### 结构体初始化

可以在创建结构体变量时进行初始化。

**方法一：直观初始化**

```cpp
Student student3 = {1002, "Bob", 92.0f};
```

**方法二：逐个赋值**

```cpp
Student student4;
student4.id = 1003;
student4.name = "Charlie";
student4.grade = 85.0f;
```

**方法三：使用自定义构造函数**

虽然结构体的主要用途是数据存储，但在 C++ 中，结构体可以像类一样拥有构造函数。

```cpp
struct Student {
    int id;
    std::string name;
    float grade;

    // 构造函数
    Student(int studentId, std::string studentName, float studentGrade) :
        id(studentId), name(studentName), grade(studentGrade) {}
};

// 使用构造函数初始化
Student student5(1004, "Daisy", 95.0f);
```



## 结构体与类的比较

在 C++ 中，`struct` 和 `class` 有很多相似之处，但也有一些关键区别。

#### 类与结构体的相似之处

- 都可以包含成员变量和成员函数。
- 都支持访问控制（public、protected、private）。
- 都可以使用继承和多态。

#### 类与结构体的区别

**默认访问控制**

- **结构体（struct）**：默认成员访问权限为 `public`。
- **类（class）**：默认成员访问权限为 `private`。

**例子**

```cpp
struct StructExample {
    int x; // 默认 public
};

class ClassExample {
    int y; // 默认 private
};
```

**用途习惯**

- **结构体（struct）**：通常用于纯数据结构，主要存储数据，成员通常是公开的。
- **类（class）**：用于包含数据和操作数据的函数，支持更加复杂的封装。

**实例比较**

```cpp
struct Point {
    int x;
    int y;
};

class Rectangle {
private:
    int width;
    int height;

public:
    void setDimensions(int w, int h) {
        width = w;
        height = h;
    }

    int area() const {
        return width * height;
    }

    int get_width(){
        return width;
    }
};

int main(){
    Rectangle rt;
    //错误，不能直接访问私有成员
    rt.width;
    //正确，可以通过公有成员函数访问
    rt.get_width();
}
```

## 结构体的高级用法

#### 嵌套结构体

结构体可以包含其他结构体作为成员。

**示例：嵌套地址结构体**

```cpp
struct Address {
    std::string city;
    std::string street;
    int houseNumber;
};

struct Person {
    std::string name;
    int age;
    Address address; // 嵌套结构体
};

int main() {
    Person person;
    person.name = "Eve";
    person.age = 30;
    person.address.city = "New York";
    person.address.street = "5th Avenue";
    person.address.houseNumber = 101;

    std::cout << person.name << " lives at " 
              << person.address.houseNumber << " " 
              << person.address.street << ", " 
              << person.address.city << std::endl;

    return 0;
}
```

**输出：**

```sql
Eve lives at 101 5th Avenue, New York
```

#### 结构体数组

可以创建包含多个结构体的数组，用于存储多个相同类型的数据项。

**示例：存储多个学生信息的数组**

```cpp
struct Student {
    int id;
    std::string name;
    float grade;
};

int main() {
    // 创建包含3个学生信息的数组
    Student students[3] = {
        {1001, "Alice", 89.5f},
        {1002, "Bob", 92.0f},
        {1003, "Charlie", 85.0f}
    };

    for (int i = 0; i < 3; ++i) {
        std::cout << "学生ID: " << students[i].id 
                  << ", 姓名: " << students[i].name 
                  << ", 成绩: " << students[i].grade << std::endl;
    }

    return 0;
}
```

**输出：**

```makefile
学生ID: 1001, 姓名: Alice, 成绩: 89.5
学生ID: 1002, 姓名: Bob, 成绩: 92
学生ID: 1003, 姓名: Charlie, 成绩: 85
```

#### 结构体指针

可以创建指向结构体的指针，并通过指针访问结构体成员。

**示例：使用结构体指针**

```cpp
struct Car {
    std::string brand;
    std::string model;
    int year;
};

int main() {
    Car car = {"Toyota", "Camry", 2020};
    Car* carPtr = &car;

    std::cout << "品牌: " << carPtr->brand << std::endl;
    std::cout << "型号: " << carPtr->model << std::endl;
    std::cout << "年份: " << carPtr->year << std::endl;

    return 0;
}
```

**输出：**

```makefile
品牌: Toyota
型号: Camry
年份: 2020
```

#### 使用 `typedef` 简化结构体定义

使用 `typedef`（或 `using` 关键字）可以为结构体类型创建别名，使代码更简洁。

**示例：使用 `typedef`**

```cpp
typedef struct {
    int id;
    std::string name;
    float grade;
} Student;

// 或者使用 `using`（C++11 及以上）
using Student = struct {
    int id;
    std::string name;
    float grade;
};
```

**应用：**

```cpp
int main() {
    Student s1 = {1004, "Daisy", 95.0f};
    std::cout << "学生ID: " << s1.id 
              << ", 姓名: " << s1.name 
              << ", 成绩: " << s1.grade << std::endl;
    return 0;
}
```

**输出：**

```makefile
学生ID: 1004, 姓名: Daisy, 成绩: 95
```

### 5. 结构体中的函数

虽然结构体主要用于存储数据，但在 C++ 中，结构体也可以包含成员函数。这使得结构体更具面向对象的特性。

**示例：在结构体中定义成员函数**

```cpp
#include <iostream>
#include <string>

struct Book {
    std::string title;
    std::string author;
    int pages;

    // 成员函数
    void printInfo() const {
        std::cout << "书名: " << title 
                  << ", 作者: " << author 
                  << ", 页数: " << pages << std::endl;
    }
};

int main() {
    Book myBook = {"C++ Primer", "Stanley B. Lippman", 976};
    myBook.printInfo();
    return 0;
}
```

**输出：**

```less
书名: C++ Primer, 作者: Stanley B. Lippman, 页数: 976
```

#### 使用结构体作为函数参数和返回值

**传递结构体给函数**

```cpp
struct Point {
    int x;
    int y;
};

// 通过值传递
void printPoint(Point p) {
    std::cout << "Point(" << p.x << ", " << p.y << ")" << std::endl;
}

// 通过引用传递
void movePoint(Point& p, int dx, int dy) {
    p.x += dx;
    p.y += dy;
}

int main() {
    Point p1 = {10, 20};
    printPoint(p1);

    movePoint(p1, 5, -5);
    printPoint(p1);

    return 0;
}
```

**输出：**

```scss
Point(10, 20)
Point(15, 15)
```

**从函数返回结构体**

```cpp
struct Rectangle {
    int width;
    int height;
};

// 计算面积的结构体
struct Area {
    int value;
};

// 函数返回结构体
Area calculateArea(Rectangle rect) {
    Area area;
    area.value = rect.width * rect.height;
    return area;
}

int main() {
    Rectangle rect = {5, 10};
    Area rectArea = calculateArea(rect);
    std::cout << "矩形面积: " << rectArea.value << std::endl;
    return 0;
}
```

**输出：**

```makefile
矩形面积: 50
```