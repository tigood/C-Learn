#ifndef OR_QUERY_H
#define OR_QUERY_H

#include "BinaryQuery.h"
#include "Query.h"
#include "QueryResult.h"
#include "TextQuery.h"
#include <memory>

class OrQuery: public BinaryQuery {
	friend Query operator|(const Query&, const Query&);

	// 构造函数
	OrQuery(const Query &left, const Query &right):
		BinaryQuery(left, right, "|") {
			std::cout << "OrQuery构造函数" << std::endl;
		}
	// 实际实现
	QueryResult eval(const TextQuery&) const override;
};

Query operator|(const Query &lhs, const Query &rhs);

#endif