//
// Created by lyx on 2025/8/4.
//

#ifndef LEARNC___LIST_H
#define LEARNC___LIST_H
#include <iostream>

template <typename T>
struct Node{
    T data;
    Node * prev;
    Node * next;
    Node(const T & value = T()) : data(value), prev(nullptr), next(nullptr){}
};

template <typename T>
class List;

template <typename T>
class Iterator{
public:
    using self_type = Iterator<T>;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;

    Iterator(Node<T> * ptr = nullptr) : node_ptr(ptr){}
    reference operator* ()const{return node_ptr->data;}
    pointer operator-> () const{return &(node_ptr->data); /* 先去data 再取data的地址进行返回 */ }
    self_type & operator++(){
        if(node_ptr){
            node_ptr = node_ptr->next;
        }
        return *this;
    }
    self_type operator++(int){
        self_type temp = *this;
        ++(*this);
        return temp;
    }
    self_type & operator--(){
        if(node_ptr){
            node_ptr = node_ptr->prev;
        }
        return *this;
    }
    self_type operator--(int){
        self_type temp = *this;
        --(*this);
        return temp;
    }
    bool operator==(const self_type & other) const {
        return node_ptr == other.node_ptr;
    }
    bool operator != (const self_type & other) const{
        return node_ptr != other.node_ptr;
    }

private:
    Node<T> * node_ptr;
    friend class List<T>;
};

template <typename T>
class List{
public:
    using iterator = Iterator<T>;
    using const_iterator = Iterator<T>;
    List(){
        head = new Node<T>();
        tail = new Node<T>();
        head->next = tail;
        tail->prev = head;
    }
    ~List(){
        clear();
        delete head;
        delete tail;
    }
    List(const List & other) = delete;
    List & operator=(const List & other) = delete;

    iterator insert(iterator pos, const T & value){
        Node<T> * node = pos.node_ptr;
        Node<T> * new_node = new Node<T>(value);
        new_node->next = pos.node_ptr;
        new_node->prev = pos.node_ptr->prev;
        pos.node_ptr->prev->next = new_node;
        pos.node_ptr->prev = new_node;
        return iterator(new_node);
    }
    iterator erase(iterator pos){
        if(pos.node_ptr == head || pos.node_ptr == tail){
            return iterator(tail);
        }
        iterator ret(pos.node_ptr->next);
        pos.node_ptr->prev->next = pos.node_ptr->next;
        pos.node_ptr->next->prev = pos.node_ptr->prev;
        delete pos.node_ptr;
        return iterator(ret);
    }
    void push_front(const T & value){
        insert(begin(), value);
    }
    void push_back(const T & value){
        insert(end(), value);
    }

    void pop_front(){
        if(!empty()){
            erase(begin());
        }
    }
    void pop_back(){
        if(!empty()){
            iterator temp = end();
            --temp;
            erase(temp);
        }
    }

    T & front(){
        return head->next->data;
    }

    T & back(){
        return tail->prev->data;
    }

    bool empty() const{
        return head->next == tail;
    }

    size_t size()const{
        size_t count = 0;
        for(auto it = begin(); it != end(); ++it){
            count++;
        }
        return count;
    }

    void remove(const T& value){
        for(auto it = begin(); it != end();){
            if(*it == value){
                it = erase(it);
            }else{
                ++it;
            }
        }
    }

    void print() const{
        Node<T> * current = head->next;
        while(current != tail){
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    iterator begin(){
        return iterator(head->next);
    }
    iterator end(){
        return iterator(tail);
    }

    void clear(){
        Node<T> * cur = head->next;
        while(cur != tail){
            Node<T> * next = cur->next;
            delete cur;
            cur = next;
        }
        head->next = tail;
        tail->prev = head;
    }

private:
    Node<T> * head;
    Node<T> * tail;
};


#endif //LEARNC___LIST_H
