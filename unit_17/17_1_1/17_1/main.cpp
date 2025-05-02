/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-30 13:03:42
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-30 13:04:49
 * @FilePath: /C++Primer/unit_17/17_1_1/17_1/main.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <iostream>
#include <tuple>

int main()
{
    std::tuple<int, int, int> t1(1, 2, 3);

    // 访问元组中的元素
    std::cout << std::get<0>(t1) << std::endl;
    std::cout << std::get<1>(t1) << std::endl;
    std::cout << std::get<2>(t1) << std::endl;
}