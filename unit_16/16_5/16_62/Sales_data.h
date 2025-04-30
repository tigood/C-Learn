/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-29 23:49:51
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-30 12:08:58
 * @FilePath: /C++Primer/unit_16/16_5/16_62/Sales_data.h
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#pragma once
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>

class Sales_data
{
    friend bool          operator==(const Sales_data &lhs, const Sales_data &rhs);
    friend std::istream &operator>>(std::istream &is, Sales_data &item);
    friend std::ostream &operator<<(std::ostream &os, const Sales_data &item);
    friend Sales_data    add(const Sales_data &, const Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);
    friend std::istream &read(std::istream &is, Sales_data &item);
    friend std::hash<Sales_data>;

public:
    Sales_data() = default;
    Sales_data(const std::string &s) : bookNo_(s) {}
    Sales_data(const std::string &s, unsigned units_sold, double revenue)
        : bookNo_(s), unitsSold_(units_sold), revenue_(revenue)
    {}
    Sales_data(std::istream &is);

    std::string isbn() const { return bookNo_; }

    Sales_data &operator+=(const Sales_data &rhs);

private:
    double avg_price() const;

    std::string bookNo_;
    unsigned    unitsSold_ = 0; // 销售量
    double      revenue_ = 0.0; // 收入
};

inline bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

inline bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn() && lhs.unitsSold_ == rhs.unitsSold_ &&
           lhs.revenue_ == rhs.revenue_;
}

inline bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
{
    return !(lhs == rhs);
}

// 旧版本
Sales_data    add(const Sales_data &lhs, const Sales_data &rhs);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);

// 新版本重载符
Sales_data    operator+(const Sales_data &lhs, const Sales_data &rhs);
std::ostream &operator<<(std::ostream &, const Sales_data &);
std::istream &operator>>(std::istream &, Sales_data &);

// hash模板特例化
namespace std
{
    template<>
    struct hash<Sales_data>
    {
        using result_type = size_t;
        using argument_type = Sales_data;
        result_type operator()(const argument_type &s) const
        {
            return hash<string>()(s.isbn()) ^ hash<unsigned>()(s.unitsSold_) ^
                   hash<double>()(s.revenue_);
        }
    };
} // namespace std
