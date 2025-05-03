/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-05-02 17:35:04
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-05-02 17:51:36
 * @FilePath: /C++Primer/unit_18/18_2_2/18_16.cpp
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
namespace Exercise
{
    int       ivar = 0;
    double    dvar = 0.0;
    const int limit = 1000;
} // namespace Exercise

int ivar = 0;
// 位置1
// using Exercise::ivar;
// using Exercise::dvar;
using Exercise::limit;

// using namespace Exercise;

void manip()
{
    // 位置2
    // using Exercise::dvar;
    // using Exercise::ivar;
    // using Exercise::limit;

    // using namespace Exercise;

    double dvar = 3.1416;
    int    iobj = limit + 1;
    ++ivar;
    ++::ivar;
}