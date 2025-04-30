/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-28 13:03:43
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-28 15:49:54
 * @FilePath: /C++Primer/unit_16/16_2_7/main.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <iostream>
#include <memory>
#include <utility>

void func_lvalue(std::string &lhs, std::string &rhs)
{
    lhs = "time";
    rhs = "good";
}

void func_rvalue(int &&lhs, int &&rhs)
{
    std::allocator<int> alloc;
    int                *data(alloc.allocate(3));

    alloc.construct(data, lhs);
    alloc.construct(data + 1, 0);
    alloc.construct(data + 2, rhs);

    for (auto p = data; p != data + 3; ++p) {
        std::cout << *p << " ";
    }

    std::cout << std::endl;

    // 释放
    for (auto p = data + 3; p != data;) {
        alloc.destroy(--p);
    }
    alloc.deallocate(data, 3);
}

template<typename F, typename T1, typename T2>
void filp(F f, T1 &&lhs, T2 &&rhs)
{
    f(std::forward<T2>(rhs), std::forward<T1>(lhs));
}

int main()
{
    filp(func_rvalue, 88, 90);

    return 0;
}