/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-29 23:49:57
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-30 12:08:57
 * @FilePath: /C++Primer/unit_16/16_5/16_62/Sales_data.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include "Sales_data.h"

Sales_data::Sales_data(std::istream &is) { is >> *this; }

double Sales_data::avg_price() const
{
    if (unitsSold_) {
        return revenue_ / unitsSold_;
    }
    else {
        return 0;
    }
}

Sales_data &Sales_data::operator+=(const Sales_data &rhs)
{
    unitsSold_ += rhs.unitsSold_;
    revenue_ += rhs.revenue_;
    return *this;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

std::istream &operator>>(std::istream &is, Sales_data &item)
{
    double price; // no need to initialize; we'll read into price before we use it
    is >> item.bookNo_ >> item.unitsSold_ >> price;
    if (is) // check that the inputs succeeded
        item.revenue_ = item.unitsSold_ * price;
    else
        item = Sales_data(); // input failed: give the object the default state
    return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.unitsSold_ << " " << item.revenue_ << " "
       << item.avg_price();
    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.unitsSold_ << " " << item.revenue_ << " "
       << item.avg_price();
    return os;
}

std::istream &read(std::istream &is, Sales_data &item)
{
    double price;
    is >> item.bookNo_ >> item.unitsSold_ >> price;
    item.revenue_ = item.unitsSold_ * price;
    return is;
}
