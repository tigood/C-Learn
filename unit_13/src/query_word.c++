#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <sstream>
#include <memory>
#include "../include/query_word.hpp"
#include "../include/strvec.hpp"

// 记得为file_vector容器开辟空间，不然直接插入回报错
TextQuery::TextQuery(std::ifstream &is):file_(std::make_shared<StrVec>()) {
    std::string line;
    while (std::getline(is, line)) {
        // 保存当前行
        file_->push_back(line);
        line_no current_line_no = file_->size();
        // 创建一个文本流
        std::istringstream in_word(line);
        std::string temp_word;
        while (in_word >> temp_word)
        {
            auto &lines = word_info_[temp_word];  // 这里使用的是引用，所以修改lines就可以个改变容器的值
            if (!lines) {
                // 走到这里说明这个单词是第一次出现
                // 分配一个新的set空间
                lines.reset(new std::set<line_no>);
            }
            lines->insert(current_line_no);  // 将此行号插入到set中
        }
    }
}

QueryResult TextQuery::query(const std::string &word) const {
    // 创建一个指向空集合的智能指针，如果没有找到就返回这个集合指针
    std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    // 查找单词是否在map中
    auto loc = word_info_.find(word);
    if (loc != word_info_.end()) {
        // 这说明找到了
        return QueryResult(word, loc->second, file_);
    }
    return QueryResult(word, nodata, file_);
}

std::ostream &print(std::ostream &os, const QueryResult &qr) {
    // 输出查询到的结果
    std::cout << qr.sought_ << "一共在" << qr.lines_->size() << "行中：" << std::endl;
    for (auto &item : *qr.lines_) {
        std::cout << "(line " << item << ") " << *(qr.file_->begin() + item - 1) << std::endl;
    }
    std::cout << std::endl;
    // 再将这个标准输出函数返回，这样就可以支持链式操作了
    return os;
}