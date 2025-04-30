#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

#include "SharedPointer.h"

template<typename T>
class Blob
{
public:
    using size_type = typename std::vector<T>::size_type;
    using value_type = typename std::vector<T>::value_type;

    // 构造函数
    Blob();
    Blob(std::initializer_list<T> il);

    // 两个迭代器构造函数
    template<typename It>
    Blob(It b, It e);

    // 返回Blob的大小
    size_type size() const { return data_->size(); }
    // 判断Blob是否为空
    bool empty() const { return data_->empty(); }

    // 在末尾添加元素
    void push_back(const T &t) { data_->push_back(t); }
    void push_back(T &&t) { data_->push_back(std::move(t)); }

    // 删除末尾元素
    void pop_back();

    // 元素访问
    T &back();
    T &operator[](size_type i);
    // 常量元素访问
    const T &back() const;
    const T &operator[](size_type i) const;

private:
    SharedPointer<std::vector<T>> data_;

    // 辅助函数
    // 检测下标是否在合法范围内
    void check(size_type i, const std::string &msg) const;
};

// 辅助函数
template<typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data_->size()) {
        throw std::out_of_range(msg);
    }
}

template<typename T>
Blob<T>::Blob() : data_(std::make_shared<std::vector<T>>())
{}

// 构造函数
template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data_(std::make_shared<std::vector<T>>(il))
{}

// 两个迭代器构造函数
template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e) : data_(std::make_shared<std::vector<T>>(b, e))
{}

// 删除末尾元素
template<typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data_->pop_back();
}

// 元素访问
template<typename T>
T &Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data_->back();
}

template<typename T>
T &Blob<T>::operator[](size_type i)
{
    check(i, "subscript out of range");
    return (*data_)[i];
}

// 常量元素访问
template<typename T>
const T &Blob<T>::back() const
{
    check(0, "back on empty Blob");
    return data_->back();
}

template<typename T>
const T &Blob<T>::operator[](size_type i) const
{
    check(i, "subscript out of range");
    return (*data_)[i];
}