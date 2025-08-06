## 运算符重载概述

**运算符重载（Operator Overloading）**允许开发者为自定义类型定义或重新定义运算符的行为，使得自定义类型的对象能够使用与内置类型相同的运算符进行操作。这不仅提高了代码的可读性，还增强了代码的表达能力。

## 为什么需要运算符重载

在面向对象编程中，我们经常需要定义自己的类来表示某些实体（如复数、向量、矩形等）。为了使这些类的对象能够与内置类型一样方便地进行操作，运算符重载显得尤为重要。例如：

- 对于复数类，使用 `+` 运算符进行加法运算。
- 对于字符串类，使用 `<<` 运算符进行输出。
- 对于矩阵类，使用 `*` 运算符进行矩阵乘法。

通过运算符重载，可以使代码更简洁、直观，类似于数学表达式。

## 运算符重载的规则与限制

1. **不能改变运算符的优先级和结合性**：运算符的优先级和结合性在编译阶段就确定，不能通过重载来改变。
2. **不能创建新的运算符**：仅能重载C++中已有的运算符，不能定义新的运算符。
3. **至少有一个操作数必须是用户定义的类型**：不能对两个内置类型进行运算符重载。
4. **某些运算符不能重载**：包括 `.`（成员选择运算符）、`.*`、`::`、`?:`（条件运算符）等。
5. **重载运算符的优先级和结合性不可改变**。

## 运算符重载的方法

在C++中，运算符可以通过成员函数或非成员函数（通常是友元函数）来重载。

### 成员函数方式

运算符作为类的成员函数进行重载时，左操作数是当前对象（`this`）。因此，对于需要修改左操作数的运算符，成员函数方式通常更直观。

**语法示例**：

```cpp
class ClassName {
public:
    ClassName operator+(const ClassName& other);
};
```

### 非成员函数方式（友元函数）

当需要对两个不同类型的对象进行运算，或者左操作数不是当前类的对象时，通常使用非成员函数方式。为了访问类的私有成员，非成员函数通常被声明为类的友元函数。

**语法示例**：

```cpp
class ClassName {
    friend ClassName operator+(const ClassName& lhs, const ClassName& rhs);
};
```

## 1. 算术运算符

### 1.1 `+` 运算符

**作用**：实现两个对象的加法操作。

**示例类**：`Complex`（复数类）

```cpp
#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    // 构造函数
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 重载 + 运算符（成员函数）
    Complex operator+(const Complex& other) const {
        return Complex(this->real + other.real, this->imag + other.imag);
    }

    // 重载 << 运算符用于输出
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

// 实现 << 运算符
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real;
    if (c.imag >= 0)
        os << " + " << c.imag << "i)";
    else
        os << " - " << -c.imag << "i)";
    return os;
}

// 示例
int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.5, -2.5);
    Complex c3 = c1 + c2;
    std::cout << "c1 + c2 = " << c3 << std::endl;
    return 0;
}
```

**输出**：

```go
c1 + c2 = (4.5 + 1.5i)
```

### 1.2 `-` 运算符

**作用**：实现两个对象的减法操作。

**示例类**：`Complex`（复数类）

```cpp
// ...（与上面类似）

// 重载 - 运算符（成员函数）
Complex operator-(const Complex& other) const {
    return Complex(this->real - other.real, this->imag - other.imag);
}

// 示例
int main() {
    Complex c1(5.0, 6.0);
    Complex c2(2.5, -1.5);
    Complex c4 = c1 - c2;
    std::cout << "c1 - c2 = " << c4 << std::endl;
    return 0;
}
```

**输出**：

```go
c1 - c2 = (2.5 + 7.5i)
```

### 1.3 `*` 运算符

**作用**：实现对象的乘法操作。

**示例类**：`Complex`（复数类）

```cpp
// ...（与上面类似）

// 重载 * 运算符（成员函数）
Complex operator*(const Complex& other) const {
    double r = this->real * other.real - this->imag * other.imag;
    double i = this->real * other.imag + this->imag * other.real;
    return Complex(r, i);
}

// 示例
int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.5, -2.5);
    Complex c5 = c1 * c2;
    std::cout << "c1 * c2 = " << c5 << std::endl;
    return 0;
}
```

**输出**：

```go
c1 * c2 = (13.5 + 1i)
```

### 1.4 `/` 运算符

**作用**：实现对象的除法操作。

**示例类**：`Complex`（复数类）

