#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <memory>
#include <set>

// 基类
class Quote {
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price): bookNo(book), price(sales_price) { }
	std::string isbn() const { return bookNo; }

	// 拷贝构造函数
	Quote(const Quote &other) = default;
	// 拷贝赋值运算符
	Quote &operator=(const Quote &other) = default;

	// 移动构造函数
	Quote(Quote &&other) noexcept = default;
	// 移动赋值运算符
	Quote &operator=(Quote &&other) noexcept = default;

	// 返回给定的数量书籍的销售总额
	// 派生类负责改写并使用不同的折扣计算算法
	virtual double net_price(std::size_t n) const { return n * price; }  // virtual 表示这是一个虚函数，对他进行动态绑定
	// debug
	virtual void debug(std::ostream &os) const;  // 仅声明
	virtual ~Quote() = default;  // 对析构函数进行动态绑定

	// 该虚函数返回当前对象的一份动态分配的拷贝
	virtual Quote* clone() const & {
		return new Quote(*this);
	}

	virtual Quote* clone() && {
		return new Quote(std::move(*this));
	}
private:
	std::string bookNo;  // 书籍编号
protected:
	double price = 0.0;
};

class Bulk_quote : public Quote {
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &, double, std::size_t, double);
	// 覆盖父类虚函数
	double net_price(std::size_t) const override;
	void print_hello() const {std::cout << "hello world" <<std::endl;}
	void debug(std::ostream &os) const override;  // 仅声明

	Bulk_quote* clone() const & override {
		return new Bulk_quote(*this);
	}

	Bulk_quote* clone() && override {
		return new Bulk_quote(std::move(*this));
	}
private:
	std::size_t min_qty = 0; // 使用折扣政策的最底购买量
	double discount = 0.0;  // 用小数表示的折扣额
};

// 自定义销售类
class My_quote : public Quote {
public:
	My_quote() = default;
	My_quote(const std::string &, double, std::size_t, double);
	// 覆盖父类虚函数
	double net_price(std::size_t) const override;

	void debug(std::ostream &os) const override;  // 仅声明
private:
	std::size_t max_count = 0;
	double discount = 0.0;
};

// 辅助类
class Basket {
private:
	// 该函数用于比较shared_ptr，multiset成员会用到他
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) {
		return lhs->isbn() < rhs->isbn();
	}

	// 使用multiset保存多个报价，按照compare成员排序
	std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};

public:
	void add_item(const Quote &sale) {
		items.insert(std::shared_ptr<Quote>(sale.clone()));
	}

	void add_item(const Quote &&sale) {
		items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
	}

	double total_receipt(std::ostream &) const;
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

	// Quote *q_base_q = &bulk_q;
	// double result = (*q_base_q).net_price(10);
	// bulk_q.print_hello();
	// std::cout << result << std::endl;
	// print_total(std::cout, base_q, 10);  // 基类 不打折
	// print_total(std::cout, bulk_q, 4);  // 派生类，本数不够，不打折
	// print_total(std::cout, bulk_q, 10);  // 派生类，数量狗，打折
	// print_total(std::cout , *q_base_q, 10);
	base_q.debug(std::cout);
	std::cout << std::endl;
	bulk_q.debug(std::cout);
	std::cout << std::endl;
	my_q.debug(std::cout);
	std::cout << std::endl;

	// std::vector<Quote> basket;
	// basket.push_back(Quote("2027", 100));
	// basket.push_back(Bulk_quote("2028", 80, 3, 0.8));
	// double sum = 0.0;
	// for (auto item : basket) {
	// 	sum += item.net_price(5);
	// }
	// std::cout << "sum = " << sum << std::endl;
	// 900

	// std::vector<std::shared_ptr<Quote>> basket;
	// basket.push_back(std::make_shared<Quote>("2027", 100));
	// basket.push_back(std::make_shared<Bulk_quote>("2028", 80, 3, 0.8));
	// double sum = 0.0;
	// for (auto item : basket) {
	// 	sum += item->net_price(5);
	// }
	// std::cout << "sum = " << sum << std::endl;
	// 580
	Basket basket;
	basket.add_item(base_q);
	basket.add_item(bulk_q);
	basket.total_receipt(std::cout);

	return 0;
}

void Quote::debug(std::ostream &os) const {
	os << "		书籍编号：" << isbn() << "	书籍价格：" << price;
}

// 子类构造函数的实现
Bulk_quote::Bulk_quote(const std::string &book, double p, std::size_t qty, double disc):
	Quote(book, p), min_qty(qty), discount(disc) {}

double Bulk_quote::net_price(std::size_t cnt) const {
	if (cnt >= min_qty)
		// 走到这里说明满足优惠条件
		return cnt * (1 - discount) * price;
	else
		// 走到这里说明不满足
		return cnt * price;
}

void Bulk_quote::debug(std::ostream &os) const {
	Quote::debug(os);  // 调用父类的debug
	os << "		min_qty：" << min_qty << "		discount：" << discount;
}

My_quote::My_quote(const std::string &book_id, double p, std::size_t count, double disc):
	Quote(book_id, p), max_count(count), discount(disc) {}

double My_quote::net_price(std::size_t cnt) const {
	if (cnt < max_count)
		return (1 - discount) * cnt * price;
	else
		return (1 - discount) * max_count * price + (cnt - max_count) * price;
}

void My_quote::debug(std::ostream &os) const {
	Quote::debug(os);
	os << "		max_count：" << max_count << "		discount：" << discount;
}

double Basket::total_receipt(std::ostream &os) const  {
	double sum = 0.0;  // 保存实时计算出的总价格
	for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
		sum += print_total(os, **iter, items.count(*iter));
	}

	os << "Total Sale: " << sum << std::endl;

	return sum;
}
