/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-30 12:50:17
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-30 12:57:06
 * @FilePath: /C++Primer/unit_16/16_5/16_65/main.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <iostream>
#include <sstream>
#include <string>

template<typename T>
std::string debug_rep(const T &t);

template<typename T>
std::string debug_rep(T *p);

std::string debug_rep(const std::string &s);
std::string debug_rep(char *p);
std::string debug_rep(const char *p);

template<typename T>
std::string debug_rep(const T &t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template<typename T>
std::string debug_rep(T *p)
{
    std::ostringstream ret;
    ret << "pointer: " << p;

    if (p) {
        ret << " " << debug_rep(*p);
    }
    else {
        ret << "null pointer";
    }

    return ret.str();
}

/**
 * @brief 模板特例化
 * 模板特例化是一个模板的一个特定实例化版本。
 * 模板特例化的形式是：
 * template<>
 * std::string debug_rep(char *p)
 * 匹配的时候，非模板重载函数版本的优先级高于特例化版本的优先级。
 */

// 模板特例化
template<>
std::string debug_rep(char *p)
{
    return debug_rep(std::string(p));
}

template<>
std::string debug_rep(const char *p)
{
    return debug_rep(std::string(p));
}

// 无模板版本
std::string debug_rep(const std::string &s) { return '"' + s + '"'; }

std::string debug_rep(char *p) { return debug_rep(std::string(p)); }

std::string debug_rep(const char *p) { return debug_rep(std::string(p)); }

int main()
{
    std::string s("hello");
    char       *p = &s[0];
    std::cout << debug_rep(s) << std::endl;
    std::cout << debug_rep(p) << std::endl;
    std::cout << debug_rep(1) << std::endl;
    return 0;
}