```cpp
#include <stdexcept>

// ...（与上面类似）

// 重载 / 运算符（成员函数）
Complex operator/(const Complex& other) const {
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0) {
        throw std::invalid_argument("除数为零！");
    }
    double r = (this->real * other.real + this->imag * other.imag) / denominator;
    double i = (this->imag * other.real - this->real * other.imag) / denominator;
    return Complex(r, i);
}

// 示例
int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.5, -2.5);
    try {
        Complex c6 = c1 / c2;
        std::cout << "c1 / c2 = " << c6 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }
    return 0;
}
```

**输出**：

```go
c1 / c2 = (-0.823529 + 1.64706i)
```

------

## 2. 赋值运算符

### 2.1 `=` 运算符

**作用**：实现对象的赋值操作。

**示例类**：`Complex`（复数类）

C++编译器会自动生成默认的拷贝赋值运算符，但当类中包含动态分配内存或需要自定义行为时，需要自行重载。

```cpp
#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
    // 构造函数
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 拷贝赋值运算符（成员函数）
    Complex& operator=(const Complex& other) {
        if (this == &other)
            return *this; // 防止自赋值
        this->real = other.real;
        this->imag = other.imag;
        return *this;
    }

    // 重载 << 运算符用于输出
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

// 实现 << 运算符
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real;
    if (c.imag >= 0)
        os << " + " << c.imag << "i)";
    else
        os << " - " << -c.imag << "i)";
    return os;
}

// 示例
int main() {
    Complex c1(3.0, 4.0);
    Complex c2;
    c2 = c1; // 使用拷贝赋值运算符
    std::cout << "c2 = " << c2 << std::endl;
    return 0;
}
```

**输出**：

```ini
c2 = (3 + 4i)
```

### 2.2 复合赋值运算符（`+=`, `-=`, `*=`, `/=`）

**作用**：实现复合赋值操作，如 `+=`，`-=` 等。

**示例类**：`Complex`（复数类）

```cpp
// ...（与上面类似）

// 重载 += 运算符（成员函数）
Complex& operator+=(const Complex& other) {
    this->real += other.real;
    this->imag += other.imag;
    return *this;
}

// 重载 -= 运算符（成员函数）
Complex& operator-=(const Complex& other) {
    this->real -= other.real;
    this->imag -= other.imag;
    return *this;
}

// 重载 *= 运算符（成员函数）
Complex& operator*=(const Complex& other) {
    double r = this->real * other.real - this->imag * other.imag;
    double i = this->real * other.imag + this->imag * other.real;
    this->real = r;
    this->imag = i;
    return *this;
}

// 重载 /= 运算符（成员函数）
Complex& operator/=(const Complex& other) {
    double denominator = other.real * other.real + other.imag * other.imag;
    if (denominator == 0) {
        throw std::invalid_argument("除数为零！");
    }
    double r = (this->real * other.real + this->imag * other.imag) / denominator;
    double i = (this->imag * other.real - this->real * other.imag) / denominator;
    this->real = r;
    this->imag = i;
    return *this;
}

// 示例
int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);

    c1 += c2;
    std::cout << "c1 += c2: " << c1 << std::endl;

    c1 -= c2;
    std::cout << "c1 -= c2: " << c1 << std::endl;

    c1 *= c2;
    std::cout << "c1 *= c2: " << c1 << std::endl;

    try {
        c1 /= c2;
        std::cout << "c1 /= c2: " << c1 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    return 0;
}
```

**输出**：

```go
c1 += c2: (4 + 6i)
c1 -= c2: (3 + 4i)
c1 *= c2: (-5 + 10i)
c1 /= c2: (2 + 0i)
```

------

## 3. 比较运算符

### 3.1 `==` 运算符

**作用**：判断两个对象是否相等。

**示例类**：`Complex`（复数类）

```cpp
// ...（与上面类似）

// 重载 == 运算符（友元函数）
friend bool operator==(const Complex& lhs, const Complex& rhs);

// 实现 == 运算符
bool operator==(const Complex& lhs, const Complex& rhs) {
    return (lhs.real == rhs.real) && (lhs.imag == rhs.imag);
}

// 示例
int main() {
    Complex c1(3.0, 4.0);
    Complex c2(3.0, 4.0);
    Complex c3(1.5, -2.5);

    if (c1 == c2)
        std::cout << "c1 和 c2 相等" << std::endl;
    else
        std::cout << "c1 和 c2 不相等" << std::endl;

    if (c1 == c3)
        std::cout << "c1 和 c3 相等" << std::endl;
    else
        std::cout << "c1 和 c3 不相等" << std::endl;

    return 0;
}
```

**输出**：

```undefined
c1 和 c2 相等
c1 和 c3 不相等
```

### 3.2 `!=` 运算符

**作用**：判断两个对象是否不相等。

**示例类**：`Complex`（复数类）

