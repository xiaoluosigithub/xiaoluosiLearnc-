//
// Created by lyx on 2025/8/7.
//

#ifndef LEARNC___SFINAE_H
#define LEARNC___SFINAE_H
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_type(T value){
    std::cout << "Integral type: " << value << std::endl;
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
print_type(T value){
    std::cout << "Floating point type: " << value << std::endl;
}

template<typename T>
typename std::enable_if<std::is_same<T, const char*>::value ||
    std::is_same<T, char *>::value>::type print_type(T value){
        std::cout << "C-style string type:" << value << std::endl;
    }

template<typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print_type(T value){
    std::cout << "std::string type : " << value << std::endl;
}

template<typename T>
typename std::enable_if<std::is_pointer<T>::value && !std::is_same<T, const char *>::value
    && !std::is_same<T, char *>::value, void>::type
print_type(T value){
    std::cout << "Pointer type " << std::endl;
}

template <typename T>
typename std::enable_if<
        !std::is_integral<T>::value &&
        !std::is_floating_point<T>::value &&
        !std::is_same<T, std::string>::value &&
        !std::is_same<T, const char *>::value &&
        !std::is_same<T, char *>::value &&
        !(std::is_pointer<T>::value && !std::is_same<T, const char *>::value
            && !std::is_same<T, char *>::value) , void
        >::type print_type(T value){
            std::cout << "Unknown type " << value << std::endl;
}

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<typename T>
concept String = std::is_same_v<T, const char *> || std::is_same_v<T, char *>;

template<typename T>
concept StdString = std::is_same_v<T, std::string>;

template<typename T>
concept PointerType = std::is_pointer_v<T> && !std::is_same_v<T, char *> && !std::is_same_v<T, const char *>;

void cout_type(Integral auto value){
    std::cout << "Integral type: " << value << std::endl;
}

void cout_type(FloatingPoint auto value){
    std::cout << "Floating point type: " << value << std::endl;
}

void cout_type(String auto value){
    std::cout << "C-style string type:" << value << std::endl;
}

void cout_type(StdString auto value){
    std::cout << "std::string type : " << value << std::endl;
}

void cout_type(PointerType auto value){
    std::cout << "Pointer type " << std::endl;
}

template<typename T>
requires (!Integral<T> && !FloatingPoint<T> && !String<T> && !StdString<T> && !PointerType<T>)
void cout_type(T value){
    std::cout << "Unknown type " << value << std::endl;
}


template<typename T>
class has_foo{
private:
    typedef char yes[1];
    typedef char no[2];
    template<typename U, void(U::*)()>
    struct SFINAE{};

    template<typename U>
    static yes & test(SFINAE<U, &U::foo>*);

    template<typename U>
    static no & test(...);

public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
};


template<typename T>
typename std::enable_if<has_foo<T>::value, void>::type
call_foo(T & obj){
    obj.foo();
    std::cout << "foo() called" << std::endl;
}

class WithFoo{
public:
        void foo(){std::cout << "WithFoo::foo() called" << std::endl;}
};

class WithoutFoo{};



template<typename T, typename = void>
struct has_non_void_value_type : std::false_type{};

template <typename T>
struct has_non_void_value_type<T, std::enable_if_t<!std::is_void_v<typename T::value_type>>> : std::true_type{};

template<typename T, bool HasValueType = has_non_void_value_type<T>::value>
struct TypePrinter;

template<typename T>
struct TypePrinter<T, true>{
    static void print(){
        std::cout <<"T has a member type called value_type" << std::endl;
    }
};

template<typename T>
struct TypePrinter<T, false>{
    static void print(){
        std::cout << "T does not have a member type called value_type" << std::endl;
    }
};

struct WithValueType{
    using value_type = int;
};
struct WithoutValueType{};


#endif //LEARNC___SFINAE_H
