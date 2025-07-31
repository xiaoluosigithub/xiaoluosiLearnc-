//
// Created by lyx on 2025/7/31.
//
#include <iostream>
class Complex{
public:
    double real, imag;
    // 重载单目运算符
    Complex operator + (const Complex &c){
        Complex temp;
        temp.real = real + c.real;
        temp.imag = imag + c.imag;
        return temp;
    }
    // 重载双目运算符
    friend Complex operator - (const Complex &c1, const Complex &c2);

    // 友元重载
    friend std::ostream & operator << (std::ostream &out, const Complex &c);
};

Complex operator - (const Complex &c1, const Complex &c2){
    Complex temp;
    temp.real = c1.real - c2.real;
    temp.imag = c1.imag - c2.imag;
    return temp;
}

std::ostream & operator << (std::ostream &out, const Complex &c){
    out << "(" << c.real << "," << c.imag << "i)";
    return out;
}

int main(){
    Complex c1, c2;
    c1.real = 1.0;
    c1.imag = 2.0;

    c2.real = 3.0;
    c2.imag = 4.0;
    Complex result = c1 + c2;
    std::cout << result.real << " + " << result.imag << "i" << std::endl;

    Complex result2 = c1 - c2;
    std::cout << result2.real << " + " << result2.imag << "i" << std::endl;

    std::cout << result << std::endl;
    std::cout << result2 << std::endl;

    return 0;
}