#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H
#include <iostream>
#include <vector>
#include <memory>
#include <set>
#include <map>

class QueryResult;

class TextQuery {
	friend QueryResult;

public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery() = delete;
    TextQuery(std::ifstream &); // 传入一个文件流

    // 公开方法
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<std::vector<std::string>> file_;  // 指向一个vector的智能指针
    std::map<std::string, std::shared_ptr<std::set<line_no>>> word_info_;
};

#endif