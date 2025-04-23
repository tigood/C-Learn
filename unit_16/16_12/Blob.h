/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-02-23 15:11:28
 * @LastEditors: tigood 3020422083@qq.com
 * 3020422083@qq.com
 * @LastEditTime: 2025-04-23 21:17:19
 * @FilePath: /C++Primer/unit_16/16_12/Blob.h
 * /C++Primer/unit_16/16_12/Blob.h
 * @Description:
 * 实现一个模板类型的Blob，可以接受任何类型当作内容
 *
 * Copyright (c) 2025 by tigood, All
 * Rights Reserved.
 */
#ifndef __BLOB_H__
#define __BLOB_H__
#include <iostream>
#include <memory>
#include <vector>

template<typename T>
class Blob
{
public:
    typedef T                                  value_type;
    typedef typename std::vector<T>::size_type size_type;

    // 构造函数
    Blob();
    Blob(std::initializer_list<T> il);

    // 模板构造函数
    template<typename It>
    Blob(It b, It e);

    // Blob中的元素数目
    size_type size() const { return data->size(); }
    bool      empty() const { return data->empty(); }

    void push_back(const T &t) { data->push_back(t); }
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();

    // 元素访问
    T &back();
    T &operator[](size_type i);

    const T &back() const;
    const T &operator[](size_type i) const;

private:
    std::shared_ptr<std::vector<T>> data;
    // 若data[i]无效，则抛出msg
    void check(size_type i, const std::string &msg) const;
};

template<typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>())
{}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il))
{}

template<typename T>
template<typename It>
Blob<T>::Blob(It b, It e) : data(std::make_shared<std::vector<T>>(b, e))
{}

template<typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    // 如果超出索引抛出一个错误
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template<typename T>
T &Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
const T &Blob<T>::back() const
{
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T &Blob<T>::operator[](size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
const T &Blob<T>::operator[](size_type i) const
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

#endif
