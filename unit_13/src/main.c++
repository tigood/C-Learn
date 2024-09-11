#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/13.1text.hpp"
#include "../include/13.5text.hpp"

void text_1() {
    using std::swap;
    HasPtr hp1{"hello world"};
    HasPtr hp2{"tigood"};
    hp1.showContent();
    hp2.showContent();
    // 即使上面使用using std::swap，但还是不会影响下面的swap使用的是我们自己的swap
    swap(hp1, hp2);
    hp1.showContent();
    hp2.showContent();
}

void text_2() {
    std::vector<HasPtr> myVector;
    myVector.reserve(4);
    myVector.emplace_back("hello world");
    myVector.emplace_back("tigood");
    myVector.emplace_back("nihao");
    myVector.emplace_back("orange");
    std::cout << "排序前：" << std::endl;
    for (auto &item : myVector) {
        item.showContent();
    }
    // 排序
    std::sort(myVector.begin(), myVector.end());
    std::cout << "排序后：" << std::endl;
    for (auto &item : myVector) {
        item.showContent();
    }
}

void text_3() {
    // 测试Message类和Folder类
    Message m1{"hello world"};
    Message m2{"tigood"};
    Folder f1{};
    m1.save(f1);
    f1.print_debug();
    std::cout << "再次添加消息之后：" << std::endl;
    m2.save(f1);
    f1.print_debug();
}

int main() {
    // text_1();
    // text_2();
    text_3();

    return 0;
}