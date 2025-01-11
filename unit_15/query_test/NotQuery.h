#ifndef NOT_QUERY_H
#define NOT_QUERY_H

#include "Query.h"
#include "QueryResult.h"
#include "Query_base.h"
#include "TextQuery.h"


// ～运算符生成一个NotQuery，其中保存着一个需要对其取反的Query
class NotQuery : public Query_base {
	friend Query operator~(const Query &);  // 将重载的运算符声明为友元函数

	// 构造函数
	NotQuery(const Query& q): query(q) {
		std::cout << "NotQuery构造函数" << std::endl;
	}

	// 实现重载方法
	std::string rep() const override{
		return "~(" + query.rep() + ")";
	}

	QueryResult eval(const TextQuery&) const override;
	
	// 属性
	Query query;
};

inline Query operator~(const Query &operand) {
	return std::shared_ptr<Query_base>(new NotQuery(operand));
	// 这里是一个隐式转换，调用的时Query接受智能指针的构造函数，因为该构造函数没有加"explicit"显式修饰符，
	// 所以这里可以进行隐式转换
}

#endif