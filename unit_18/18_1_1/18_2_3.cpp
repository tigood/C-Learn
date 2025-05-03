/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-05-02 10:07:00
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-05-02 10:15:35
 * @FilePath: /C++Primer/unit_18/18_1_1/18_2_3.cpp
 * @Description: 练习18.2  18.3
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include <cstddef>
#include <fstream>
#include <vector>

struct intArray
{
    intArray() : p(nullptr) {}
    explicit intArray(std::size_t s) : p(new int[s]) {}

    ~intArray() { delete[] p; }

    int *p;
};

void exercise(int *b, int *e)
{
    std::vector<int> v(b, e); // 发生异常之后，这一块会调用自己的析构函数

    // int *p = new int[v.size()]; // 着一块就不能自己析构，所以我们修改一下
    // 方案 1:
    intArray p(v.size());

    // 方案 2:
    // std::shared_ptr<int> p(new int[v.size()], [](int *p) { delete[] p; });
    // delete array using lambda

    std::ifstream in("ints"); // the object in will be destroyed.

    // 此处发生异常
}

int main() { return 0; }