/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-02-24 11:04:42
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-22 19:25:46
 * @FilePath: /C++Primer/unit_16/16_12/Screen.h
 * @Description: Screen类的实现
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <iostream>
#include <istream>
#include <ostream>
#include <string>

// 向前声明
template<unsigned h, unsigned W>
class Screen;

// 输出运算符重载
template<unsigned H, unsigned W>
std::ostream &operator<<(std::ostream &os, const Screen<H, W> &c);

// 输入运算符重载
template<unsigned H, unsigned W>
std::istream &operator>>(std::istream &is, Screen<H, W> &c);

template<unsigned H, unsigned W>
class Screen
{
    friend std::ostream &operator<< <>(std::ostream &os, const Screen<H, W> &c);
    friend std::istream &operator>><>(std::istream &is, Screen<H, W> &c);

public:
    typedef std::string::size_type pos;
    Screen() = default;
    Screen(const char c) : content(H * W, c) {}

    char    get() const { return content[cursor]; }
    Screen &move(pos r, pos c);

private:
    pos         cursor = 0;
    pos         height = H, width = W;
    std::string content;
};

template<unsigned H, unsigned W>
Screen<H, W> &Screen<H, W>::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;

    return *this;
}

template<unsigned H, unsigned W>
std::ostream &operator<<(std::ostream &os, const Screen<H, W> &c)
{
    unsigned i;
    for (i = 0; i < c.height; i++) {
        os << c.content.substr(0, c.width) << std::endl;
    }

    return os;
}

template<unsigned H, unsigned W>
std::istream &operator>>(std::istream &is, Screen<H, W> &c)
{
    char a;
    is >> a;
    std::string temp(H * W, a);
    c.content = temp;

    return is;
}
