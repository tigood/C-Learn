#include "../include/String.hpp"
#include <iostream>
#include <algorithm>
#include <string.h>

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

String &String::operator+=(const String &rhs) {
    // 计算长度
    size_t lhs_length = this->end_ - this->elements_;
    size_t rhs_lenght = rhs.end_ - rhs.elements_;
    size_t new_lenght = lhs_length + rhs_lenght;

    // 开辟空间
    char *new_elements = alloc.allocate(new_lenght + 1);
    // 拷贝内容
    memcpy(new_elements, this->elements_, lhs_length);
    memcpy(new_elements + lhs_length, rhs.elements_, rhs_lenght);

    // 添加结束字符
    new_elements[new_lenght + 1] = '\0';

    // 释放源内存
    free();

    // 重新修改指向
    this->elements_ = new_elements;
    this->end_ = new_elements + new_lenght;

    return *this;
}

std::ostream &operator<<(std::ostream &os, const String &str) {
    if (str.elements_) {  // 检查指针是否有效
        os.write(str.elements_, str.end_ - str.elements_); // 输出字符串
    }
    return os;
}

std::istream &operator>>(std::istream &is, String &str) {
    char buffer[1024]; // 临时缓冲区
    is >> buffer; // 读取输入到缓冲区

    // 这里可以添加逻辑来处理读取的字符串，例如分配内存和复制内容
    str.free(); // 释放旧内存（如果有的话）
    str.range_initalizer(buffer, buffer + strlen(buffer)); // 初始化新内容
    return is;
}

bool operator==(const String &str1, const String &str2) {
    // 比较长度
    if (str1.end_ - str1.elements_ != str2.end_ - str2.elements_)
        return false;
    // 再比较内容
    return (strncmp(str1.elements_, str2.elements_, str1.end_ - str1.elements_) == 0);
}

bool operator!=(const String &str1, const String &str2) {
    return !(str1 == str2);
}

bool operator<(const String &str1, const String &str2) {
    // 首先判断长度
    size_t str1_length = str1.end_ - str1.elements_;
    size_t str2_length = str2.end_ - str2.elements_;
    if (str1_length != str2_length) {
        return str1_length < str2_length;
    }

    // 再检测内存
    return strncmp(str1.elements_, str2.elements_, str1_length) < 0;
}

bool operator>(const String &str1, const String &str2) {
    return !(str1 == str2 || str1 < str2);
}