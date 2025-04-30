/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-29 14:58:23
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-29 18:44:00
 * @FilePath: /C++Primer/unit_16/16_4_2/16_56.cpp
 * @Description: 包扩展
 *               1. 包扩展的基本形式是在函数模板的参数列表中使用省略号(...)
 *               2. 省略号的作用是表示参数包，即可以接受任意数量的参数
 *               3. 省略号的位置可以是函数模板的参数列表的最后一个参数，也可以是第一个参数
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

template<typename Printable>
void print(std::ostream &os, Printable printable)
{
    os << printable << std::endl;
}

template<typename Printable, typename... Args>
void print(std::ostream &os, Printable printable, Args const &...args)
{
    os << printable << ", ";
    return print(os, args...);
}

template<typename... Args>
void errorMsg(std::ostream &os, Args const &...args)
{
    print(os, debug_rep(args)...);
}

int main()
{
    errorMsg(std::cout, 1, "hello world!", 2);
    errorMsg(std::cout, 1);

    return 0;
}