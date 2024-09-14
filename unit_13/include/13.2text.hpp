#ifndef _13_2_TEXT
#define _13_2_TEXT
#include <iostream>

class HasPtr{
public:
    HasPtr() = delete;
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0), use(new std::size_t(0)) {}
    // 拷贝构造函数
    HasPtr(const HasPtr &);
    // 移动构造函数
    HasPtr(HasPtr &&rhs) noexcept : ps(rhs.ps), i(rhs.i) { rhs.ps = 0; }
    // // 赋值拷贝符号
    // HasPtr& operator=(const HasPtr&);
    // 赋值运算符既是拷贝赋值运算符，也是移动赋值运算符
    HasPtr &operator=(HasPtr rhs) { swap(*this, rhs);
        return *this;
    }
    // 析构函数
    ~HasPtr();
    // 友元函数
    friend void swap(HasPtr &, HasPtr &);

private:
    std::string *ps;
    int i;
    std::size_t *use;  // 用来记录有多少个对象共享*ps对象
};

class TreeNode {
public:
    TreeNode(): value(std::string()), count(new int(1)), left(nullptr), right(nullptr) {}
    // 拷贝构造函数
    TreeNode(const TreeNode &other): value(other.value), count(other.count), left(other.left), right(other.right) {}
    // 拷贝运算符重载
    TreeNode &operator=(const TreeNode &);
    // 析构函数
    ~TreeNode() {
        if (--*count == 0) {
            delete count;
            delete left;
            delete right;
        }
    }

private:
    std::string value;
    int *count;
    TreeNode *left;
    TreeNode *right;
};

class BinStrTree{
public:
    BinStrTree(): root(new TreeNode()) {}
    // 拷贝构造函数
    BinStrTree(const BinStrTree &other): root(new TreeNode(*other.root)) {}
    // 赋值运算符重载
    BinStrTree &operator=(const BinStrTree &);
    // 析构函数
    ~BinStrTree() {
        delete root;
    }

private:
    TreeNode *root;
};

#endif