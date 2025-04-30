/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-30 12:09:58
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-30 12:16:07
 * @FilePath: /C++Primer/unit_16/16_5/16_62/main.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <unordered_set>

#include "Sales_data.h"

int main()
{
    std::unordered_multiset<Sales_data> mset;
    Sales_data                          sd("Python", 10, 0.98);

    mset.emplace(sd);
    mset.emplace("C++", 5, 9.99);

    for (const auto &item : mset) {
        std::cout << "the hash code of " << item.isbn() << ":\n0x" << std::hex
                  << std::hash<Sales_data>()(item) << "\n";
    }

    return 0;
}