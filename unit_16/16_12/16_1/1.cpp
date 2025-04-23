/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-22 19:00:55
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-23 21:14:08
 * @FilePath: /C++Primer/unit_16/16_12/16_1/1.cpp
 * @Description: 这是一个测试模板别名的代码
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <iostream>
#include <string>
#include <utility>

// 模板别名
template<typename T>
using twin = std::pair<T, T>;

// 固定一个或多个参数
template<typename T>
using pair_string = std::pair<T, std::string>;

int main()
{
    twin<std::string> names = {"liu", "shi_jia"};
    std::cout << names.first << " " << names.second << std::endl;

    return 0;
}