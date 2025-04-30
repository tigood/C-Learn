/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-28 09:08:14
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-28 09:11:47
 * @FilePath: /C++Primer/unit_16/16_1_6/main.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <iostream>

#include "Blob.h"

int main()
{
    Blob<int> b1;
    Blob<int> b2{1, 2, 3, 4, 5};
    b1.push_back(1);
    std::cout << "b1 back: " << b1.back() << std::endl;
    for (size_t i = 0; i < b2.size(); ++i) {
        std::cout << b2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}