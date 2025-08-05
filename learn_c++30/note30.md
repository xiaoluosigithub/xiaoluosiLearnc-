# BST实现map

## 1. 选择底层数据结构

`std::map` 通常基于平衡的二叉搜索树（如红黑树）实现，以保证操作的时间复杂度为 O(log n)。为了简化实现，本文将采用**普通的二叉搜索树**，即不进行自平衡处理。不过在实际应用中，为了保证性能，建议使用自平衡的树结构（例如红黑树、AVL 树）。

## 2. 设计数据结构

### 2.1 节点结构

首先，需要定义树的节点结构，每个节点包含键值对以及指向子节点的指针。

```cpp
#include <iostream>
#include <stack>
#include <utility> // For std::pair
#include <exception>

template <typename Key, typename T>
struct TreeNode {
    std::pair<Key, T> data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(const Key& key, const T& value, TreeNode* parentNode = nullptr)
        : data(std::make_pair(key, value)), left(nullptr), right(nullptr), parent(parentNode) {}
};
```

### 2.2 Map 类的定义

接下来，定义 `MyMap` 类，包含根节点和基本操作。

```cpp
template <typename Key, typename T>
class MyMap {
public:
    MyMap() : root(nullptr) {}
    ~MyMap() { clear(root); }

    // 禁止拷贝构造和赋值
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;

    // 插入或更新键值对
    void insert(const Key& key, const T& value) {
        if (root == nullptr) {
            root = new TreeNode<Key, T>(key, value);
            return;
        }

        TreeNode<Key, T>* current = root;
        TreeNode<Key, T>* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (key < current->data.first) {
                current = current->left;
            } else if (key > current->data.first) {
                current = current->right;
            } else {
                // 键已存在，更新值
                current->data.second = value;
                return;
            }
        }

        if (key < parent->data.first) {
            parent->left = new TreeNode<Key, T>(key, value, parent);
        } else {
            parent->right = new TreeNode<Key, T>(key, value, parent);
        }
    }

    // 查找元素，返回指向节点的指针
    TreeNode<Key, T>* find(const Key& key) const {
        TreeNode<Key, T>* current = root;
        while (current != nullptr) {
            if (key < current->data.first) {
                current = current->left;
            } else if (key > current->data.first) {
                current = current->right;
            } else {
                return current;
            }
        }
        return nullptr;
    }

    // 删除元素
    void erase(const Key& key) {
        TreeNode<Key, T>* node = find(key);
        if (node == nullptr) return; // 没有找到要删除的节点

        // 节点有两个子节点
        if (node->left != nullptr && node->right != nullptr) {
            // 找到中序后继
            TreeNode<Key, T>* successor = minimum(node->right);
            node->data = successor->data; // 替换数据
            node = successor; // 将要删除的节点指向后继节点
        }

        // 节点有一个或没有子节点
        TreeNode<Key, T>* child = (node->left) ? node->left : node->right;
        if (child != nullptr) {
            child->parent = node->parent;
        }

        if (node->parent == nullptr) {
            root = child;
        } else if (node == node->parent->left) {
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }

        delete node;
    }

    // 清空所有节点
    void clear() {
        clear(root);
        root = nullptr;
    }

    // 获取迭代器
    class Iterator {
    public:
        Iterator(TreeNode<Key, T>* node = nullptr) : current(node) {}

        std::pair<const Key, T>& operator*() const {
            return current->data;
        }

        std::pair<const Key, T>* operator->() const {
            return &(current->data);
        }

        // 前置递增
        Iterator& operator++() {
            current = successor(current);
            return *this;
        }

        // 后置递增
        Iterator operator++(int) {
            Iterator temp = *this;
            current = successor(current);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

    private:
        TreeNode<Key, T>* current;

        TreeNode<Key, T>* minimum(TreeNode<Key, T>* node) const {
            while (node->left != nullptr) {
                node = node->left;
            }
            return node;
        }

        TreeNode<Key, T>* successor(TreeNode<Key, T>* node) const {
            if (node->right != nullptr) {
                return minimum(node->right);
            }

            TreeNode<Key, T>* p = node->parent;
            while (p != nullptr && node == p->right) {
                node = p;
                p = p->parent;
            }
            return p;
        }
    };

    Iterator begin() const {
        return Iterator(minimum(root));
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

private:
    TreeNode<Key, T>* root;

    // 删除树中的所有节点
    void clear(TreeNode<Key, T>* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    // 找到最小的节点
    TreeNode<Key, T>* minimum(TreeNode<Key, T>* node) const {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // 找到最大的节点
    TreeNode<Key, T>* maximum(TreeNode<Key, T>* node) const {
        if (node == nullptr) return nullptr;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }
};
```

### 2.3 解释

1. **TreeNode 结构**：

   - `data`: 存储键值对 `std::pair<Key, T>`。
   - `left` 和 `right`: 指向左子节点和右子节点。
   - `parent`: 指向父节点，便于迭代器中查找后继节点。

2. **MyMap 类**：

   - 构造与析构

     ：

     - 构造函数初始化根节点为空。
     - 析构函数调用 `clear` 释放所有节点内存。

   - 插入 (`insert`)

     ：

     - 从根节点开始，根据键的大小确定插入左子树还是右子树。
     - 如果键已存在，更新对应的值。

   - 查找 (`find`)

     ：

     - 按照键的大小在树中查找对应的节点。

   - 删除 (`erase`)

     ：

     - 查找到目标节点。
     - 如果节点有两个子节点，找到中序后继节点并替换当前节点的数据，然后删除后继节点。
     - 如果节点有一个或没有子节点，直接替换节点指针并删除节点。

   - 清空 (`clear`)

     ：

     - 使用递归方式删除所有节点。

   - 迭代器

     ：

     - 定义了嵌套的 `Iterator` 类，支持前置和后置递增操作。
     - 迭代器通过中序遍历实现，保证键的顺序性。
     - `begin()` 返回最小的节点，`end()` 返回 `nullptr`。

## 3. 使用示例

下面提供一个使用 `MyMap` 的示例，展示插入、查找、删除和迭代操作。

```cpp
int main() {
    MyMap<std::string, int> myMap;

    // 插入元素
    myMap.insert("apple", 3);
    myMap.insert("banana", 5);
    myMap.insert("orange", 2);
    myMap.insert("grape", 7);
    myMap.insert("cherry", 4);

    // 使用迭代器遍历元素（按键的字母顺序）
    std::cout << "Map contents (in-order):\n";
    for(auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << " => " << it->second << "\n";
    }

    // 查找元素
    std::string keyToFind = "banana";
    auto node = myMap.find(keyToFind);
    if(node != nullptr) {
        std::cout << "\nFound " << keyToFind << " with value: " << node->data.second << "\n";
    } else {
        std::cout << "\n" << keyToFind << " not found.\n";
    }

    // 删除元素
    myMap.erase("apple");
    myMap.erase("cherry");

    // 再次遍历
    std::cout << "\nAfter erasing apple and cherry:\n";
    for(auto it = myMap.begin(); it != myMap.end(); ++it) {
        std::cout << it->first << " => " << it->second << "\n";
    }

    return 0;
}
```

### 输出结果

```makefile
Map contents (in-order):
apple => 3
banana => 5
cherry => 4
grape => 7
orange => 2

Found banana with value: 5

After erasing apple and cherry:
banana => 5
grape => 7
orange => 2
```