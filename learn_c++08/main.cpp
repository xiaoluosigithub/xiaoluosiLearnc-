//
// Created by lyx on 2025/7/30.
//
#include <iostream>

typedef double wages;
typedef wages base, *p;
using int64_t = long long;


int main(){
    wages wage = 10.5;
    base wage2 = wage;
    p wage_ptr = &wage;

    int64_t a = 10;

    int age1 = 10;
    int age2 = 10;
    auto age_add = age1 + age2;

    auto i = 0, *p = &i;
    {
        int i = 0, &r = i;
        auto a = r;
        r++;
        std::cout << i << " " << r << std::endl;
    }

    {
        int i = 0, &r = i;
        auto a = r;

        const int ci = i, &cr = ci;
        auto b = ci;
        auto c = cr;
        auto d = &i;
        auto e = &ci;
        const auto f = ci;
        auto &g = ci;
    }

    {
        const int ci = 0, &cj = ci;
        decltype(ci) x = 0;
        decltype(cj) y = x;

        int i = 42, *p = &i, &r = i;
        decltype(r + 0) b;
        decltype(*p) c = i;
        decltype((i)) f= i;
    }

    return 0;
}