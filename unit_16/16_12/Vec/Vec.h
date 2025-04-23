/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-02-24 13:26:09
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-02-24 15:58:28
 * @FilePath: /C++Primer/unit_16/16_12/Vec/Vec.h
 * @Description:    实现一个Vec模板类
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#ifndef __VEC_H__
#define __VEC_H__
#include <memory>

template<typename T>
class Vec
{
public:
    Vec() : element(nullptr), first_free(nullptr), cap(nullptr) {}
    Vec(std::initializer_list<T>);
    Vec(const Vec &v); // 拷贝构造函数

    Vec &operator=(const Vec &rhs); // 拷贝运算符重载

    ~Vec();

    // members
    void push_back(const T &t);

    std::size_t size() const { return first_free - element; }
    std::size_t capacity() const { return cap - element; }

    T *begin() const { return element; }
    T *end() const { return first_free; }

    // 如果 n 大于当前容量，则重新分配 n 个元素的空间，并移动原有数据
    void reserve(std::size_t n);
    // 若 n 小于 size()，则销毁多余元素.若 n 大于 size()，则扩展并填充新元素 t
    void resize(std::size_t n);
    void resize(std::size_t n, const T &t);

private:
    T *element;    // 指向数组的起始位置
    T *first_free; // 指向数组中第一个未使用的元素
    T *cap;        // 指向数组的容量上限

    std::allocator<T> alloc; // 内存分配器

    // 工具函数
    void reallocate();    // 扩容存储空间
    void check_n_alloc(); // 检查是否需要扩容空间
    void free();

    //为 指定大小 n 重新分配空间，并将原有数据移动过去。类似 reallocate()，但
    // reallocate() 默认扩容 2 倍，而 wy_alloc_n_move(n) 允许自定义容量大小。
    void wy_alloc_n_move(std::size_t n);

    // 为 [b, e) 这段范围的元素 分配新空间并复制数据，
    // 然后返回 {新空间起始地址, 末尾地址}。
    std::pair<T *, T *> alloc_n_copy(T *b, T *e);
};

template<typename T>
Vec<T>::Vec(std::initializer_list<T> l)
{
    T *newData = alloc.allocate(l.size());

    T *p = newData;
    for (const auto &t : l)
        alloc.construct(p++, t);

    element = newData;
    first_free = cap = element + l.size();
}

template<typename T>
Vec<T>::Vec(const Vec &v)
{
    std::pair<T *, T *> newData = alloc_n_copy(v.begin(), v.end());

    element = newData.first;
    first_free = cap = newData.second;
}

template<typename T>
Vec<T> &Vec<T>::operator=(const Vec &rhs)
{
    std::pair<T *, T *> newData = alloc_n_copy(rhs.begin(), rhs.end());

    // 释放当前对像原来的指向的空间，防止内存泄漏
    free();

    element = newData.first;
    first_free = cap = newData.second;

    return *this;
}

template<typename T>
Vec<T>::~Vec<T>()
{
    free();
}

template<typename T>
void Vec<T>::push_back(const T &t)
{
    // 检查空间是否够用
    check_n_alloc();
    alloc.construct(first_free++, t);
}

template<typename T>
void Vec<T>::reserve(std::size_t n)
{
    // 判断重新设置的长度是否比现在的大
    if (n <= capacity())
        return;

    wy_alloc_n_move(n);
}

template<typename T>
void Vec<T>::resize(std::size_t n)
{
    resize(n, Vec());
}

template<typename T>
void Vec<T>::resize(std::size_t n, const T &t)
{
    if (n < size()) {
        for (auto p = element + n; p != first_free;)
            alloc.destory(p++);

        first_free = element + n;
    }
    else if (n > size()) {
        for (auto i = size(); i != n; i++) {
            push_back(t);
        }
    }
}

template<typename T>
std::pair<T *, T *> Vec<T>::alloc_n_copy(T *b, T *e)
{
    T *data = alloc.allocate(e - b);
    return {data, std::uninitialized_copy(b, e, data)};
}

template<typename T>
void Vec<T>::free()
{
    if (element) {
        for (auto p = first_free; p != element;) {
            alloc.destory(--p);
        }

        alloc.deallocate(element, capacity());
    }
}

template<typename T>
void Vec<T>::wy_alloc_n_move(std::size_t n)
{
    std::size_t newCapacity = n;
    T          *newData = alloc.allocate(newCapacity);

    // 将原来的数据移动到新空间中
    T *dest = newData;
    T *old = element;
    for (std::size_t i = 0; i < size(); i++) {
        alloc.construct(dest++, std::move(*old++));
    }

    // 释放当前的函数的空间
    free();

    element = newData;
    first_free = dest;
    cap = element + newCapacity;
}

template<typename T>
void Vec<T>::reallocate()
{
    std::size_t newCapacity = size() ? 2 * size() : 1;

    wy_alloc_n_move(newCapacity);
}

#endif