```cpp
// ...（与上面类似）

// 重载 != 运算符（友元函数）
friend bool operator!=(const Complex& lhs, const Complex& rhs);

// 实现 != 运算符
bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}

// 示例
int main() {
    Complex c1(3.0, 4.0);
    Complex c2(3.0, 4.0);
    Complex c3(1.5, -2.5);

    if (c1 != c2)
        std::cout << "c1 和 c2 不相等" << std::endl;
    else
        std::cout << "c1 和 c2 相等" << std::endl;

    if (c1 != c3)
        std::cout << "c1 和 c3 不相等" << std::endl;
    else
        std::cout << "c1 和 c3 相等" << std::endl;

    return 0;
}
```

**输出**：

```undefined
c1 和 c2 相等
c1 和 c3 不相等
```

### 3.3 `<`, `>`, `<=`, `>=` 运算符

**作用**：实现对象之间的大小比较。对于复数来说，通常没有自然的大小顺序，但为了示例，可以定义复数的模长进行比较。

**示例类**：`Complex`（复数类）

```cpp
#include <cmath>

// ...（与上面类似）

// 重载 < 运算符（友元函数）
friend bool operator<(const Complex& lhs, const Complex& rhs);

// 重载 > 运算符（友元函数）
friend bool operator>(const Complex& lhs, const Complex& rhs);

// 重载 <= 运算符（友元函数）
friend bool operator<=(const Complex& lhs, const Complex& rhs);

// 重载 >= 运算符（友元函数）
friend bool operator>=(const Complex& lhs, const Complex& rhs);

// 实现 < 运算符
bool operator<(const Complex& lhs, const Complex& rhs) {
    double lhs_mod = std::sqrt(lhs.real * lhs.real + lhs.imag * lhs.imag);
    double rhs_mod = std::sqrt(rhs.real * rhs.real + rhs.imag * rhs.imag);
    return lhs_mod < rhs_mod;
}

// 实现 > 运算符
bool operator>(const Complex& lhs, const Complex& rhs) {
    return rhs < lhs;
}

// 实现 <= 运算符
bool operator<=(const Complex& lhs, const Complex& rhs) {
    return !(rhs < lhs);
}

// 实现 >= 运算符
bool operator>=(const Complex& lhs, const Complex& rhs) {
    return !(lhs < rhs);
}

// 示例
int main() {
    Complex c1(3.0, 4.0); // 模长 5
    Complex c2(1.0, 2.0); // 模长 sqrt(5) ≈ 2.236
    Complex c3(3.0, 4.0); // 模长 5

    if (c1 < c2)
        std::cout << "c1 的模长小于 c2 的模长" << std::endl;
    else
        std::cout << "c1 的模长不小于 c2 的模长" << std::endl;

    if (c1 > c2)
        std::cout << "c1 的模长大于 c2 的模长" << std::endl;
    else
        std::cout << "c1 的模长不大于 c2 的模长" << std::endl;

    if (c1 <= c3)
        std::cout << "c1 的模长小于或等于 c3 的模长" << std::endl;
    else
        std::cout << "c1 的模长大于 c3 的模长" << std::endl;

    if (c1 >= c3)
        std::cout << "c1 的模长大于或等于 c3 的模长" << std::endl;
    else
        std::cout << "c1 的模长小于 c3 的模长" << std::endl;

    return 0;
}
```

**输出**：

```undefined
c1 的模长不小于 c2 的模长
c1 的模长大于 c2 的模长
c1 的模长小于或等于 c3 的模长
c1 的模长大于或等于 c3 的模长
```

------

## 4. 逻辑运算符

### 4.1 `&&`, `||`, `!` 运算符

**作用**：实现逻辑操作。需要注意，C++ 中的 `&&` 和 `||` 运算符无法短路地重载，而且通常不建议重载它们，因为会改变其原有的逻辑语义。通常，建议使用类型转换或其他方法来实现逻辑判断。

**示例类**：`Boolean` 类（用于示例）

```cpp
#include <iostream>

class Boolean {
private:
    bool value;

public:
    // 构造函数
    Boolean(bool val = false) : value(val) {}

    // 重载逻辑非运算符（!）（成员函数）
    bool operator!() const {
        return !value;
    }

    // 重载逻辑与运算符（&）（非短路）（成员函数）
    Boolean operator&(const Boolean& other) const {
        return Boolean(this->value & other.value);
    }

    // 重载逻辑或运算符（|）（非短路）（成员函数）
    Boolean operator|(const Boolean& other) const {
        return Boolean(this->value | other.value);
    }

    // 重载输出运算符
    friend std::ostream& operator<<(std::ostream& os, const Boolean& b);
};

// 实现 << 运算符
std::ostream& operator<<(std::ostream& os, const Boolean& b) {
    os << (b.value ? "true" : "false");
    return os;
}

// 示例
int main() {
    Boolean b1(true);
    Boolean b2(false);

    Boolean b3 = b1 & b2;
    Boolean b4 = b1 | b2;
    Boolean b5 = !b1;
    Boolean b6 = !b2;

    std::cout << "b1 & b2 = " << b3 << std::endl;
    std::cout << "b1 | b2 = " << b4 << std::endl;
    std::cout << "!b1 = " << b5 << std::endl;
    std::cout << "!b2 = " << b6 << std::endl;

    return 0;
}
```

