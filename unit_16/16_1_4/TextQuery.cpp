/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-04-23 12:55:38
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-04-23 20:07:38
 * @FilePath: /C++Primer/unit_16/16_1_4/TextQuery.cpp
 * @Description: 文本查询类源文件
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include "TextQuery.h"

#include <sstream>
#include <string>

#include "DebugDelete.h"
#include "QueryResult.h"

TextQuery::TextQuery(std::ifstream &fin)
    : sp_fileData_(new std::vector<std::string>(), DebugDelete()),
      sp_queryMap_(new std::map<std::string, std::set<int>>(), DebugDelete())
{
    std::string line;
    while (std::getline(fin, line)) {
        sp_fileData_->push_back(line);
    }
}

QueryResult TextQuery::query(const std::string &qWord) const
{
    std::size_t counter = 0;

    for (std::size_t i = 0; i < sp_fileData_->size(); i++) {
        std::stringstream lineStream((*sp_fileData_)[i]);
        std::string       word;
        while (lineStream >> word) {
            if (word == qWord) {
                counter++;
                (*sp_queryMap_)[qWord].insert(i);
            }
        }
    }

    return QueryResult(counter, qWord, sp_fileData_, sp_queryMap_);
}