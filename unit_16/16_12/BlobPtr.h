/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-02-24 00:46:49
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-02-24 02:10:00
 * @FilePath: /C++Primer/unit_16/16_12/BlobPtr.h
 * @Description:    一个针对Blob的指针或者迭代器的辅助类
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#ifndef __BLOBPTR_H__
#define __BLOBPTR_H__
#include <memory>
#include <stdexcept>
#include <vector>

#include "Blob.h"

template<typename T>
class BlobPtr; // 向前声明

template<typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template<typename T>
bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

template<typename T>
bool operator>(const BlobPtr<T> &lhs, const Blob<T> &rhs);

template<typename T>
class BlobPtr
{
    friend bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);
    friend bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);
    friend bool operator>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs);

public:
    BlobPtr() : curr(0) {}
    BlobPtr(Blob<T> &a, std::size_t sz = 0) : wptr(a.data), curr(sz) {}

    T &operator*() const
    {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];
    }

    // 前置运算符
    BlobPtr &operator++();
    BlobPtr &operator--();

    // 后置运算符
    BlobPtr &operator++(int);
    BlobPtr &operator--(int);

private:
    std::shared_ptr<std::vector<T>> check(std::size_t, const std::string &) const;

    std::weak_ptr<std::vector<T>> wptr; // 指向一个Blob
    std::size_t                   curr; // 当前指针指向第几个元素
};

// check
template<typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(std::size_t        sz,
                                                  const std::string &msg) const
{
    // 将wptr提升
    auto sp = wptr.lock();
    if (!sp)
        throw std::runtime_error("BlobPtr: " + msg + "- unbound BlobPtr");

    // 检查索引
    if (sz >= sp->size())
        throw std::out_of_range("BlorPtr: " + msg + "- index out of range");

    // 返回一个有效的
    return sp;
}

template<typename T>
BlobPtr<T> &BlobPtr<T>::operator++()
{
    check(curr, "increment past end of StrBlob");
    ++curr;
    return *this;
}

template<typename T>
BlobPtr<T> &BlobPtr<T>::operator--()
{
    --curr;
    check(curr, "decrement past begin of StrBlob");
    return *this;
}

template<typename T>
BlobPtr<T> &BlobPtr<T>::operator++(int)
{
    // 此处不需要检测，因为下面的前置++运算符会检测
    BlobPtr ret = *this;
    ++(*this);

    return ret;
}

template<typename T>
BlobPtr<T> &BlobPtr<T>::operator--(int)
{
    BlobPtr ret = *this;
    --(*this);

    return ret;
}

template<typename T>
bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    // 检测两个指针是否指向一个同一个地址
    if (lhs.wptr.lock() != rhs.wptr.lock()) {
        throw std::runtime_error("ptrs to different Blobs");
    }

    return lhs.curr == rhs.curr;
}

template<typename T>
bool operator<(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    if (lhs.wptr.lock() != rhs.wptr.lock()) {
        throw std::runtime_error("ptrs to different Blobs");
    }

    return lhs.curr < rhs.curr;
}

template<typename T>
bool operator>(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs)
{
    return !(lhs < rhs);
}

#endif
