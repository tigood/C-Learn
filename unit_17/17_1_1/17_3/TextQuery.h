/*
 * @Author: tigood 3020422083@qq.com
 * @Date: 2025-05-01 00:24:35
 * @LastEditors: tigood 3020422083@qq.com
 * @LastEditTime: 2025-05-01 00:31:21
 * @FilePath: /C++Primer/unit_17/17_1_1/17_3/TextQuery.h
 * @Description: 使用tuple做为queryResult
 *
 * Copyright (c) 2025 by tigood, All Rights Reserved.
 */
#pragma once
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

class TextQuery
{
public:
    using index_Tp = std::vector<std::string>::size_type;
    using resultType = std::tuple<std::string, std::shared_ptr<std::set<index_Tp>>,
                                  std::shared_ptr<std::vector<std::string>>>;

    TextQuery(std::ifstream &);

    resultType query(const std::string &) const;

private:
    std::shared_ptr<std::vector<std::string>>                  file_;
    std::map<std::string, std::shared_ptr<std::set<index_Tp>>> wm_;
};