**输出**：

```yaml
b1 & b2 = false
b1 | b2 = true
!b1 = false
!b2 = true
```

**说明**：

- **注意**：在重载 `&&` 和 `||` 运算符时，要明白它们不会具有短路行为。因此，通常不建议重载这两个运算符。
- 本例中，使用 `&` 和 `|` 运算符来模拟逻辑与、或操作。

------

## 5. 位运算符

### 5.1 `&`, `|`, `^`, `~` 运算符

**作用**：实现位级操作，如按位与、按位或、按位异或、按位取反。

**示例类**：`Bitmask` 类

```cpp
#include <iostream>

class Bitmask {
private:
    unsigned int bits;

public:
    // 构造函数
    Bitmask(unsigned int b = 0) : bits(b) {}

    // 重载 & 运算符（成员函数）
    Bitmask operator&(const Bitmask& other) const {
        return Bitmask(this->bits & other.bits);
    }

    // 重载 | 运算符（成员函数）
    Bitmask operator|(const Bitmask& other) const {
        return Bitmask(this->bits | other.bits);
    }

    // 重载 ^ 运算符（成员函数）
    Bitmask operator^(const Bitmask& other) const {
        return Bitmask(this->bits ^ other.bits);
    }

    // 重载 ~ 运算符（成员函数）
    Bitmask operator~() const {
        return Bitmask(~this->bits);
    }

    // 重载 << 运算符用于输出
    friend std::ostream& operator<<(std::ostream& os, const Bitmask& b);
};

// 实现 << 运算符
std::ostream& operator<<(std::ostream& os, const Bitmask& b) {
    os << "0x" << std::hex << b.bits << std::dec;
    return os;
}

// 示例
int main() {
    Bitmask bm1(0b10101010); // 0xAA
    Bitmask bm2(0b11001100); // 0xCC

    Bitmask bm3 = bm1 & bm2;
    Bitmask bm4 = bm1 | bm2;
    Bitmask bm5 = bm1 ^ bm2;
    Bitmask bm6 = ~bm1;

    std::cout << "bm1 & bm2 = " << bm3 << std::endl;
    std::cout << "bm1 | bm2 = " << bm4 << std::endl;
    std::cout << "bm1 ^ bm2 = " << bm5 << std::endl;
    std::cout << "~bm1 = " << bm6 << std::endl;

    return 0;
}
```

**输出**：

```undefined
bm1 & bm2 = 0x88
bm1 | bm2 = 0xee
bm1 ^ bm2 = 0x66
~bm1 = 0xffffff55
```

### 5.2 `<<`, `>>` 位移运算符

**作用**：实现位移操作，如左移、右移。

**示例类**：`Bitmask` 类

```cpp
// ...（与上面类似）

// 重载 << 运算符（左移，成员函数）
Bitmask operator<<(int shift) const {
    return Bitmask(this->bits << shift);
}

// 重载 >> 运算符（右移，成员函数）
Bitmask operator>>(int shift) const {
    return Bitmask(this->bits >> shift);
}

// 示例
int main() {
    Bitmask bm1(0b0001); // 0x1

    Bitmask bm2 = bm1 << 3;
    Bitmask bm3 = bm1 >> 1;

    std::cout << "bm1 << 3 = " << bm2 << std::endl;
    std::cout << "bm1 >> 1 = " << bm3 << std::endl;

    return 0;
}
```

**输出**：

```bash
bm1 << 3 = 0x8
bm1 >> 1 = 0x0
```

**说明**：

- 重载位移运算符时，通常接受一个整型参数，表示位移的位数。

------

## 6. 自增自减运算符

### 6.1 前置 `++` 和 `--` 运算符

**作用**：实现对象的自增和自减操作。

**示例类**：`Counter` 类

