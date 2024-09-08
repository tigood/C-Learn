#include <iostream>
#include <vector>
#include "../include/13.1text.hpp"

void text_1() {
    std::string s1("hello world");
    HasPtr p1 = HasPtr(s1);
    p1.showContent();
}

void f(const X &rx, X x) {
    std::vector<X> vec;
    vec.reserve(2);
    vec.push_back(rx);
    vec.push_back(x);
}

int main() {
    // text_1();
    // // 接下来的内容
    // std::cout << "Done!" << std::endl;
    X *px = new X;
    f(*px, *px);
    delete px;

    return 0;
}
