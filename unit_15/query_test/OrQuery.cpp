#include "OrQuery.h"
#include "TextQuery.h"
#include <iterator>
#include <memory>
#include <algorithm>

Query operator|(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery& t) const {
	QueryResult left = lhs.eval(t), right = rhs.eval(t);

	auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
	
	// 插入右侧运算符对象所得的行号
	ret_lines->insert(right.begin(), right.end());

	return QueryResult(rep(), ret_lines, left.get_file());
}