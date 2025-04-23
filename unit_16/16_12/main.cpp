/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-02-23 21:42:52
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-02-23 21:57:17
 * @FilePath: /C++Primer/unit_16/16_12/main.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <string>

#include "Blob.h"

int main()
{
    Blob<int>         ints{1, 2, 3, 4};
    Blob<std::string> names{"liushijia", "wangyike", "tigood"};
    std::cout << ints[1] << std::endl;
    std::cout << names[0] << " love " << names[1] << std::endl;

    return 0;
}
