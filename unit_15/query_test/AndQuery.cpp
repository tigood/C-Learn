#include "AndQuery.h"
#include "TextQuery.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <set>

Query operator&(const Query &lhs, const Query &rhs) {
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery& t) const {
	// 获得左右对象查询的到的值
	auto right = rhs.eval(t), left = lhs.eval(t);

	// 创建一个保存两个set交集结果的集合
	auto ret_lines = std::make_shared<std::set<line_no>>();

	// 将两个范围的交集写入一个目的迭代器
	// 使用的是一个标准库算法  然后目标集合使用inserter开获取一个插入迭代器
	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));

	return QueryResult(rep(), ret_lines, left.get_file());
}