```cpp
#include <iostream>

class Counter {
private:
    int count;

public:
    // 构造函数
    Counter(int c = 0) : count(c) {}

    // 前置 ++ 运算符（成员函数）
    Counter& operator++() {
        ++count;
        return *this;
    }

    // 前置 -- 运算符（成员函数）
    Counter& operator--() {
        --count;
        return *this;
    }

    // 重载 << 运算符用于输出
    friend std::ostream& operator<<(std::ostream& os, const Counter& c);
};

// 实现 << 运算符
std::ostream& operator<<(std::ostream& os, const Counter& c) {
    os << c.count;
    return os;
}

// 示例
int main() {
    Counter c(10);
    std::cout << "初始值: " << c << std::endl;
    std::cout << "++c = " << ++c << std::endl;
    std::cout << "--c = " << --c << std::endl;
    return 0;
}
```

**输出**：

```diff
初始值: 10
++c = 11
--c = 10
```

### 6.2 后置 `++` 和 `--` 运算符

**作用**：实现对象的后置自增和自减操作。

**示例类**：`Counter` 类

```cpp
// ...（与上面类似）

// 后置 ++ 运算符（成员函数）
Counter operator++(int) {
    Counter temp = *this;
    ++count;
    return temp;
}

// 后置 -- 运算符（成员函数）
Counter operator--(int) {
    Counter temp = *this;
    --count;
    return temp;
}

// 示例
int main() {
    Counter c(10);
    std::cout << "初始值: " << c << std::endl;
    std::cout << "c++ = " << c++ << std::endl;
    std::cout << "c-- = " << c-- << std::endl;
    std::cout << "当前值: " << c << std::endl;
    return 0;
}
```

**输出**：

```makefile
初始值: 10
c++ = 10
c-- = 11
当前值: 10
```

**说明**：

- **前置运算符**：先修改对象，再返回引用。
- **后置运算符**：先保存原值，修改对象，再返回原值。

------

## 7. 下标运算符 `[]`

**作用**：实现对象的下标访问，如数组访问。

**示例类**：`Vector` 类

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

class Vector {
private:
    std::vector<double> components;

public:
    // 构造函数
    Vector(const std::vector<double>& comps) : components(comps) {}

    // 重载 [] 运算符（非 const）
    double& operator[](size_t index) {
        if (index >= components.size()) {
            throw std::out_of_range("下标越界！");
        }
        return components[index];
    }

    // 重载 [] 运算符（const）
    const double& operator[](size_t index) const {
        if (index >= components.size()) {
            throw std::out_of_range("下标越界！");
        }
        return components[index];
    }

    // 重载 << 运算符用于输出
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
};

// 实现 << 运算符
std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "(";
    for (size_t i = 0; i < v.components.size(); ++i) {
        os << v.components[i];
        if (i != v.components.size() - 1)
            os << ", ";
    }
    os << ")";
    return os;
}

// 示例
int main() {
    Vector v({1.0, 2.0, 3.0});
    std::cout << "初始向量: " << v << std::endl;

    // 访问元素
    try {
        std::cout << "v[1] = " << v[1] << std::endl;
        v[1] = 5.0;
        std::cout << "修改后向量: " << v << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    // 访问越界
    try {
        std::cout << "v[3] = " << v[3] << std::endl; // 越界
    } catch (const std::out_of_range& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    return 0;
}
```

**输出**：

```makefile
初始向量: (1, 2, 3)
v[1] = 2
修改后向量: (1, 5, 3)
错误: 下标越界！
```

**说明**：

- 提供了 `const` 和 非 `const` 两种重载，以支持不同上下文中的访问。
- 在访问时进行了边界检查，确保安全性。

------

## 8. 函数调用运算符 `()`

**作用**：使对象能够像函数一样被调用，常用于函数对象（functors）或仿函数。

**示例类**：`Multiplier` 类

```cpp
#include <iostream>

class Multiplier {
private:
    double factor;

public:
    // 构造函数
    Multiplier(double f = 1.0) : factor(f) {}

    // 重载 () 运算符（成员函数）
    double operator()(double x) const {
        return x * factor;
    }
};

// 示例
int main() {
    Multiplier double_it(2.0);
    Multiplier triple_it(3.0);

    std::cout << "double_it(5) = " << double_it(5) << std::endl;
    std::cout << "triple_it(5) = " << triple_it(5) << std::endl;

    return 0;
}
```

**输出**：

```undefined
double_it(5) = 10
triple_it(5) = 15
```

**说明**：

- 通过重载 `()` 运算符，`Multiplier` 对象可以像函数一样接受参数并进行操作。
- 常用于需要定制函数行为的场景，如排序时的比较函数。

------

## 9. 输入输出运算符 `<<`, `>>`

**作用**：实现对象与输入输出流之间的交互。

**示例类**：`Complex`（复数类）

```cpp
#include <iostream>
#include <stdexcept>

class Complex {
private:
    double real;
    double imag;

public:
    // 构造函数
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 重载 << 运算符（友元函数）
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);

    // 重载 >> 运算符（友元函数）
    friend std::istream& operator>>(std::istream& is, Complex& c);
};

// 实现 << 运算符
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real;
    if (c.imag >= 0)
        os << " + " << c.imag << "i)";
    else
        os << " - " << -c.imag << "i)";
    return os;
}

