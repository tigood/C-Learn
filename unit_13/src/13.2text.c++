#include <iostream>
#include "../include/13.2text.hpp"

// 拷贝构造函数
HasPtr::HasPtr(const HasPtr &other) : ps(other.ps), i(other.i), use(other.use) { (*use)++; }

// 析构函数
HasPtr::~HasPtr() {
    // 如果该对象取消引用之后，之后释放空间
    if (--*use == 0) {
        delete ps;
        delete use;
    }
}

// 拷贝运算符重载
HasPtr&
HasPtr::operator=(const HasPtr &other) {
    // 递增右侧运算对象的引用计数
    (*other.use)++;
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    // 将右侧对象拷贝到左侧
    ps = other.ps;
    i = other.i;
    use = other.use;
    return *this;
}

TreeNode&
TreeNode::operator=(const TreeNode &other) {
    ++*other.count;
    if (--*count == 0) {
        delete count;
        delete left;
        delete right;
    }
    value = other.value;
    left = other.left;
    right = other.right;
    count = other.count;
    return *this;
}

BinStrTree&
BinStrTree::operator=(const BinStrTree &other) {
    // 删除原来的动态空间
    delete root;
    root = new TreeNode(*other.root);
    return *this;
}
