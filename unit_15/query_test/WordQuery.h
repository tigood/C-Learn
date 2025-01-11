#ifndef WORD_QUERY_H
#define WORD_QUERY_H

#include "QueryResult.h"
#include "Query_base.h"
#include "TextQuery.h"
#include <string>

class WordQuery : public Query_base {
	friend class Query;  
	// Query使用WordQuery构造函数
	WordQuery(const std::string& s):
		query_word(s) {
			std::cout << "WordQuery::WordQuery(" + s + ")\n";
		}

	// 覆盖的虚函数
	QueryResult eval(const TextQuery& t) const override {
		return t.query(query_word);
	}
	std::string rep() const override {
		return query_word;  // 返回查询的单词
	}

	std::string query_word;			// 要查找的单词
};


#endif