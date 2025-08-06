//
// Created by lyx on 2025/8/5.
//

#ifndef LEARNC___MYMAP_H
#define LEARNC___MYMAP_H
#include <iostream>
#include <utility>
#include <exception>
#include <stack>


template <typename Key, typename T>
struct TreeNode{
    std::pair<Key, T> data;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
    TreeNode(const Key & key, const T& value, TreeNode * parentNode = nullptr):
    data(std::make_pair(key, value)), left(nullptr), right(nullptr), parent(parentNode){}
};

template <typename Key, typename T>
class MyMap {
public:
    MyMap() : root(nullptr){}
    ~MyMap(){
        clear();
    }
    void clear(){
        clear(root);
        root = nullptr;
    }
    MyMap(const MyMap& other) = delete; // 删去拷贝构造
    MyMap& operator = (const MyMap & other) = delete; // 删去拷贝赋值
    void insert(const Key& key, const T& value){
        if(root == nullptr){
            root = new TreeNode<Key, T>(key, value);
            return;
        }
        TreeNode<Key, T> * current = root;
        TreeNode<Key, T> * parent = nullptr;

        while(current != nullptr) {
            parent = current;
            if(key < current->data.first){
                current = current->left;
            } else if (key > current->data.first){
                current = current->right;
            } else {
                current->data.second = value;
                return;
            }
        }
        if(key < parent->data.first){
            parent->left = new TreeNode<Key, T>(key, value, parent);
        } else {
            parent->right = new TreeNode<Key, T>(key, value, parent);
        }
    }
    // 删除节点
    void erase(const Key& key){
        auto * node = find(key);
        if(node == nullptr) return;

        // 左右子树都不为空
        if(node->left != nullptr && node->right != nullptr){
            // 寻找后继节点
            auto * successor = minimum(node->right);
            // 替换当前节点值为后记节点
            node->data = successor->data;
            // 更新节点为后继节点
            node = successor;
        }
        auto * child = (node->left) ? node->left : node->right;
        if(child != nullptr) {
            child->parent = node->parent;
        }
        if(node->parent == nullptr){
            root = child;
        } else if (node == node->parent->left){
            node->parent->left = child;
        } else {
            node->parent->right = child;
        }
        delete node;
    }
    TreeNode<Key, T> * find(const Key & key) const{
        auto * current = root;
        while(current != nullptr){
            if(key < current->data.first){
                current = current->left;
            } else if (key > current->data.first){
                current = current->right;
            } else {
                return current;
            }
        }
        return nullptr;
    }

    class Iterator{
    public:
        Iterator(TreeNode<Key, T> * node) : current(node){}
        std::pair<const Key, const T> & operator * () const {return current->data;}
        std::pair<Key,T> * operator -> () const{return &current->data;}
        bool operator == (const Iterator& other) const {return current == other.current;}
        bool operator != (const Iterator& other) const {return !(*this == other);}
        Iterator& operator++(){
            if(current != nullptr){
                current = successor(current);
            }
            return * this;
        }
        Iterator operator++(int){
            Iterator tmp = *this;
            ++*this;
            return tmp;
        }
    private:
        TreeNode<Key, T> * current;
        // 遍历node节点为根的树(含node节点)，找到最小的节点
        TreeNode<Key, T> * minimum(TreeNode<Key, T> * node) const{
            while(node->left != nullptr){
                node = node->left;
            }
            return node;
        }
        TreeNode<Key, T> * maximum(TreeNode<Key, T> * node) const{
            while(node->right != nullptr){
                node = node->right;
            }
            return node;
        }
        // 获取node节点的直接后继节点
        TreeNode<Key, T> * successor(TreeNode<Key, T> * node) const{
            if(node->right != nullptr){
                return minimum(node->right);
            }
            auto * p = node->parent;
            while(p != nullptr && node == p->right){
                node = p;
                p = p->parent;
            }
            return p;
        }
    };
    Iterator begin() const{
        return Iterator(minimum(root));
    }
    Iterator end() const{
        return Iterator(nullptr);
    }
private:
    TreeNode<Key, T> * root;
    void clear(TreeNode<Key, T> * node) {
        if(node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    // 遍历node节点为根的树(含node节点)，找到最小的节点
    TreeNode<Key, T> * minimum(TreeNode<Key, T> * node) const{
        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }
    TreeNode<Key, T> * maximum(TreeNode<Key, T> * node) const{
        while(node->right != nullptr){
            node = node->right;
        }
        return node;
    }
    TreeNode<Key, T> * successor(TreeNode<Key, T> * node) const{
        if(node->right != nullptr){
            return minimum(node->right);
        }
        auto * p = node->parent;
        while(p != nullptr && node == p->right){
            node = p;
            p = p->parent;
        }
        return p;
    }
};
#endif //LEARNC___MYMAP_H
