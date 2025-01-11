#include <algorithm>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

// 基类
class Quote {
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price): bookNo(book), price(sales_price) { }
	std::string isbn() const { return bookNo; }
	// 返回给定的数量书籍的销售总额
	// 派生类负责改写并使用不同的折扣计算算法
	virtual double net_price(std::size_t n) const { return n * price; }  // virtual 表示这是一个虚函数，对他进行动态绑定
	// debug
	virtual void debug(std::ostream &os) const;  // 仅声明
	virtual ~Quote() = default;  // 对析构函数进行动态绑定
private:
	std::string bookNo;  // 书籍编号
protected:
	double price = 0.0;
};

class Disc_quote : public Quote {
public:
	Disc_quote() = default;
	Disc_quote(const std::string &id, double _price, std::size_t _qty, double _discount):
		Quote(id, _price), qty(_qty), discount(_discount) {}
	// 全虚函数
	double net_price(std::size_t) const = 0;
protected:
	std::size_t qty = 0;  // 额度界限
	double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &id, double _price, std::size_t _qty, double _dis_count) : 
		Disc_quote(id, _price, _qty, _dis_count) {}
	// 覆盖父类虚函数
	double net_price(std::size_t) const override;
	void print_hello() const {std::cout << "hello world" <<std::endl;}
	void debug(std::ostream &os) const override;  // 仅声明
};

// 自定义销售类
class My_quote : public Disc_quote {
public:
	My_quote() = default;
	My_quote(const std::string &id, double price, std::size_t qty, double dis_count):
		Disc_quote(id, price, qty, dis_count) {}
	// 覆盖父类虚函数
	double net_price(std::size_t) const override;
	void debug(std::ostream &os) const override;  // 仅声明
};

// 计算并打印，销售给定数量的某种书籍所得的费用
double print_total(std::ostream &os, const Quote &item, size_t n) {
	double result = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << result << std::endl;
	return result;
}

int main() {
	Quote base_q("2024", 100);
	Bulk_quote bulk_q("2025", 100, 5, 0.2);
	My_quote my_q("2026", 100, 4, 0.3);
	base_q.debug(std::cout);
	std::cout << std::endl;
	bulk_q.debug(std::cout);
	std::cout << std::endl;
	my_q.debug(std::cout);
	std::cout << std::endl;


	return 0;
}

void Quote::debug(std::ostream &os) const {
	os << "		书籍编号：" << isbn() << "	书籍价格：" << price;
}

// 子类构造函数的实现

double Bulk_quote::net_price(std::size_t cnt) const {
	if (cnt >= qty)
		// 走到这里说明满足优惠条件
		return cnt * (1 - discount) * price;
	else
		// 走到这里说明不满足
		return cnt * price;
}

void Bulk_quote::debug(std::ostream &os) const {
	Quote::debug(os);  // 调用父类的debug
	os << "		min_qty：" << qty << "		discount：" << discount;
}

double My_quote::net_price(std::size_t cnt) const {
	if (cnt < qty)
		return (1 - discount) * cnt * price;
	else
		return (1 - discount) * qty * price + (cnt - qty) * price;
}

void My_quote::debug(std::ostream &os) const {
	Quote::debug(os);
	os << "		max_count：" << qty << "		discount：" << discount;
}