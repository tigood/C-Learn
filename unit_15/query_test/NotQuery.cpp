#include "NotQuery.h"
#include "TextQuery.h"
#include <memory>
#include <set>

QueryResult NotQuery::eval(const TextQuery& t) const {
	// 获取当前对象的查询结果
	auto result = query.eval(t);

	// 开辟一个set空间
	auto ret_lines = std::make_shared<std::set<line_no>>();

	// 对结果的所有行进行迭代
	auto beg = result.begin(), end = result.end();
	// 对于输入文件的每一行，如果该行不在result当中，则将其添加到ret_lines
	auto sz = result.get_file()->size();  // 返回输入文件的长度
	for (size_t n = 0; n != sz; n++) {
		if (beg == end || *beg != n) {
			ret_lines->insert(n);  // 如果不在result当中，添加这一行
		} else if (beg != end) {
			++beg;   // 否则继续获得result的下一行
		}
	}

	return QueryResult(rep(), ret_lines, result.get_file());
}