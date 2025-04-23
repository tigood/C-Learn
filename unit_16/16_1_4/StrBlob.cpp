/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-22 22:47:12
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-22 23:55:17
 * @FilePath: /C++Primer/unit_16/16_1_4/StrBlob.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include "./StrBlob.h"

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <vector>

inline StrBlob::StrBlob(std::initializer_list<std::string> il)
    : data_(std::make_shared<std::vector<std::string>>(il))
{}

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data_->size()) {
        throw std::out_of_range(msg);
    }
    return;
}

void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");

    data_->pop_back();
}

std::string &StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data_->front();
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(size_t             i,
                                                            const std::string &msg) const
{
    auto ret = wptr_.lock();
    if (!ret) {
        throw std::runtime_error("unbound StrBlobPtr");
    }
    if (i >= ret->size()) {
        throw std::out_of_range(msg);
    }
    // 返回一个shared_ptr
    return ret;
}

std::string &StrBlobPtr::deref() const
{
    // p保存的是一个lock来的shared_ptr，所以对共享内存的引用+1
    auto p = check(curr_, "dereference past end");
    // 返回的时候返回的是一个字符串引用
    // 然后p离开作用域，自动析构，对共享内存的引用-1
    return (*p)[curr_];
}

StrBlobPtr &StrBlobPtr::incr()
{
    check(curr_, "increment past end of StrBlobPtr");
    ++curr_;
    return *this;
}

StrBlobPtr &StrBlobPtr::decr()
{
    --curr_;
    check(curr_, "decrement past begin of StrBlobPtr");
    return *this;
}

bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs)
{
    auto l = lhs.wptr_.lock(), r = rhs.wptr_.lock();
    if (l == r) {
        return (!r || lhs.curr_ == rhs.curr_);
    }
    else {
        return false;
    }
}

bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) { return !eq(lhs, rhs); }

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data_->size()); }
