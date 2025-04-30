/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-30 12:20:06
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-30 12:43:59
 * @FilePath: /C++Primer/unit_16/16_5/16_63/main.cpp
 * @Description: 模板
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <cstring>
#include <iostream>
#include <vector>

template<typename T>
std::size_t count(std::vector<T> const &vec, T value)
{
    auto count = 0u;
    for (auto const &elem : vec)
        if (value == elem)
            ++count;
    return count;
}

// 特化版本：适用于 vector<char*> 和 const char*
template<>
std::size_t count(std::vector<const char *> const &vec, const char *value)
{
    auto count = 0u;
    for (auto const &elem : vec)
        if (0 == strcmp(value, elem))
            ++count;
    return count;
}

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << count(vec, 5) << std::endl;

    std::vector<const char *> vec2 = {"hello", "world", "hello",
                                      "world", "hello", "world"};
    std::cout << count(vec2, "hello") << std::endl;
    return 0;
}