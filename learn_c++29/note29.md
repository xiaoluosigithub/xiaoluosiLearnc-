# std::map用法

`std::map` 是 C++ 标准模板库（STL）中的一个关联容器，用于存储键值对（key-value pairs），其中每个键都是唯一的，并且按照特定的顺序（通常是升序）自动排序。`std::map` 通常基于红黑树实现，提供对元素的高效查找、插入和删除操作。

## 1. 基本特性

- **有序性**：`std::map` 中的元素按照键的顺序自动排序，默认使用 `<` 运算符进行比较。
- **唯一键**：每个键在 `std::map` 中必须是唯一的，如果尝试插入重复的键，则插入操作会失败。
- **关联容器**：通过键快速访问对应的值，通常具有对数时间复杂度（O(log n)）。
- **可变性**：可以动态地插入和删除元素。

## 2. 头文件和命名空间

要使用 `std::map`，需要包含头文件 `<map>` 并使用 `std` 命名空间：

```cpp
#include <map>
#include <iostream>
#include <string>

using namespace std;
```

## 3. 声明和初始化

### 3.1 声明一个 `std::map`

```cpp
// 键为 int，值为 std::string 的 map
map<int, string> myMap;

// 键为 std::string，值为 double 的 map
map<string, double> priceMap;
```

### 3.2 初始化 `std::map`

可以使用初始化列表或其他方法初始化 `map`：

```cpp
map<int, string> myMap = {
    {1, "Apple"},
    {2, "Banana"},
    {3, "Cherry"}
};
```

## 4. 主要操作

### 4.1 插入元素

有几种方法可以向 `std::map` 中插入元素：

#### 4.1.1 使用 `insert` 函数

```cpp
myMap.insert(pair<int, string>(4, "Date"));
// 或者使用 `make_pair`
myMap.insert(make_pair(5, "Elderberry"));
// 或者使用初始化列表
myMap.insert({6, "Fig"});
```

#### 4.1.2 使用下标运算符 `[]`

```cpp
myMap[7] = "Grape";
// 如果键 8 不存在，则会插入键 8 并赋值
myMap[8] = "Honeydew";
```

**注意**：使用 `[]` 运算符时，如果键不存在，会自动插入该键，并将值初始化为类型的默认值。

### 4.2 访问元素

#### 4.2.1 使用下标运算符 `[]`

```cpp
string fruit = myMap[1]; // 获取键为 1 的值 "Apple"
```

**注意**：如果键不存在，`[]` 会插入该键并返回默认值。

#### 4.2.2 使用 `at` 成员函数

```cpp
try {
    string fruit = myMap.at(2); // 获取键为 2 的值 "Banana"
} catch (const out_of_range& e) {
    cout << "Key not found." << endl;
}
```

`at` 函数在键不存在时会抛出 `std::out_of_range` 异常，适合需要异常处理的场景。

#### 4.2.3 使用 `find` 成员函数

```cpp
auto it = myMap.find(3);
if (it != myMap.end()) {
    cout << "Key 3: " << it->second << endl; // 输出 "Cherry"
} else {
    cout << "Key 3 not found." << endl;
}
```

`find` 返回一个迭代器，指向找到的元素，若未找到则返回 `map::end()`。

### 4.3 删除元素

#### 4.3.1 使用 `erase` 函数

```cpp
// 按键删除
myMap.erase(2);

// 按迭代器删除
auto it = myMap.find(3);
if (it != myMap.end()) {
    myMap.erase(it);
}

// 删除区间 [first, last)
myMap.erase(myMap.begin(), myMap.find(5));
```

#### 4.3.2 使用 `clear` 函数

```cpp
myMap.clear(); // 删除所有元素
```

### 4.4 遍历 `std::map`

#### 4.4.1 使用迭代器

```cpp
for (map<int, string>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
    cout << "Key: " << it->first << ", Value: " << it->second << endl;
}
```

#### 4.4.2 使用基于范围的 `for` 循环（C++11 及以上）

```cpp
for (const auto& pair : myMap) {
    cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
}
```

