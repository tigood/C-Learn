/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2024-09-14 21:05:06
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-02-23 01:29:25
 * @FilePath: /C++Primer/unit_13/src/Stringtext.c++
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include "../include/String.hpp"
#include <vector>
#include <iostream>
#include <bits/c++config.h>

void text_1()
{
    std::vector<String> svect;
    svect.reserve(3);
    // 当使用push_back添加一个常量字符串的时候会优先使用移动构造函数
    svect.push_back("hello");
    svect.push_back("world");
    svect.push_back("tigood");
    std::vector<String> v1{"hello", "tigood"};
    std::vector<String> v2;
    // 而在两个对象之间的拷贝的时候会使用拷贝构造函数
    v2 = v1;
    std::cout << "Done" << std::endl;
    String s4("hello");
    std::cout << s4 << std::endl;
    std::cin >> s4;
    std::cout << s4 << std::endl;
}

int main()
{
    text_1();

    return 0;
}