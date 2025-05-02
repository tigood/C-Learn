/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-05-01 22:11:48
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-05-01 22:14:23
 * @FilePath: /C++Primer/unit_17/17_2_2/17_10.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <bitset>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = {1, 2, 3, 5, 8, 13, 21};
    std::bitset<32>  bset;

    for (auto i : v)
        bset.set(i);

    std::bitset<32> bset2;
    for (unsigned i = 0; i != 32; i++)
        bset2[i] = bset[i];

    std::cout << bset << std::endl;
    std::cout << bset2 << std::endl;
    return 0;
}