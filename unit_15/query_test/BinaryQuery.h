#ifndef BINARY_QUERY_H
#define BINARY_QUERY_H

#include "Query.h"
#include "Query_base.h"

class BinaryQuery: public Query_base {
// 定义为保护修饰符，是因为子类要访问
protected:
	// 构造函数
	BinaryQuery(const Query& l, const Query& r, std::string s):
		lhs(l), rhs(r), opSym(s) {
			std::cout << "BinaryQuery构造函数" << std::endl;
		}

	// 实现虚函数
	std::string rep() const {
		return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
	}
	// 不实现eval，继续保留这个虚函数，让子类去实现，当前类还是一个抽象类

	// 属性
	Query lhs, rhs; 		// 左侧和右侧运算对象
	std::string opSym;    	// 运算符的名字
};

#endif