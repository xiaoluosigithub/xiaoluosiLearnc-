//
// Created by lyx on 2025/8/6.
//

#ifndef LEARNC___COMPLEX_H
#define LEARNC___COMPLEX_H
#include <iostream>

class Complex {
private:
    double real;
    double imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    Complex operator + (const Complex & cmp) const{
        return Complex(real + cmp.real, imag + cmp.imag);
    }
    friend std::ostream & operator << (std::ostream & os, const Complex &cmp){
        os << "(" << cmp.real;
        if(cmp.imag >= 0){
            os << "+" << cmp.imag << "i)";
        } else {
            os << "-" << -cmp.imag << "i)";
        }
        return os;
    }
    Complex operator - (const Complex & cmp) const{
        return Complex(this->real - cmp.real, this->imag - cmp.imag);
    }
    Complex operator * (const Complex & cmp) const{
        return Complex(this->real * cmp.real - this->imag * cmp.imag, this->real * cmp.imag + this->imag * cmp.real);
    }
    Complex & operator=(const Complex & cmp){
        if(this != &cmp){
            return *this;
        }
        this->real = cmp.real;
        this->imag = cmp.imag;
        return *this;
    }

    bool operator == (const Complex & cmp) const{
        return this->real == cmp.real && this->imag == cmp.imag;
    }

    bool operator != (const Complex & cmp) const {
        return this->real != cmp.real || this->imag != cmp.imag;
    }

};


#endif //LEARNC___COMPLEX_H
