//
// Created by lyx on 2025/8/5.
//

#ifndef LEARNC___DEQUE_H
#define LEARNC___DEQUE_H
#include <iostream>

template <typename T>
class Deque {
private:
    T * buffer;
    std::size_t capacity;
    std::size_t count;
    std::size_t front_idx;
    std::size_t back_idx;
public:
    Deque(size_t initial_capacity = 10) : capacity(initial_capacity), count(0), front_idx(0), back_idx(0){
        buffer = new T[capacity]();
    }
    ~Deque(){
        delete[] buffer;
    }
    bool empty() const {
        return count == 0;
    }
    [[nodiscard]] size_t size()const{
        return count;
    }
    void resize(size_t new_capacity){
        T * new_buffer = new T[new_capacity]();
        for(size_t i = 0; i < count; ++i){
            new_buffer[i] = buffer[(front_idx + i) % capacity];
        }
        front_idx = 0;
        back_idx = count;
        capacity = new_capacity;
        delete[] buffer;
        buffer = new_buffer;
    }
    void push_front(const T& value){
        if(count == capacity){
            resize(capacity * 2);
        }
        front_idx = front_idx == 0 ? capacity - 1 : front_idx - 1;
        buffer[front_idx] = value;
        ++count;
    }
    void push_back(const T& value){
        if(count == capacity){
            resize(capacity * 2);
        }
        buffer[back_idx] = value;
        back_idx = (back_idx + 1) % capacity;
        ++count;
    }
    void pop_front(){
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }
        (++front_idx) %= capacity;
        --count;
    }
    void pop_back(){
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }
        (--back_idx += capacity) %= capacity;
        --count;
    }
    T& back(){
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }
        size_t last_idx = back_idx == 0 ? capacity - 1 : back_idx - 1;
        return buffer[last_idx];
    }

    const T& back() const{
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }
        size_t last_idx = back_idx == 0 ? capacity - 1 : back_idx - 1;
        return buffer[last_idx];
    }
    T& front(){
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }
        return buffer[front_idx];
    }
    const T& front() const{
        if(empty()){
            throw std::out_of_range("Deque is empty");
        }
        return buffer[front_idx];
    }
    class Iterator{
    private:
        Deque<T> * deque_ptr;
        size_t pos; // 迭代器偏移量
    public:
        using iterator_category = std::bidirectional_iterator_tag; // 迭代器类型
        using value_type = T; // 迭代器所迭代的值的类型
        using difference_type = std::ptrdiff_t; // 迭代器所迭代的元素之间的距离
        using pointer = T*; // 迭代器所迭代元素的指针
        using reference = T&; // 迭代器所迭代元素的引用
        Iterator(Deque<T> * deque, size_t position) : deque_ptr(deque), pos(position){}
        reference operator * () const{
            size_t real_idx = (deque_ptr->front_idx + pos) % (deque_ptr->capacity);
            return deque_ptr->buffer[real_idx];
        }
        pointer operator -> () const{
            size_t real_idx = (deque_ptr->front_idx + pos) % (deque_ptr->capacity);
            return &(deque_ptr->buffer[real_idx]);
        }
        Iterator& operator ++ (){
            ++pos;
            return *this;
        }
        Iterator operator ++ (int){
            // 返回当前迭代器，再让当前迭代器++
            Iterator tmp = *this;
            ++pos;
            return tmp;
        }
        Iterator& operator -- (){
            --pos;
            return *this;
        }
        Iterator operator -- (int){
            Iterator tmp = *this;
            --pos;
            return tmp;
        }
        bool operator == (const Iterator & other) const{
            return (deque_ptr == other.deque_ptr) && (pos == other.pos);
        }
        bool operator != (const Iterator & other) const{
            return !(*this == other);
        }
    };

    Iterator begin(){
        return Iterator(this, 0);
    }
    Iterator end(){
        return Iterator(this, count);
    }
};


#endif //LEARNC___DEQUE_H
