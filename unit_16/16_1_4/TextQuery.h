/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-23 12:55:30
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-23 20:07:54
 * @FilePath: /C++Primer/unit_16/16_1_4/TextQuery.h
 * @Description: 文本查询类头文件
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class QueryResult;

class TextQuery
{
public:
    using SharedFilePtr = std::shared_ptr<std::vector<std::string>>;
    using QueryMapPtr = std::shared_ptr<std::map<std::string, std::set<int>>>;

    // 构造函数
    TextQuery() = default;
    // 构造函数，接受一个文件流做为参数
    TextQuery(std::ifstream &fin);

    // 查询操作
    QueryResult query(const std::string &qWord) const;

private:
    // 指向存储文件的向量的智能指针
    SharedFilePtr sp_fileData_ = nullptr;
    // 指向查询结果的映射的智能指针
    QueryMapPtr sp_queryMap_ = nullptr;
};

#endif
