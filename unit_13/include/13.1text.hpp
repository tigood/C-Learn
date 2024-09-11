#ifndef _13_1_TEXT
#define _13_1_TEXT
#include <string>
#include <iostream>
class HasPtr{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0) {}
    HasPtr(const HasPtr &other_hasPtr);  // 拷贝构造函数
    // 赋值运算符
    HasPtr &operator=(const HasPtr &);
    bool operator<(const HasPtr &);  // 重载小于运算符
    // 析构函数
    ~HasPtr();
    // 友类函数
    friend void swap(HasPtr &, HasPtr &);

    // 方法
    void showContent() const;

private:
    std::string *ps;
    int i;
};

// 13.13
struct X {
    X() { std::cout << "X()" << std::endl; }
    X(const X &) { std::cout << "X(const X&)" << std::endl; }
    X &operator=(const X &) { 
        std::cout << "X& operator=(const X&)" << std::endl;
        return *this;
    }
    ~X() { std::cout << "~X()" << std::endl; }
};

class NoCopy{
public:
    NoCopy() = default;  // 使用合成的默认构造函数
    NoCopy(const NoCopy &) = delete;  // 阻止拷贝构造函数
    NoCopy &operator=(const NoCopy &) = delete;  // 阻止拷贝运算符
    ~NoCopy() = default;  // 使用合成的析构函数
};

// 13.18
class Employee{
public:
    Employee();
    Employee(const std::string &name);
    Employee(const Employee &) = delete;
    Employee &operator=(const Employee &) = delete;
    int id() const { return no_; }

private:
    std::string name_;
    int no_;
    static int s_increment_;
};

HasPtr::HasPtr(const HasPtr &other_hasPtr) :
    ps(new std::string(*other_hasPtr.ps)), i(other_hasPtr.i) {}

HasPtr&
HasPtr::operator=(const HasPtr &other) {
    // 判断是否为自赋值
    if (this != &other) {
        // 走到这里说明不是自赋值
        // 释放旧内存
        delete ps;
        ps = new std::string(*other.ps);
        i = other.i;
    }
    return *this;
}

bool
HasPtr::operator<(const HasPtr &other) {
    return *ps < *other.ps;
}

// 析构函数
HasPtr::~HasPtr() {
    // 清除开辟的空间
    delete ps;
    // 输出提示
    std::cout << "我被析构了！" << std::endl;
}

void
HasPtr::showContent() const {
    std::cout << *ps << std::endl;
}

inline
void swap(HasPtr &lhs, HasPtr &rhs) {
    // 交换指针
    std::swap(lhs.ps, rhs.ps);
    std::swap(lhs.i, rhs.i);
    std::cout << "交换成功" << std::endl;
    ;
}

Employee::Employee():
    no_(s_increment_++) {}

Employee::Employee(const std::string& name): 
    name_(name), no_(s_increment_++) {}

int Employee::s_increment_ = 0;

#endif