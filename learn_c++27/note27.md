## 简介

C++的标准模板库（STL）提供了多种通用容器，用于存储和管理数据。这些容器各有特点，适用于不同的应用场景。理解每种容器的用法和内部实现原理，对于编写高效且可维护的代码至关重要。本教案将详细介绍几种常用的STL容器，包括`vector`、`list`、`deque`、`map`、`unordered_map`、`set`、`unordered_set`以及容器适配器如`stack`、`queue`和`priority_queue`。

------

## `vector`：动态数组

### 用法

`vector`是STL中最常用的序列容器之一，提供了动态大小的数组功能。它支持随机访问，允许在末尾高效地添加和删除元素。

### 内部实现原理

`vector`在内部使用动态数组（通常是连续的内存块）来存储元素。当需要扩展容量时，它会分配一块更大的内存，将现有元素复制到新内存中，然后释放旧内存。这种策略在平均情况下保证了`push_back`的常数时间复杂度。

### 性能特性

- **随机访问**：支持常数时间的随机访问（`O(1)`）。
- **末尾插入/删除**：`push_back`和`pop_back`操作在摊销分析下是常数时间（`O(1)`）。
- **中间插入/删除**：在中间位置插入或删除元素需要移动后续元素，时间复杂度为线性时间（`O(n)`）。

### 应用场景

- 需要频繁随机访问元素。
- 主要在容器末尾进行插入和删除操作。
- 当容器大小不需要频繁调整（避免频繁的内存重新分配）。

### 代码示例

```cpp
#include <iostream>
#include <vector>

int main() {
    // 创建一个空的整数vector
    std::vector<int> numbers;

    // 向vector末尾添加元素
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);

    // 通过索引访问元素
    std::cout << "第一个元素: " << numbers[0] << std::endl;

    // 遍历vector
    std::cout << "所有元素: ";
    for(auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 删除最后一个元素
    numbers.pop_back();

    // 打印删除后的vector
    std::cout << "删除最后一个元素后: ";
    for(auto num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 输出

```makefile
第一个元素: 10
所有元素: 10 20 30 
删除最后一个元素后: 10 20
```

------

## `list`：双向链表

### 用法

`list`是一个实现了双向链表的数据结构，适合在容器中间频繁插入和删除元素。与`vector`不同，`list`不支持随机访问，但在任何位置的插入和删除操作都是常数时间。

### 内部实现原理

`list`在内部使用双向链表，每个元素包含指向前一个和后一个元素的指针。这使得在已知位置插入或删除元素时，无需移动其他元素，只需更新指针即可。

### 性能特性

- **随机访问**：不支持随机访问，访问第`n`个元素需要线性时间（`O(n)`）。
- **中间插入/删除**：已知位置的插入和删除操作是常数时间（`O(1)`）。
- **遍历**：顺序遍历，适合需要频繁遍历但不需要随机访问的场景。

### 应用场景

- 需要在容器中间频繁插入或删除元素。
- 不需要进行随机访问。
- 对内存的局部性要求不高（链表元素在内存中不连续）。

### 代码示例

```cpp
#include <iostream>
#include <list>

