#ifndef _QUERY_WORD
#define _QUERY_WORD
#include <set>
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include "strvec.hpp"

class QueryResult;

class TextQuery{
    friend QueryResult;

public:
    using line_no = size_t;
    TextQuery() = delete;
    TextQuery(std::ifstream &); // 传入一个文件流

    // 公开方法
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<StrVec> file_;  // 指向一个vector的智能指针
    std::map<std::string, std::shared_ptr<std::set<line_no>>> word_info_;
};

class QueryResult{
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:
    QueryResult() = delete;
    // 构造函数
    QueryResult(std::string s, 
                std::shared_ptr<std::set<TextQuery::line_no>> lines, 
                std::shared_ptr<StrVec> file):
        sought_(s), lines_(lines), file_(file) {}

private:
    std::string sought_;  // 查询的单词
    std::shared_ptr<std::set<TextQuery::line_no>> lines_;  // 一个指向保存行号的集合的智能指针
    std::shared_ptr<StrVec> file_;  // 指向保存文件内容容器的智能指针
};

std::ostream &print(std::ostream &, const QueryResult &);

#endif