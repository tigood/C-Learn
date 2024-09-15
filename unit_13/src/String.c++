#include "../include/String.hpp"
#include <iostream>
#include <algorithm>

std::allocator<char> String::alloc;
// 辅助函数的实现
std::pair<char *, char *>
String::alloc_n_copy(const char *b, const char *e) {
    // 开辟一个适当的空间，将数据拷贝到这个空间内
    auto str = alloc.allocate(e - b);
    return {str, std::uninitialized_copy(b, e, str)};
}

void String::range_initalizer(const char *first, const char *end) {
    auto newData = alloc_n_copy(first, end);
    // 更新我们的属性
    elements_ = newData.first;
    end_ = newData.second;
}
void String::free() {
    if(elements_) {
        std::for_each(elements_, end_, [this](char &c)
                      { this->alloc.destroy(&c); });
        alloc.deallocate(elements_, end_ - elements_);
    }
}
// String类的实现
String::String(const char *pch) {
    // 有参构造函数
    char *s1 = const_cast<char *>(pch);
    // 找到空字符\0
    while (*s1 != '\0') {
        ++s1;
    }
    range_initalizer(pch, ++s1);
}

String::String(const String &other) {
    // 拷贝构造函数
    range_initalizer(other.elements_, other.end_);
    std::cout << "拷贝构造函数执行了" << std::endl;
}

String &String::operator=(const String &other) {
    // 拷贝运算符重载
    // 开辟新空间，并且将需要拷贝的数据放进去
    auto newData = alloc_n_copy(other.elements_, other.end_);
    // 释放空间
    free();
    // 更新属性
    elements_ = newData.first;
    end_ = newData.second;
    std::cout << "拷贝符号重载执行了" << std::endl;
    return *this;
}

String::~String() {
    // 析构函数
    free();
}

// 移动构造函数
String::String(String &&s) noexcept : 
    elements_(s.elements_), end_(s.end_) {
    std::cout << "使用和移动构造函数" << std::endl;
    // 将源移动对象设置可析构状态
    s.elements_ = s.end_ = nullptr;
}

// 移动赋值运算符
String &String::operator=(String &&s) noexcept {
    // 检查是不是自拷贝
    if (this != &s) {
        // 首先释放自身
        free();
        elements_ = s.elements_;
        end_ = s.end_;
        // 将源对象设置为可析构状态
        s.elements_ = s.end_ = nullptr;
    }
    std::cout << "使用了移动赋值运算符" << std::endl;
    return *this;
}