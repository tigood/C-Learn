/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-24 14:18:19
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-28 09:21:28
 * @FilePath: /C++Primer/unit_16/16_1_6/UniquePointer.h
 * @Description: UniquePointer类的头文件
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#pragma once
#include <cstddef>

#include "DebugDelete.h"

template<typename, typename>
class UniquePointer;

template<typename T, typename D>
void swap(UniquePointer<T, D> &lhs, UniquePointer<T, D> &rhs);

template<typename T, typename D = DebugDelete>
class UniquePointer
{
    friend void swap<T, D>(UniquePointer<T, D> &lhs, UniquePointer<T, D>);

public:
    // 因为UniquePointer不支持拷贝和赋值，所以将拷贝构造函数和赋值运算符声明为删除的
    UniquePointer(const UniquePointer &) = delete;
    UniquePointer &operator=(const UniquePointer &) = delete;
    // 构造函数
    UniquePointer() = default;
    UniquePointer(T *up) : ptr_(up) {}

    // 移动构造函数
    UniquePointer(UniquePointer &&up) noexcept : ptr_(up.ptr_) { up.ptr_ = nullptr; }
    // 移动赋值运算符
    UniquePointer &operator=(UniquePointer &&up) noexcept;
    // 空指针做为参数
    UniquePointer &operator=(std::nullptr_t n) noexcept;

    // 运算符重载函数
    T &operator*() const { return *ptr_; }
    T *operator->() const { return &this->operator*(); }

    operator bool() const { return ptr_ ? true : false; }

    // 返回底层指针
    T *get() const { return ptr_; }

    // 使用友类函数swap交换两个UniquePointer对象
    void swap(UniquePointer &rhs) { ::swap(*this, rhs); }

    // 释放内容，并让他指向空指针或者指向新的内容
    void reset() noexcept
    {
        deleter_(ptr_);
        ptr_ = nullptr;
    }

    void reset(T *p) noexcept
    {
        deleter_(ptr_);
        ptr_ = p;
    }

    // 返回ptr_, 并将ptr_置空
    T *release();

    // 析构函数
    ~UniquePointer() { deleter_(ptr_); }

private:
    T *ptr_ = nullptr;
    D  deleter_ = D();
};

// 全局交换函数
template<typename T, typename D>
inline void swap(UniquePointer<T, D> lhs, UniquePointer<T, D> rhs)
{
    using std::swap;
    swap(lhs.ptr_, rhs.ptr_);
    swap(lhs.deleter_, rhs.deleter_);
}

// 移动赋值运算符
template<typename T, typename D>
UniquePointer<T, D> &UniquePointer<T, D>::operator=(UniquePointer &&up) noexcept
{
    if (this != &up) {
        deleter_(ptr_);
        ptr_ = nullptr;
        swap(*this, up);
    }

    return *this;
}

// 空指针赋值运算符
template<typename T, typename D>
UniquePointer<T, D> &UniquePointer<T, D>::operator=(std::nullptr_t n) noexcept
{
    if (n == nullptr) {
        deleter_(ptr_);
        ptr_ = nullptr;
    }
    return *this;
}

template<typename T, typename D>
inline T *UniquePointer<T, D>::release()
{
    T *ret = ptr_;
    ptr_ = nullptr;
    return ret;
}