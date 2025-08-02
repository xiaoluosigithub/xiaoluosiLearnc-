//
// Created by lyx on 2025/8/2.
//

#ifndef LEARNC___SIMPLESHAREDPTR_H
#define LEARNC___SIMPLESHAREDPTR_H

struct ControlBlock{
    int ref_count;
    ControlBlock() :ref_count(1){}
};


template <typename T>
class SimpleSharedPtr {
private:
    T *ptr;
    ControlBlock * control;
    void release(){
        if(control){
            --control->ref_count;
            if(control->ref_count == 0){
                delete ptr;
                ptr = nullptr;
                delete control;
                control = nullptr;
            }
        }
    }
public:
    SimpleSharedPtr():ptr(nullptr),control(nullptr){}
    explicit SimpleSharedPtr(T *p) : ptr(p){
        if(p){
            control = new ControlBlock();
        }else{
            control = nullptr;
        }
    }
    ~SimpleSharedPtr(){
        if(ptr){
            release();
        }
    }

    // 拷贝构造 s2(s1)
    SimpleSharedPtr(const SimpleSharedPtr & s) : ptr(s.ptr), control(s.control){
        if(control){
            ++ control->ref_count;
        }
    }

    // 拷贝赋值 s2(new student()); s2 = s1;
    SimpleSharedPtr & operator = (const SimpleSharedPtr &s){
        if(this != &s){
            release();
            ptr = s.ptr;
            control = s.control;
            if(control){
                ++ control->ref_count;
            }
        }
        return * this;
    }

    // 移动构造 SimpleSharedPtr s2(std::move(s1))
    SimpleSharedPtr(SimpleSharedPtr && other) noexcept : ptr(other.ptr), control(other.control){
        other.ptr = nullptr;
        other.control = nullptr;
    }

    // 移动赋值 SimpleSharePtr s2; s2 = std::move(s1);
    SimpleSharedPtr & operator = (SimpleSharedPtr && other) noexcept{
        if(this != &other){
            release();
            ptr = other.ptr;
            control = other.control;
            other.ptr = nullptr;
            other.control = nullptr;
        }
        return *this;
    }

    // 重载运算符 SimpleSharePtr s2(new student()); s2 -> name = "tom"; s2.ptr -> name = "tom";
    T * operator -> () const {
        return ptr;
    }

    // simpleSharePtr s2(new student()); (*s2).name = "tom"; (*s2.ptr).name = "tom";
    T & operator * () const {
        return *ptr;
    }

    // Student * raw_s2 = s2.get();
    T * get() const{
        return ptr;
    }

    //
    int use_count() const{
        return control ? control->ref_count : 0;
    };

    // s2.reset(new Student());
    // s2.reset();
    void reset(T *p = nullptr){
        release();
        ptr = p;
        if(p){
            control = new ControlBlock();
        } else {
            control = nullptr;
        }
    }

};


#endif //LEARNC___SIMPLESHAREDPTR_H
