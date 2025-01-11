#include <iostream>
#include <string>

class Base {
public:
	void print_content(int num) {
		std::cout << "int num: " << num << std::endl;
	}

	void print_content(double num) {
		std::cout << "double num: " << num << std::endl;
	}

	void print_content(std::string str) {
		std::cout << "string: " << str << std::endl;
	}

	virtual ~Base() {
		std::cout << "父类析构" << std::endl;
	}
};

class Child : public Base {
public:
	// 将所有的print_content继承下来
	using Base::print_content;
	// 重写string
	void print_content(std::string str) {
		std::cout << "这是一个字符串：" << str << std::endl;
	}

	~Child() override {
		std::cout << "子类的析构函数" << std::endl;
	}


};

int main() {
	Base *basePtr = new Base();
	Child *childPtr = new Child();
	basePtr->print_content("hello");
	childPtr->print_content("world");
	delete childPtr;  // 先调用子类的析构函数，再调用父类的析构函数
	delete basePtr;  // 调用父类的析构函数

	return 0;
}