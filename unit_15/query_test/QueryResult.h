#ifndef QUERY_RESULT_H
#define QUERY_RESULT_H

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "TextQuery.h"

class QueryResult{
    friend std::ostream &print(std::ostream &, const QueryResult &);

public:
    QueryResult() = delete;
    // 构造函数
    QueryResult(std::string s, 
                std::shared_ptr<std::set<TextQuery::line_no>> lines, 
                std::shared_ptr<std::vector<std::string>> file):
        sought_(s), lines_(lines), file_(file) {
        	std::cout << "QueryResult构造函数" << std::endl;
        }

    const std::shared_ptr<std::vector<std::string>> get_file() const { return file_; }

    std::set<TextQuery::line_no>::iterator
    begin() { return lines_->begin(); }

    std::set<TextQuery::line_no>::iterator
    end() { return lines_->end(); }

private:
    std::string sought_;  // 查询的单词
    std::shared_ptr<std::set<TextQuery::line_no>> lines_;  // 一个指向保存行号的集合的智能指针
    std::shared_ptr<std::vector<std::string>> file_;  // 指向保存文件内容容器的智能指针
};

std::ostream &print(std::ostream &, const QueryResult &);
#endif