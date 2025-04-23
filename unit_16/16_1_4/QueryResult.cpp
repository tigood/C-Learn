#include "QueryResult.h"

// 拷贝构造函数
QueryResult::QueryResult(const QueryResult &other)
    : sp_queryMap_(other.sp_queryMap_),
      sp_fileData_(other.sp_fileData_),
      queryWord_(other.queryWord_),
      counter_(other.counter_)
{}

// 构造函数
QueryResult::QueryResult(const std::size_t c, const std::string &str,
                         const TextQuery::SharedFilePtr &sp_f,
                         const TextQuery::QueryMapPtr   &sp_m)
    : sp_queryMap_(sp_m), sp_fileData_(sp_f), queryWord_(str), counter_(c)
{}

void print(std::ostream &os, const QueryResult &qr)
{
    const std::string queryWord = qr.getQueryWord();

    os << "The word [" << queryWord << "] occurs " << qr.getCounter() << " times: \n";

    auto sp_f = qr.getSp_fileData();
    auto sp_m = qr.getSp_queryMap();

    for (const auto &index : (*sp_m)[queryWord]) {
        os << "Line " << index + 1 << ": " << (*sp_f)[index] << std::endl;
    }
}