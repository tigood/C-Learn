/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-29 14:58:23
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-29 17:55:48
 * @FilePath: /C++Primer/unit_16/16_3/16_48.cpp
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