int main() {
    // 创建一个空的整数list
    std::list<int> numbers;

    // 向list末尾添加元素
    numbers.push_back(100);
    numbers.push_back(200);
    numbers.push_back(300);

    // 向list前端添加元素
    numbers.push_front(50);

    // 遍历list
    std::cout << "所有元素: ";
    for(auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // 插入元素
    auto it = numbers.begin();
    ++it; // 指向第二个元素
    numbers.insert(it, 150);

    // 打印插入后的list
    std::cout << "插入元素后: ";
    for(auto num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // 删除元素
    numbers.remove(200);

    // 打印删除后的list
    std::cout << "删除元素后: ";
    for(auto num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### 输出

```makefile
所有元素: 50 100 200 300 
插入元素后: 50 150 100 200 300 
删除元素后: 50 150 100 300
```

## 模拟实现一个简化版的 `List`

为了更好地理解 `std::list` 的内部工作原理，我们可以尝试模拟实现一个简化版的双向链表。下面将逐步介绍如何设计和实现这个 `List` 类。

### 类设计

我们的 `List` 类将包含以下组件：

1. **节点结构体（Node）**：表示链表的每个节点。
2. **迭代器类（Iterator）**：允许用户遍历链表。
3. **`List` 类**：管理链表的基本操作，如插入、删除和遍历。

### 节点结构体

每个节点包含数据域和前后指针：

```cpp
template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& value = T()) : data(value), prev(nullptr), next(nullptr) {}
};
```

### 迭代器实现

为了实现双向迭代器，我们需要定义一个 `Iterator` 类，支持 `++` 和 `--` 操作。

```cpp
template<typename T>
class List;

template<typename T>
class Iterator {
public:
    using self_type = Iterator<T>;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    Iterator(Node<T>* ptr = nullptr) : node_ptr(ptr) {}

    // Dereference operator
    reference operator*() const { return node_ptr->data; }

    // Arrow operator
    pointer operator->() const { return &(node_ptr->data); }

    // Pre-increment
    self_type& operator++() {
        if (node_ptr) node_ptr = node_ptr->next;
        return *this;
    }

    // Post-increment
    self_type operator++(int) {
        self_type temp = *this;
        ++(*this);
        return temp;
    }

    // Pre-decrement
    self_type& operator--() {
        if (node_ptr) node_ptr = node_ptr->prev;
        return *this;
    }

    // Post-decrement
    self_type operator--(int) {
        self_type temp = *this;
        --(*this);
        return temp;
    }

    // Equality comparison
    bool operator==(const self_type& other) const {
        return node_ptr == other.node_ptr;
    }

    // Inequality comparison
    bool operator!=(const self_type& other) const {
        return node_ptr != other.node_ptr;
    }

private:
    Node<T>* node_ptr;

    friend class List<T>;
};
```

### `List` 类

`List` 类提供链表的基本功能。

```cpp
#include <iostream>

template<typename T>
class List {
public:
    using iterator = Iterator<T>;
    using const_iterator = Iterator<T>;

    // 构造函数
    List() {
        head = new Node<T>(); // 哨兵节点
        tail = new Node<T>(); // 哨兵节点
        head->next = tail;
        tail->prev = head;
    }

    // 析构函数
    ~List() {
        clear();
        delete head;
        delete tail;
    }

    // 禁止拷贝构造和赋值操作（简化实现）
    List(const List& other) = delete;
    List& operator=(const List& other) = delete;

    // 插入元素到迭代器位置之前
    iterator insert(iterator pos, const T& value) {
        Node<T>* current = pos.node_ptr;
        Node<T>* new_node = new Node<T>(value);

        Node<T>* prev_node = current->prev;

        new_node->next = current;
        new_node->prev = prev_node;

        prev_node->next = new_node;
        current->prev = new_node;

        return iterator(new_node);
    }

    // 删除迭代器指向的元素
    iterator erase(iterator pos) {
        Node<T>* current = pos.node_ptr;
        if (current == head || current == tail) {
            // 不能删除哨兵节点
            return pos;
        }

        Node<T>* prev_node = current->prev;
        Node<T>* next_node = current->next;

        prev_node->next = next_node;
        next_node->prev = prev_node;

        delete current;

        return iterator(next_node);
    }

    // 在头部插入元素
    void push_front(const T& value) {
        insert(begin(), value);
    }

    // 在尾部插入元素
    void push_back(const T& value) {
        insert(end(), value);
    }

    // 在头部删除元素
    void pop_front() {
        if (!empty()) {
            erase(begin());
        }
    }

    // 在尾部删除元素
    void pop_back() {
        if (!empty()) {
            iterator temp = end();
            --temp;
            erase(temp);
        }
    }

    // 获取头元素引用
    T& front() {
        return head->next->data;
    }

    // 获取尾元素引用
    T& back() {
        return tail->prev->data;
    }

    // 判断是否为空
    bool empty() const {
        return head->next == tail;
    }

    // 获取链表大小（O(n)复杂度）
    size_t size() const {
        size_t count = 0;
        for(auto it = begin(); it != end(); ++it) {
            ++count;
        }
        return count;
    }

    // 清空链表
    void clear() {
        Node<T>* current = head->next;
        while(current != tail) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head->next = tail;
        tail->prev = head;
    }

    // 获取开始迭代器
    iterator begin() {
        return iterator(head->next);
    }

    // 获取结束迭代器
    iterator end() {
        return iterator(tail);
    }

    // 打印链表（辅助函数）
    void print() const {
        Node<T>* current = head->next;
        while(current != tail) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

private:
    Node<T>* head; // 头哨兵
    Node<T>* tail; // 尾哨兵
};
```

### 完整代码示例

下面是一个完整的示例，包括创建 `List` 对象，进行各种操作，并打印结果。

```cpp
#include <iostream>

// 节点结构体
template<typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& value = T()) : data(value), prev(nullptr), next(nullptr) {}
};

// 迭代器类
template<typename T>
class Iterator {
public:
    using self_type = Iterator<T>;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    Iterator(Node<T>* ptr = nullptr) : node_ptr(ptr) {}

    // Dereference operator
    reference operator*() const { return node_ptr->data; }

    // Arrow operator
    pointer operator->() const { return &(node_ptr->data); }

    // Pre-increment
    self_type& operator++() {
        if (node_ptr) node_ptr = node_ptr->next;
        return *this;
    }

    // Post-increment
    self_type operator++(int) {
        self_type temp = *this;
        ++(*this);
        return temp;
    }

    // Pre-decrement
    self_type& operator--() {
        if (node_ptr) node_ptr = node_ptr->prev;
        return *this;
    }

    // Post-decrement
    self_type operator--(int) {
        self_type temp = *this;
        --(*this);
        return temp;
    }

    // Equality comparison
    bool operator==(const self_type& other) const {
        return node_ptr == other.node_ptr;
    }

    // Inequality comparison
    bool operator!=(const self_type& other) const {
        return node_ptr != other.node_ptr;
    }

private:
    Node<T>* node_ptr;

    friend class List<T>;
};

// List 类
template<typename T>
class List {
public:
    using iterator = Iterator<T>;
    using const_iterator = Iterator<T>;

    // 构造函数
    List() {
        head = new Node<T>(); // 头哨兵
        tail = new Node<T>(); // 尾哨兵
        head->next = tail;
        tail->prev = head;
    }

    // 析构函数
    ~List() {
        clear();
        delete head;
        delete tail;
    }

    // 禁止拷贝构造和赋值操作（简化实现）
    List(const List& other) = delete;
    List& operator=(const List& other) = delete;

    // 插入元素到迭代器位置之前
    iterator insert(iterator pos, const T& value) {
        Node<T>* current = pos.node_ptr;
        Node<T>* new_node = new Node<T>(value);

        Node<T>* prev_node = current->prev;

        new_node->next = current;
        new_node->prev = prev_node;

        prev_node->next = new_node;
        current->prev = new_node;

        return iterator(new_node);
    }

    // 删除迭代器指向的元素
    iterator erase(iterator pos) {
        Node<T>* current = pos.node_ptr;
        if (current == head || current == tail) {
            // 不能删除哨兵节点
            return pos;
        }

        Node<T>* prev_node = current->prev;
        Node<T>* next_node = current->next;

        prev_node->next = next_node;
        next_node->prev = prev_node;

        delete current;

        return iterator(next_node);
    }

    // 在头部插入元素
    void push_front(const T& value) {
        insert(begin(), value);
    }

    // 在尾部插入元素
    void push_back(const T& value) {
        insert(end(), value);
    }

    // 在头部删除元素
    void pop_front() {
        if (!empty()) {
            erase(begin());
        }
    }

    // 在尾部删除元素
    void pop_back() {
        if (!empty()) {
            iterator temp = end();
            --temp;
            erase(temp);
        }
    }

    // 获取头元素引用
    T& front() {
        return head->next->data;
    }

    // 获取尾元素引用
    T& back() {
        return tail->prev->data;
    }

    // 判断是否为空
    bool empty() const {
        return head->next == tail;
    }

    // 获取链表大小（O(n)复杂度）
    size_t size() const {
        size_t count = 0;
        for(auto it = begin(); it != end(); ++it) {
            ++count;
        }
        return count;
    }

    // 清空链表
    void clear() {
        Node<T>* current = head->next;
        while(current != tail) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head->next = tail;
        tail->prev = head;
    }

    // 获取开始迭代器
    iterator begin() {
        return iterator(head->next);
    }

    // 获取结束迭代器
    iterator end() {
        return iterator(tail);
    }

    // 打印链表（辅助函数）
    void print() const {
        Node<T>* current = head->next;
        while(current != tail) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

private:
    Node<T>* head; // 头哨兵
    Node<T>* tail; // 尾哨兵
};

// 测试代码
int main() {
    List<int> lst;

    // 插入元素
    lst.push_back(10);    // 链表: 10
    lst.push_front(5);    // 链表: 5, 10
    lst.push_back(15);    // 链表: 5, 10, 15
    lst.insert(++lst.begin(), 7); // 链表: 5, 7, 10, 15

    // 打印链表
    std::cout << "链表内容: ";
    lst.print(); // 输出: 5 7 10 15

    // 删除元素
    lst.pop_front(); // 链表: 7, 10, 15
    lst.pop_back();  // 链表: 7, 10

    // 打印链表
    std::cout << "删除头尾后链表内容: ";
    lst.print(); // 输出: 7 10

    // 插入和删除
    auto it = lst.begin();
    lst.insert(it, 3);  // 链表: 3, 7, 10
    lst.erase(++it);    // 链表: 3, 10

    // 打印链表
    std::cout << "插入和删除后链表内容: ";
    lst.print(); // 输出: 3 10

    // 清空链表
    lst.clear();
    std::cout << "清空后，链表是否为空: " << (lst.empty() ? "是" : "否") << std::endl;

    return 0;
}
```

### 代码解释

1. **节点结构体 `Node`**：包含数据域 `data`，前驱指针 `prev` 和后继指针 `next`。

2. **迭代器类 `Iterator`**：

   - **构造函数**：接受一个 `Node<T>*` 指针。

   - 重载操作符

     ：

     - `*` 和 `->` 用于访问节点数据。
     - `++` 和 `--` 支持前向和后向遍历。
     - `==` 和 `!=` 用于比较迭代器。

3. **`List` 类**：

   - 成员变量

     ：

     - `head` 和 `tail` 是头尾哨兵节点。

   - **构造函数**：初始化头尾哨兵，并将它们互相连接。

   - **析构函数**：清空链表并删除哨兵节点。

   - **`insert`**：在指定位置前插入新节点。

   - **`erase`**：删除指定位置的节点。

   - **`push_front` 和 `push_back`**：分别在头部和尾部插入元素。

   - **`pop_front` 和 `pop_back`**：分别删除头部和尾部元素。

   - **`front` 和 `back`**：访问头尾元素。

   - **`empty` 和 `size`**：检查链表是否为空和获取链表大小。

   - **`clear`**：清空链表。

   - **`begin` 和 `end`**：返回开始和结束迭代器。

   - **`print`**：辅助函数，用于打印链表内容。

4. **测试代码**：创建 `List<int>` 对象，并执行一系列的插入、删除和遍历操作，验证 `List` 类的功能。

### 编译和运行

保存上述代码到一个名为 `List.cpp` 的文件中，然后使用以下命令编译和运行：

```bash
g++ -std=c++11 -o List List.cpp
./List
```

**输出结果：**

```makefile
链表内容: 5 7 10 15 
删除头尾后链表内容: 7 10 
插入和删除后链表内容: 3 10 
清空后，链表是否为空: 是
```
## 迭代器分类

### 1. 迭代器（Iterator）简介

在 C++ 中，**迭代器** 是一种用于遍历容器（如 `std::vector`、`std::list` 等）元素的对象。它们提供了类似指针的接口，使得算法可以独立于具体的容器而工作。迭代器的设计允许算法以统一的方式处理不同类型的容器。

------

### 2. 迭代器类别（Iterator Categories）

为了使不同类型的迭代器能够支持不同的操作，C++ 标准库将迭代器分为以下几种类别，每种类别支持的操作能力逐级增强：

1. **输入迭代器（Input Iterator）**
2. **输出迭代器（Output Iterator）**
3. **前向迭代器（Forward Iterator）**
4. **双向迭代器（Bidirectional Iterator）**
5. **随机访问迭代器（Random Access Iterator）**
6. **无效迭代器（Contiguous Iterator）**（C++20 引入）

每个类别都继承自前一个类别，具备更强的功能。例如，双向迭代器不仅支持前向迭代器的所有操作，还支持反向迭代（即可以向后移动）。

**主要迭代器类别及其特性**

| 类别             | 支持的操作                                             | 示例容器                              |
| ---------------- | ------------------------------------------------------ | ------------------------------------- |
| 输入迭代器       | 只读访问、单向前进                                     | 单向链表 `std::forward_list`          |
| 输出迭代器       | 只写访问、单向前进                                     | 输出流 `std::ostream_iterator`        |
| 前向迭代器       | 读写访问、单向前进                                     | 向量 `std::vector`                    |
| 双向迭代器       | 读写访问、单向前进和反向迭代                           | 双向链表 `std::list`                  |
| 随机访问迭代器   | 读写访问、单向前进、反向迭代、跳跃移动（支持算术运算） | 向量 `std::vector`、队列 `std::deque` |
| 无效迭代器（新） | 随机访问迭代器的所有功能，且元素在内存中连续排列       | 新的 C++ 容器如 `std::span`           |

------

### 3. `iterator_category` 的作用

`iterator_category` 是迭代器类型中的一个别名，用于标识该迭代器所属的类别。它是标准库中 **迭代器特性（Iterator Traits）** 的一部分，标准算法会根据迭代器的类别优化其行为。

### 为什么需要 `iterator_category`

标准库中的算法（如 `std::sort`、`std::find` 等）需要知道迭代器支持哪些操作，以便选择最优的实现方式。例如：

- 对于**随机访问迭代器**，可以使用快速的随机访问算法（如快速排序）。
- 对于**双向迭代器**，只能使用适用于双向迭代的算法（如归并排序）。
- 对于**输入迭代器**，只能进行单次遍历，许多复杂算法无法使用。

通过指定 `iterator_category`，你可以让标准算法了解你自定义迭代器的能力，从而选择合适的方法进行操作。

### `iterator_category` 的声明

在你的自定义迭代器类中，通过以下方式声明迭代器类别：

```cpp
using iterator_category = std::bidirectional_iterator_tag;
```

这表示该迭代器是一个 **双向迭代器**，支持向前和向后遍历。

------

### 4. `std::bidirectional_iterator_tag` 详解

`std::bidirectional_iterator_tag` 是一个标签（Tag），用于标识迭代器类别。C++ 标准库中有多个这样的标签，分别对应不同的迭代器类别：

- `std::input_iterator_tag`
- `std::output_iterator_tag`
- `std::forward_iterator_tag`
- `std::bidirectional_iterator_tag`
- `std::random_access_iterator_tag`
- `std::contiguous_iterator_tag`（C++20）

这些标签本质上是空的结构体，用于类型区分。在标准算法中，通常会通过这些标签进行 **重载选择（Overload Resolution）** 或 **特化（Specialization）**，以实现针对不同迭代器类别的优化。

### 继承关系

迭代器标签是有继承关系的：

- `std::forward_iterator_tag` 继承自 `std::input_iterator_tag`
- `std::bidirectional_iterator_tag` 继承自 `std::forward_iterator_tag`
- `std::random_access_iterator_tag` 继承自 `std::bidirectional_iterator_tag`
- `std::contiguous_iterator_tag` 继承自 `std::random_access_iterator_tag`

这种继承关系反映了迭代器类别的能力层级。例如，**双向迭代器** 具备 **前向迭代器** 的所有能力，加上反向遍历的能力。

------

### 5. 迭代器特性（Iterator Traits）详解

C++ 提供了 **迭代器特性（Iterator Traits）**，通过模板类 `std::iterator_traits` 来获取迭代器的相关信息。通过这些特性，标准算法可以泛化地处理不同类型的迭代器。

### 迭代器特性包含的信息

`std::iterator_traits` 提供以下信息：

- `iterator_category`：迭代器类别标签。
- `value_type`：迭代器指向的元素类型。
- `difference_type`：迭代器间的距离类型（通常是 `std::ptrdiff_t`）。
- `pointer`：指向元素的指针类型。
- `reference`：对元素的引用类型。

### 自定义迭代器与 `iterator_traits`

当你定义自己的迭代器时，确保提供这些类型别名，以便标准库算法能够正确识别和使用你的迭代器。例如：

```cpp
template<typename T>
class Iterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = T;
    using difference_type   = std::ptrdiff_t;
    using pointer           = T*;
    using reference         = T&;

    // 其他成员函数...
};
```

这样，使用 `std::iterator_traits<Iterator<T>>` 时，就能正确获取迭代器的特性。

------