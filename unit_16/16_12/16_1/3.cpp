/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-22 19:47:13
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-22 22:23:55
 * @FilePath: /C++Primer/unit_16/16_12/16_1/3.cpp
 * @Description:测试默认模板实参
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <functional>
#include <iostream>

template<typename T, typename F = std::less<T>>
int myCompare(const T &v1, const T &v2, F f = F())
{
    if (f(v1, v2))
        return -1;
    if (f(v2, v1))
        return 1;

    return 0;
}

int main()
{
    std::cout << myCompare(1, 2) << std::endl;

    return 0;
}