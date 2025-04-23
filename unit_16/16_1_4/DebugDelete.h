/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-22 20:36:51
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-22 22:20:36
 * @FilePath: /C++Primer/unit_16/16_1_4/DebugDelete.h
 * @Description:
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#ifndef DEBUGDELETE_H
#define DEBUGDELETE_H
#include <iostream>

class DebugDelete
{
public:
    DebugDelete(std::ostream &os = std::cerr) : os_(os) {}

    template<typename T>
    void operator()(T *p) const
    {
        std::cout << "delete unique_ptr\n";
        delete p;
    }

private:
    std::ostream &os_;
};
#endif // DEBUGDELETE_H