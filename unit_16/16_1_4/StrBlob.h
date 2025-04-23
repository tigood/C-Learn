/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-22 22:23:45
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-22 23:53:55
 * @FilePath: /C++Primer/unit_16/16_1_4/StrBlob.h
 * @Description: StrBlob.h
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#ifndef StrBlob_H
#define StrBlob_H
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

// 前向声明 指针类，用来管理StrBlob中的元素
class StrBlobPtr;

class StrBlob
{
    friend class StrBlobPtr;

public:
    typedef std::vector<std::string>::size_type size_type;

    // 构造函数
    StrBlob() : data_(std::make_shared<std::vector<std::string>>()) {}
    StrBlob(std::initializer_list<std::string> il);

    // 返回Bolb中的元素格式
    size_type size() const { return data_->size(); }
    bool      empty() const { return data_->empty(); }

    // 添加或者删除元素
    void push_back(const std::string &t) { data_->push_back(t); }
    void pop_back();

    // 返回迭代器
    std::string &front() const;
    std::string &back() const;

    // 返回迭代器
    StrBlobPtr begin();
    StrBlobPtr end();

private:
    void check(size_type i, const std::string &msg) const;

    std::shared_ptr<std::vector<std::string>> data_;
};

class StrBlobPtr
{
    friend bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

public:
    StrBlobPtr() : curr_(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr_(a.data_), curr_(sz) {}
    StrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr_(a.data_), curr_(sz) {}

    // 解引用，返回当前指针指向字符串的值
    std::string &deref() const;
    // 自增
    StrBlobPtr &incr();
    // 自减
    StrBlobPtr &decr();

private:
    // 如果检测存在，就返回一个可用的shared_ptr指针
    std::shared_ptr<std::vector<std::string>> check(std::size_t,
                                                    const std::string &) const;

    std::weak_ptr<std::vector<std::string>> wptr_;
    std::size_t                             curr_;
};
#endif