#include "../include/strvec.hpp"
#include <iostream>
#include <string>
#include <memory>

std::allocator<std::string> StrVec::alloc;

// StrVec类实现
// 辅助函数的实现
std::pair<std::string *, std::string *> StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
    // 通过分配器分配一个动态内存
    auto data = alloc.allocate(e - b);
    // 将数据拷贝到新分配的内存中并返回一个pair对象
    return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    // 销毁对象并且释放空间
    // 不能传递给deallocate一个空指针
    if (elements_) {
        for (auto p = first_free_; p != elements_;)
        {
            // 因为p指向实际对象之后的第一个值，所以这里是--p，先移动再销毁对象
            alloc.destroy(--p);
        }
        // 对象全部销毁之后释放内存
        alloc.deallocate(elements_, cap_ - elements_);
    }
}

// void StrVec::reallocate() {
//     // 重新分配一个更大的内存，并将新的数据放进去
//     // 计算新的容量
//     auto newCapacity = size() ? size() * 2 : 1;
//     // 通过分配器开辟一个新的空间=
//     auto newData = alloc.allocate(newCapacity);
//     // 将数据从旧内存移动到新内存
//     auto dest = newData;  // 指向新内存的首地址
//     auto elem = elements_;  // 指向旧内存的首地址
//     for (size_t i = 0; i != size(); ++i) {
//         alloc.construct(dest++, std::move(*elem++));
//     }
//     // 释放空间
//     free();
//     // 更新我们的数据结构
//     elements_ = newData;
//     first_free_ = dest;
//     cap_ = newData + newCapacity;
// }

void StrVec::reallocate() {
    // 分配一个更大的内存，将数据存储进去，通过移动迭代器实现
    auto newCapcity = size() ? size() * 2 : 1;
    // 通过分配器开辟一块空间
    auto newData = alloc.allocate(newCapcity);
    // 将旧元素移动到新内存中去
    // 这是使用的是移动迭代器
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), newData);
    // 移动完毕了，释放旧内村
    free();
    // 更新数据
    elements_ = newData;
    first_free_ = last;
    cap_ = newData + newCapcity;
}

void StrVec::range_initialize(const std::string *b, const std::string *e) {
    auto newData = alloc_n_copy(b, e);
    // 更新配置
    elements_ = newData.first;
    first_free_ = cap_ = newData.second;
}

void StrVec::push_back(const std::string &s) {
    // 检查是否有空间
    chk_n_alloc();
    // 添加新元素
    alloc.construct(first_free_++, s);
}

// 默认拷贝构造函数
StrVec::StrVec(const StrVec &other) {
    range_initialize(other.elements_, other.first_free_);
}

StrVec::StrVec(std::initializer_list<std::string> il) {
    range_initialize(il.begin(), il.end());
}

// 重载拷贝符号
StrVec &StrVec::operator=(const StrVec &other) {
    // 开辟新空间
    auto newData = alloc_n_copy(other.begin(), other.end());
    // 开辟新空间之后，再释放内存
    free();
    // 更改我们的数据结构
    elements_ = newData.first;
    first_free_ = cap_ = newData.second;
    return *this;
}

// 析构函数
StrVec::~StrVec() {
    free();
}

// 移动构造函数的实现
// 移动函数是不会抛出异常的，所以在这里使用noexcept声明来做到一个优化的效果
StrVec::StrVec(StrVec &&s) noexcept:
    elements_(s.elements_), first_free_(s.first_free_), cap_(s.cap_) {
    // 让s处于一个这样的状态--对它执行析构函数是安全的
    s.elements_ = s.first_free_ = s.cap_ = nullptr;
}

// 移动赋值运算的实现
StrVec &StrVec::operator=(StrVec &&s) noexcept {
    // 判断是不是自赋值
    if (this != &s) {
        // 释放原空间
        free();
        // 重新赋值新结构
        elements_ = s.elements_;
        first_free_ = s.first_free_;
        cap_ = s.cap_;
        // 将源对象设置为可析构状态
        s.elements_ = s.first_free_ = s.cap_ = nullptr;
    }
    return *this;
}
