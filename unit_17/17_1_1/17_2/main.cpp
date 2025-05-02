/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-30 13:07:03
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-30 13:08:57
 * @FilePath: /C++Primer/unit_17/17_1_1/17_2/main.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

int main()
{
    std::tuple<std::string, std::vector<std::string>, std::pair<std::string, int>> tup(
        "hello", {"world", "!"}, {"good", 1});
    std::cout << std::get<0>(tup) << std::endl;
    std::cout << std::get<1>(tup)[0] << std::endl;
    std::cout << std::get<2>(tup).first << std::endl;
    std::cout << std::get<2>(tup).second << std::endl;

    return 0;
}