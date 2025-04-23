/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-01-12 13:19:57
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-02-23 14:39:20
 * @FilePath: /C++Primer/unit_16/16_1/16_1_4.cpp
 * @Description:	练习题4
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <iostream>
#include <vector>
#include <string>

namespace ch16
{
template <typename Iterator, typename Value>
auto find(Iterator first, Iterator last, const Value &value)
{
    for (; first != last && *first != value; ++first)
        ;

    return first;
}
} // namespace ch16

int main()
{
    std::vector<int> v{1, 2, 3, 4, 5, 6};
    auto is_in_vector = v.cend() != ch16::find(v.cbegin(), v.cend(), 4);
    std::cout << (is_in_vector ? "found\n" : "not found!\n");

    std::vector<std::string> str_v{"hello", "world", "aa", "bb", "cc", "dd"};
    auto str_in_list = str_v.cend() != ch16::find(str_v.cbegin(), str_v.cend(), "world");
    std::cout << (str_in_list ? "found\n" : "not found!\n");
}