// 实现 >> 运算符
std::istream& operator>>(std::istream& is, Complex& c) {
    // 假设输入格式为：real imag
    is >> c.real >> c.imag;
    return is;
}

// 示例
int main() {
    Complex c1;
    std::cout << "请输入复数的实部和虚部，以空格分隔: ";
    std::cin >> c1;
    std::cout << "您输入的复数是: " << c1 << std::endl;
    return 0;
}
```

**示例输入**：

```makefile
请输入复数的实部和虚部，以空格分隔: 3.5 -2.1
```

**输出**：

```go
您输入的复数是: (3.5 - 2.1i)
```

**说明**：

- `<<` 运算符用于输出对象到流中。
- `>>` 运算符用于从流中输入对象的数据。
- 一般将这些运算符重载为友元函数，以便访问类的私有成员。

------

## 10. 其他运算符

### 10.1 成员访问运算符 `->`, `->*`

**说明**：

- 运算符 `->` 和 `->*` 通常用于代理模式或智能指针的实现，较为复杂。
- 其重载需要返回一个指针类型，以便进一步访问成员。
- 通常不建议普通类进行重载，除非有特定需求。

**示例类**：`Proxy` 类（代理模式）

```cpp
#include <iostream>

class RealObject {
public:
    void display() const {
        std::cout << "RealObject::display()" << std::endl;
    }
};

class Proxy {
private:
    RealObject* ptr;

public:
    // 构造函数
    Proxy(RealObject* p = nullptr) : ptr(p) {}

    // 重载 -> 运算符（成员函数）
    RealObject* operator->() const {
        return ptr;
    }
};

// 示例
int main() {
    RealObject real;
    Proxy proxy(&real);

    proxy->display(); // 使用重载的 -> 运算符
    return 0;
}
```

**输出**：

```cpp
RealObject::display()
```

**说明**：

- `Proxy` 类通过重载 `->` 运算符，将对 `Proxy` 对象的成员访问转发给其内部的 `RealObject` 对象。
- 这是实现代理模式或智能指针的常见方式。

------

## 综合案例：复数（Complex）类中的所有运算符重载

为了将上述所有运算符的重载整合在一个类中，以下是一个全面的 `Complex` 类示例，涵盖了大部分可重载的运算符。

```cpp
#include <iostream>
#include <cmath>
#include <stdexcept>

class Complex {
private:
    double real;
    double imag;

public:
    // 构造函数
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // 拷贝赋值运算符
    Complex& operator=(const Complex& other) {
        if (this == &other)
            return *this;
        this->real = other.real;
        this->imag = other.imag;
        return *this;
    }

    // 重载 + 运算符（成员函数）
    Complex operator+(const Complex& other) const {
        return Complex(this->real + other.real, this->imag + other.imag);
    }

    // 重载 - 运算符（成员函数）
    Complex operator-(const Complex& other) const {
        return Complex(this->real - other.real, this->imag - other.imag);
    }

    // 重载 * 运算符（成员函数）
    Complex operator*(const Complex& other) const {
        double r = this->real * other.real - this->imag * other.imag;
        double i = this->real * other.imag + this->imag * other.real;
        return Complex(r, i);
    }

