/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-02-24 12:22:29
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-02-24 12:33:58
 * @FilePath: /C++Primer/unit_16/16_12/ScreenTest.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include "Screen.h"

int main()
{
    Screen<5, 5> s('a');
    std::cout << s;
    std::cin >> s;
    std::cout << s;
}