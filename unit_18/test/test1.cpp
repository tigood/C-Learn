/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-05-01 22:38:58
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-05-01 22:44:13
 * @FilePath: /C++Primer/unit_18/test/test1.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <exception>
#include <iostream>
#include <stdexcept>

int divide(int a, int b)
{
    if (b == 0)
        throw std::runtime_error("divisor is zero");
    return a / b;
}

int main()
{
    try {
        std::cout << divide(10, 0) << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
}