    // 重载 / 运算符（成员函数）
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw std::invalid_argument("除数为零！");
        }
        double r = (this->real * other.real + this->imag * other.imag) / denominator;
        double i = (this->imag * other.real - this->real * other.imag) / denominator;
        return Complex(r, i);
    }

    // 重载 += 运算符
    Complex& operator+=(const Complex& other) {
        this->real += other.real;
        this->imag += other.imag;
        return *this;
    }

    // 重载 -= 运算符
    Complex& operator-=(const Complex& other) {
        this->real -= other.real;
        this->imag -= other.imag;
        return *this;
    }

    // 重载 *= 运算符
    Complex& operator*=(const Complex& other) {
        double r = this->real * other.real - this->imag * other.imag;
        double i = this->real * other.imag + this->imag * other.real;
        this->real = r;
        this->imag = i;
        return *this;
    }

    // 重载 /= 运算符
    Complex& operator/=(const Complex& other) {
        double denominator = other.real * other.real + other.imag * other.imag;
        if (denominator == 0) {
            throw std::invalid_argument("除数为零！");
        }
        double r = (this->real * other.real + this->imag * other.imag) / denominator;
        double i = (this->imag * other.real - this->real * other.imag) / denominator;
        this->real = r;
        this->imag = i;
        return *this;
    }

    // 重载 == 运算符
    friend bool operator==(const Complex& lhs, const Complex& rhs) {
        return (lhs.real == rhs.real) && (lhs.imag == rhs.imag);
    }

    // 重载 != 运算符
    friend bool operator!=(const Complex& lhs, const Complex& rhs) {
        return !(lhs == rhs);
    }

    // 重载 < 运算符（基于模长）
    friend bool operator<(const Complex& lhs, const Complex& rhs) {
        double lhs_mod = std::sqrt(lhs.real * lhs.real + lhs.imag * lhs.imag);
        double rhs_mod = std::sqrt(rhs.real * rhs.real + rhs.imag * rhs.imag);
        return lhs_mod < rhs_mod;
    }

    // 重载 > 运算符
    friend bool operator>(const Complex& lhs, const Complex& rhs) {
        return rhs < lhs;
    }

    // 重载 <= 运算符
    friend bool operator<=(const Complex& lhs, const Complex& rhs) {
        return !(rhs < lhs);
    }

    // 重载 >= 运算符
    friend bool operator>=(const Complex& lhs, const Complex& rhs) {
        return !(lhs < rhs);
    }

    // 重载 << 运算符
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real;
        if (c.imag >= 0)
            os << " + " << c.imag << "i)";
        else
            os << " - " << -c.imag << "i)";
        return os;
    }

    // 重载 >> 运算符
    friend std::istream& operator>>(std::istream& is, Complex& c) {
        // 简单输入格式：real imag
        is >> c.real >> c.imag;
        return is;
    }

    // 重载 ~ 运算符（取反复数）
    Complex operator~() const {
        return Complex(this->real, -this->imag);
    }

    // 重载逻辑非运算符（!）
    bool operator!() const {
        return (this->real == 0 && this->imag == 0);
    }

    // 重载下标运算符（如 c[0] 返回 real, c[1] 返回 imag）
    double& operator[](size_t index) {
        if (index == 0)
            return real;
        else if (index == 1)
            return imag;
        else
            throw std::out_of_range("下标越界！");
    }

    const double& operator[](size_t index) const {
        if (index == 0)
            return real;
        else if (index == 1)
            return imag;
        else
            throw std::out_of_range("下标越界！");
    }

    // 重载前置 ++ 运算符
    Complex& operator++() {
        ++real;
        ++imag;
        return *this;
    }

    // 重载后置 ++ 运符
    Complex operator++(int) {
        Complex temp = *this;
        ++real;
        ++imag;
        return temp;
    }

    // 重载前置 -- 运算符
    Complex& operator--() {
        --real;
        --imag;
        return *this;
    }

    // 重载后置 -- 运算符
    Complex operator--(int) {
        Complex temp = *this;
        --real;
        --imag;
        return temp;
    }

    // 重载函数调用运算符
    double operator()(const std::string& part) const {
        if (part == "real")
            return real;
        else if (part == "imag")
            return imag;
        else
            throw std::invalid_argument("参数错误！");
    }
};

