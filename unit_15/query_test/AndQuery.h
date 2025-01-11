#ifndef AND_QUERY_H
#define AND_QUERY_H

#include "BinaryQuery.h"
#include "Query.h"
#include "QueryResult.h"
#include "Query_base.h"
#include "TextQuery.h"
#include <memory>

class AndQuery: public BinaryQuery {
	friend Query operator&(const Query&, const Query&);

	// 构造函数	调用父类构造函数
	AndQuery(const Query &left, const Query &right):
		BinaryQuery(left, right, "&") {
			std::cout << "AndQuery构造函数" << std::endl;
		}

	// 具体实现
	QueryResult eval(const TextQuery&) const override;
};


Query operator&(const Query &lhs, const Query &rhs);

#endif