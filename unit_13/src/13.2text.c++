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

// // 拷贝运算符重载
// HasPtr&
// HasPtr::operator=(const HasPtr &other) {
//     // 递增右侧运算对象的引用计数
//     (*other.use)++;
//     if (--*use == 0) {
//         delete ps;
//         delete use;
//     }
//     // 将右侧对象拷贝到左侧
//     ps = other.ps;
//     i = other.i;
//     use = other.use;
//     return *this;
// }

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

// HasPtr的交换函数
// 如果我们不定义这个swap交换函数，HasPtr类就会使用系统内置的swap函数
// 因为这个一个类值对象，拷贝的时候时重新开辟空间的，所以交换时就会进行不必要的拷贝
// 我们交换只是希望交换指针的值，所以需要我们自己自定义一个swap函数
inline
void swap(HasPtr &lhs, HasPtr &rhs) {
    // 使用内置的swap函数交换两个属性的值
    std::swap(lhs.ps, rhs.ps);
    std::swap(lhs.i, rhs.i);
    std::cout << "数据交换成功";
}