// 示例
int main() {
    Complex c1(3.0, 4.0);
    Complex c2(1.5, -2.5);
    Complex c3;

    // 赋值运算
    c3 = c1;
    std::cout << "c3 = " << c3 << std::endl;

    // 加法
    Complex c4 = c1 + c2;
    std::cout << "c1 + c2 = " << c4 << std::endl;

    // 减法
    Complex c5 = c1 - c2;
    std::cout << "c1 - c2 = " << c5 << std::endl;

    // 乘法
    Complex c6 = c1 * c2;
    std::cout << "c1 * c2 = " << c6 << std::endl;

    // 除法
    try {
        Complex c7 = c1 / c2;
        std::cout << "c1 / c2 = " << c7 << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    // 比较运算
    if (c1 > c2)
        std::cout << "c1 的模长大于 c2" << std::endl;
    else
        std::cout << "c1 的模长不大于 c2" << std::endl;

    // 逻辑非运算
    Complex c_zero;
    if (!c1)
        std::cout << "c1 是零复数" << std::endl;
    else
        std::cout << "c1 不是零复数" << std::endl;

    if (!c_zero)
        std::cout << "c_zero 是零复数" << std::endl;
    else
        std::cout << "c_zero 不是零复数" << std::endl;

    // 取反运算
    Complex c_neg = ~c1;
    std::cout << "~c1 = " << c_neg << std::endl;

    // 下标运算
    try {
        std::cout << "c1[0] (real) = " << c1[0] << std::endl;
        std::cout << "c1[1] (imag) = " << c1[1] << std::endl;
        // std::cout << "c1[2] = " << c1[2] << std::endl; // 会抛出异常
    } catch (const std::out_of_range& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    // 自增自减运算符
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "++c1 = " << ++c1 << std::endl;
    std::cout << "c1++ = " << c1++ << std::endl;
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "--c1 = " << --c1 << std::endl;
    std::cout << "c1-- = " << c1-- << std::endl;
    std::cout << "c1 = " << c1 << std::endl;

    // 函数调用运算符
    std::cout << "c1 的实部: " << c1("real") << std::endl;
    std::cout << "c1 的虚部: " << c1("imag") << std::endl;

    // 输入运算
    std::cout << "请输入一个复数的实部和虚部，以空格分隔: ";
    Complex c_input;
    std::cin >> c_input;
    std::cout << "您输入的复数是: " << c_input << std::endl;

    return 0;
}
```

**示例运行**：

```go
c3 = (3 + 4i)
c1 + c2 = (4.5 + 1.5i)
c1 - c2 = (1.5 + 6.5i)
c1 * c2 = (13.5 + 1i)
c1 / c2 = (-0.823529 + 1.64706i)
c1 的模长大于 c2
c1 不是零复数
c_zero 是零复数
~c1 = (3 - 4i)
c1[0] (real) = 3
c1[1] (imag) = 4
c1 = (3 + 4i)
++c1 = (4 + 5i)
c1++ = (4 + 5i)
c1 = (5 + 6i)
--c1 = (4 + 5i)
c1-- = (4 + 5i)
c1 = (3 + 4i)
c1 的实部: 3
c1 的虚部: 4
请输入一个复数的实部和虚部，以空格分隔: 2.5 -3.5
您输入的复数是: (2.5 - 3.5i)
```

**说明**：

- 该类集成了大部分可重载的运算符，包括算术、赋值、比较、逻辑、位运算、自增自减、下标、函数调用以及输入输出运算符。
- 某些运算符（如 `&&`, `||`, `->*`）未在此示例中体现，因为它们的重载较为复杂且不常见。
- 在实际开发中，应根据需求选择性地重载运算符，避免过度设计。

------

## 11. 其他可重载运算符

### 11.1 逗号运算符 `,`

**作用**：实现对象在逗号表达式中的行为。

**示例类**：`Logger` 类（用于示例）

```cpp
#include <iostream>
#include <string>

class Logger {
private:
    std::string message;

public:
    // 构造函数
    Logger(const std::string& msg = "") : message(msg) {}

    // 重载逗号运算符（成员函数）
    Logger operator,(const Logger& other) const {
        // 简单示例：连接日志消息
        return Logger(this->message + ", " + other.message);
    }

    // 重载 << 运算符用于输出
    friend std::ostream& operator<<(std::ostream& os, const Logger& l);
};

// 实现 << 运算符
std::ostream& operator<<(std::ostream& os, const Logger& l) {
    os << l.message;
    return os;
}

// 示例
int main() {
    Logger log1("启动");
    Logger log2("加载配置");
    Logger log3("初始化");
    Logger combined = (log1, log2, log3);
    std::cout << "组合日志: " << combined << std::endl;
    return 0;
}
```

**输出**：

```makefile
组合日志: 启动, 加载配置, 初始化
```

**说明**：

- 重载 `,` 运算符可以自定义逗号表达式的行为，但在实际应用中不常见，应谨慎使用。
- 多个逗号运算符的重载会按从左至右的顺序依次调用。

------

## 运算符重载注意事项

1. **语义一致性**：重载运算符后，其行为应与运算符的传统意义保持一致。例如，`+` 应表示加法，避免引起混淆。
2. **效率**：尽量避免不必要的对象拷贝，可以通过返回引用或使用移动语义提升效率。
3. **异常安全**：在实现运算符重载时，考虑并处理可能的异常情况，确保程序的健壮性。
4. **封装性**：保持类的封装性，避免过度暴露内部细节。仅在必要时使用友元函数。
5. **返回类型**：根据运算符的用途选择合适的返回类型。例如，算术运算符通常返回新对象，赋值运算符返回引用等。
6. **避免复杂的逻辑**：运算符重载应简洁明了，不应包含过于复杂的逻辑，避免使代码难以理解和维护。
7. **可读性**：使用适当的注释和文档说明运算符重载的行为，增强代码的可读性。

------

## 小结

运算符重载是C++中强大的特性，允许开发者为自定义类定义或重新定义运算符的行为，使对象的操作更加直观和符合逻辑。在设计和实现运算符重载时，应遵循语义一致性、效率和封装性等原则，避免滥用。通过本教案中的详细案例，学习者可以全面理解运算符重载的应用，并在实际编程中灵活运用。