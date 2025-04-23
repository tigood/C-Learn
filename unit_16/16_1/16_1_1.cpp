/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-01-11 19:48:50
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-02-23 01:59:01
 * @FilePath: /C++Primer/unit_16/16_1/16_1_1.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <cstring>
#include <iostream>
#include <bits/c++config.h>

// 模板函数
template <typename T>
int compare(
    const T &v1,
    const T &v2)
{ // 通过将类型设置为const，保证了也可以处理不能进行拷贝的类型
    if (v1 < v2)
        return -1;
    if (v1 > v2)
        return 1;
    return 0;
}

// template <typename T>
// int compare(const T& v1, const T& v2) {  //
// 通过将类型设置为const，保证了也可以处理不能进行拷贝的类型 	if (v1 < v2) return
// -1; 	if (v2 < v1) return 1; 	return 0;
// }

template <typename T>
T return_tmp(T *p_tmp)
{
    T tmp = *p_tmp;

    return tmp;
}

template <unsigned N, unsigned M>
// (&p1)[N] 表示p1是一个引用，指向一个长度为N的字符数组
int compare_1(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2);
}

int main()
{
    int a = 10;
    std::cout << compare(1, 2) << std::endl;
    std::cout << compare("hello", "lello") << std::endl;
    std::cout << compare("hello", "hello") << std::endl;
    std::cout << return_tmp(&a) << std::endl;

    return 0;
}