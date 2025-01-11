#ifndef QUERY_H
#define QUERY_H
#include "QueryResult.h"
#include "Query_base.h"
#include "TextQuery.h"
#include "WordQuery.h"
#include <memory>
#include <ostream>
#include <string>

class Query {
	// 这些运算符需要访问接受shared_ptr的构造函数，而该函数是私有的
	friend Query operator~(const Query &);
	friend Query operator|(const Query &, const Query &);
	friend Query operator&(const Query &, const Query &);

public:
	// 构建一个新的WordQuery
	inline
	Query(const std::string &s) : q(new WordQuery(s)) {
		std::cout << "Query::Query(const std::string& s) where s="+s+"\n";
	}  // 分配一个新的WordQuery，然后令其指针成员指向新分配的对象
	// 接口函数：调用对应的Query_bash操作
	QueryResult eval(const TextQuery &t) const {
		return q->eval(t);
	}
	std::string rep() const {
		return q->rep();
	}

private:
	Query(std::shared_ptr<Query_base> query) : q(query) {
		std::cout << "Query::Query(std::shared_ptr<Query_base> query)\n";
	}
	std::shared_ptr<Query_base> q;
};

inline std::ostream&
operator << (std::ostream &os, const Query &query) {
	return os << query.rep();
}

#endif