### 4.5 常用成员函数

- **`size()`**：返回容器中元素的数量。
- **`empty()`**：判断容器是否为空。
- **`count(key)`**：返回具有指定键的元素数量（对于 `map`，返回 0 或 1）。
- **`lower_bound(key)`** 和 **`upper_bound(key)`**：返回迭代器，分别指向第一个不小于和第一个大于指定键的元素。
- **`equal_range(key)`**：返回一个范围，包含所有等于指定键的元素。

## 5. 自定义键的排序

默认情况下，`std::map` 使用 `<` 运算符对键进行排序。如果需要自定义排序方式，可以提供一个自定义的比较函数或函数对象。

### 5.1 使用函数对象

```cpp
struct Compare {
    bool operator()(const int& a, const int& b) const {
        return a > b; // 降序排序
    }
};

map<int, string, Compare> myMapDesc;
myMapDesc[1] = "Apple";
myMapDesc[2] = "Banana";
// ...
```

### 5.2 使用 lambda 表达式（C++11 及以上）

需要注意，`std::map` 的第三个模板参数必须是可比较类型，不能直接使用 lambda 表达式作为模板参数。不过，可以使用 `std::function` 或自定义结构体来包装 lambda。

```cpp
struct CompareLambda {
    bool operator()(const int& a, const int& b) const {
        return a > b; // 降序排序
    }
};

map<int, string, CompareLambda> myMapDesc;
myMapDesc[1] = "Apple";
// ...
```

## 6. `std::map` 与其他关联容器的比较

- **`std::unordered_map`**：基于哈希表实现，提供平均常数时间复杂度的查找、插入和删除操作，但不保证元素的顺序。适用于对顺序无要求且需要高效查找的场景。
- **`std::multimap`**：允许多个相同键的元素，其他特性与 `std::map` 类似。适用于需要存储重复键值对的场景。

## 7. 性能考虑

- 时间复杂度：
  - 查找、插入、删除：O(log n)
  - 遍历：O(n)
- **空间复杂度**：`std::map` 通常需要额外的空间来维护树结构，相比 `std::vector` 等序列容器，内存开销更大。

选择使用 `std::map` 还是其他容器，应根据具体需求和性能要求进行权衡。

## 8. 完整示例

以下是一个完整的示例，展示了 `std::map` 的基本用法：

```cpp
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    // 创建一个 map，键为 int，值为 string
    map<int, string> myMap;

    // 插入元素
    myMap[1] = "Apple";
    myMap[2] = "Banana";
    myMap.insert({3, "Cherry"});
    myMap.insert(make_pair(4, "Date"));

    // 访问元素
    cout << "Key 1: " << myMap[1] << endl;
    cout << "Key 2: " << myMap.at(2) << endl;

    // 查找元素
    int keyToFind = 3;
    auto it = myMap.find(keyToFind);
    if (it != myMap.end()) {
        cout << "Found key " << keyToFind << ": " << it->second << endl;
    } else {
        cout << "Key " << keyToFind << " not found." << endl;
    }

    // 遍历 map
    cout << "All elements:" << endl;
    for (const auto& pair : myMap) {
        cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
    }

    // 删除元素
    myMap.erase(2);
    cout << "After deleting key 2:" << endl;
    for (const auto& pair : myMap) {
        cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
    }

    // 检查是否为空
    if (!myMap.empty()) {
        cout << "Map is not empty. Size: " << myMap.size() << endl;
    }

    // 清空所有元素
    myMap.clear();
    cout << "After clearing, map is " << (myMap.empty() ? "empty." : "not empty.") << endl;

    return 0;
}
```

**输出**：

```yaml
Key 1: Apple
Key 2: Banana
Found key 3: Cherry
All elements:
Key: 1, Value: Apple
Key: 2, Value: Banana
Key: 3, Value: Cherry
Key: 4, Value: Date
After deleting key 2:
Key: 1, Value: Apple
Key: 3, Value: Cherry
Key: 4, Value: Date
Map is not empty. Size: 3
After clearing, map is empty.
```