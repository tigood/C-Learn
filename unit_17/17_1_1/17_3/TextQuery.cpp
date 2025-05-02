/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-05-01 00:32:25
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-05-01 00:52:31
 * @FilePath: /C++Primer/unit_17/17_1_1/17_3/TextQuery.cpp
 * @Description：
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#include "TextQuery.h"

#include <memory>
#include <set>
#include <string>

TextQuery::TextQuery(std::ifstream &is) : file_(new std::vector<std::string>)
{
    std::string line;
    while (std::getline(is, line)) {
        file_->push_back(line);
        int index = file_->size() - 1;

        std::stringstream lineStream(line);
        std::string       word;
        while (lineStream >> word) {
            std::shared_ptr<std::set<index_Tp>> &sp_lineIndex = wm_[word];
            if (!sp_lineIndex) {
                sp_lineIndex.reset(new std::set<index_Tp>);
            }

            // 插入
            sp_lineIndex->insert(index);
        }
    }
}

TextQuery::resultType TextQuery::query(const std::string &word) const
{
    // 使用static对象，避免每次调用都创建一个新的set
    // 让查询失败时的返回值具有一致性（可以用 == 判断是否为 noData）；
    static std::shared_ptr<std::set<index_Tp>> noData(new std::set<index_Tp>);

    auto iter = wm_.find(word);
    if (iter == wm_.end()) {
        return resultType(word, noData, file_);
    }
    else {
        return resultType(word, iter->second, file_);
    }
}