/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-23 12:55:47
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-23 19:58:07
 * @FilePath: /C++Primer/unit_16/16_1_4/QueryResult.h
 * @Description: 查询结果类头文件
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#ifndef QUERYRESULT_H
#define QUERYRESULT_H
#include "TextQuery.h"

class QueryResult
{
public:
    QueryResult() = default;
    // 拷贝构造函数
    QueryResult(const QueryResult &other);

    QueryResult(const std::size_t c, const std::string &str,
                const TextQuery::SharedFilePtr &sp_f, const TextQuery::QueryMapPtr &sp_m);

    std::size_t              getCounter() const { return counter_; }
    std::string              getQueryWord() const { return queryWord_; }
    TextQuery::SharedFilePtr getSp_fileData() const { return sp_fileData_; }
    TextQuery::QueryMapPtr   getSp_queryMap() const { return sp_queryMap_; }

private:
    // 计数器
    std::size_t counter_ = 0;

    // 查询的单词
    std::string queryWord_;

    // 指向文件数据的智能指针
    TextQuery::SharedFilePtr sp_fileData_ = nullptr;

    // 指向查询结果映射的智能指针
    TextQuery::QueryMapPtr sp_queryMap_ = nullptr;
};

void print(std::ostream &os, const QueryResult &qr);

#endif