#include "../include/String.hpp"
#include <vector>
#include <iostream>

void text_1() {
    std::vector<String> svect;
    svect.reserve(3);
    // 当使用push_back添加一个常量字符串的时候会优先使用移动构造函数
    svect.push_back("hello");
    svect.push_back("world");
    svect.push_back("tigood");
    std::vector<String> v1{"hello", "tigood"};
    std::vector<String> v2;
    // 而在两个对象之间的拷贝的时候会使用拷贝构造函数
    v2 = v1;
    std::cout << "Done" << std::endl;
}

int main() {
    text_1();

    return 0;
}