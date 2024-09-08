#include <iostream>
#include <vector>
#include "../include/13.1text.hpp"

void text_1() {
    std::string s1("hello world");
    HasPtr p1 = HasPtr(s1);
    p1.showContent();
}

void f(const X &rx, X x) {  // 发生一次拷贝构造函数
    std::vector<X> vec;
    vec.reserve(2);
    vec.push_back(rx);  // 发生一次拷贝构造函数
    vec.push_back(x);  // 发生一次拷贝构造函数
    // 该函数结束之后,传入参数x被析构,容器中的两个元素被析构,一共析构三次
}

int main() {
    // text_1();
    // // 接下来的内容
    // std::cout << "Done!" << std::endl;
    X *px = new X;
    f(*px, *px);
    delete px;  // 这里再析构一次

    return 0;
}
