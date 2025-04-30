#pragma once
#include <cstddef>
#include <functional>
#include <memory>
#include <ostream>
#include <stdexcept>

#include "DebugDelete.h"

// 向前声明
template<typename T>
class SharedPointer;

template<typename T>
void swap(SharedPointer<T> &lhs, SharedPointer<T> &rhs);

template<typename T>
class SharedPointer
{
    friend void swap<T>(SharedPointer<T> &lhs, SharedPointer<T> &rhs);

public:
    // 构造函数
    SharedPointer() = default;

    // explicit关键字用于防止隐式类型转换
    // 例如，当我们使用SharedPointer<int> sp = 10;时，
    // 会发生隐式类型转换，将int类型转换为SharedPointer<int>类型，
    // 这是不允许的，因为我们没有定义从int到SharedPointer<int>的转换。
    // 所以我们需要使用explicit关键字来防止这种隐式类型转换。
    // 这样之后只能这样调用：SharedPointer<int> sp(new int(10));
    // 或者SharedPointer<int> sp = SharedPointer<int>(new int(10));
    // 或者SharedPointer<int> sp = std::make_shared<int>(10);
    // 这是我们希望的调用方法
    // 但是，我们可以使用SharedPointer<int>
    // sp(10);来显式地构造一个SharedPointer<int>类型的对象。
    // 这样就可以避免隐式类型转换了。
    // 但是，我们也可以使用SharedPointer<int> sp = std::make_shared<int>(10);
    explicit SharedPointer(T *ptr, std::function<void(T *)> deleter = DebugDelete())
        : ptr_(ptr), refCounter_(new std::size_t(1)), deleter_(deleter)
    {}

    // 从shread_ptr转换为SharedPointer
    explicit SharedPointer(std::shared_ptr<T>     &&sp,
                           std::function<void(T *)> d = DebugDelete());

    // 拷贝构造函数
    SharedPointer(const SharedPointer &sp)
        : ptr_(sp.ptr_), refCounter_(sp.refCounter_), deleter_(sp.deleter_)
    {
        (*sp.refCounter_)++; // 增加引用
    }

    // 移动构造函数
    SharedPointer(SharedPointer &&sp) noexcept;

    // 拷贝运算符
    SharedPointer &operator=(const SharedPointer &rhs);

    // 移动运算符
    SharedPointer &operator=(SharedPointer &&rhs) noexcept;

    // 布尔类型重载
    operator bool() const { return ptr_ ? true : false; }

    // 解引用
    T &operator*() const { return *ptr_; }
    // 箭头运算符
    T *operator->() const { return &this->operator*(); }

    // 返回被引用的数量
    std::size_t useCount() const { return *refCounter_; }

    // get函数
    T *get() const { return ptr_; }

    // 当前引用是否是唯一的
    bool unique() const { return *refCounter_ == 1; }

    // 交换两个指针的内容
    void swap(SharedPointer &rhs) { ::swap(*this, rhs); }

    // 如果当前用户是资源唯一的使用者就释放这个资源
    void reset() noexcept { decrement_n_destroy(); }

    // 使ptr_指向新的指针位置，并且新资源引用+1
    void reset(T *p);

    // 重置到 p 指向的位置并将删除器更改为 d。
    void reset(T *p, std::function<void(T *)> d)
    {
        reset(p);
        deleter_ = d;
    }

    // 析构函数
    ~SharedPointer() { decrement_n_destroy(); }

private:
    // 指针指向的对象
    T *ptr_ = nullptr;

    // 引用该内容的数量
    std::size_t *refCounter_ = new std::size_t(0);

    // 指向删除器的指针
    // std::function<void(T *)> 是一个可调用对象，定义上的范围广与函数指针，
    // 可以指向任何类型的可调用对象，包括函数、函数对象、lambda表达式等。
    // 它可以存储任何可调用对象，并且可以像函数指针一样被调用。
    // 它的主要作用是实现多态性，即可以存储不同类型的可调用对象，
    // 并且可以像函数指针一样被调用。
    // 像我这里的删除器重载的()操作符，就是一个可调用对象，
    // 可以像函数指针一样被调用。
    std::function<void(T *)> deleter_{DebugDelete()};

    // 工具函数
    void decrement_n_destroy();
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const SharedPointer<T> &sp);

template<typename T>
inline void swap(SharedPointer<T> &lhs, SharedPointer<T> &rhs)
{
    using std::swap;
    swap(lhs.ptr_, rhs.ptr_);
    swap(lhs.refCounter_, rhs.refCounter_);
    swap(lhs.deleter_, rhs.deleter_);
}

template<typename T>
SharedPointer<T>::SharedPointer(std::shared_ptr<T> &&sp, std::function<void(T *)> d)
{
    if (sp.unique())
        *this = SharedPointer(new T(*sp), d);
    else
        throw std::runtime_error(
            "only unique and rvalue reference can transfer ownership");
}

template<typename T>
SharedPointer<T>::SharedPointer(SharedPointer &&sp) noexcept
    : ptr_(sp.ptr_), refCounter_(sp.refCounter_), deleter_(std::move(sp.deleter_))
{
    sp.ptr_ = nullptr;
    sp.refCounter_ = nullptr;
}

template<typename T>
SharedPointer<T> &SharedPointer<T>::operator=(const SharedPointer &rhs)
{
    (*rhs.refCounter_)++;

    // 释放当前元素的资源
    decrement_n_destroy();
    // 拷贝资源
    ptr_ = rhs.ptr_;
    refCounter_ = rhs.refCounter_;
    deleter_ = rhs.deleter_;

    return *this;
}

// 移动运算符
template<typename T>
SharedPointer<T> &SharedPointer<T>::operator=(SharedPointer &&rhs) noexcept
{
    decrement_n_destroy();

    ::swap(*this, rhs);

    std::cout << "shared_pointer::move=\n";

    return *this;
}

template<typename T>
void SharedPointer<T>::reset(T *ptr)
{
    if (ptr_ != ptr) {
        decrement_n_destroy();
        ptr_ = ptr;
        refCounter_ = new std::size_t(1);
    }
}

// 运算符重载
template<typename T>
inline std::ostream &operator<<(std::ostream &os, const SharedPointer<T> &sp)
{
    os << sp.get();
    return os;
}

// 辅助函数
template<typename T>
inline void SharedPointer<T>::decrement_n_destroy()
{
    if (ptr_) {
        if (--*refCounter_ == 0) {
            deleter_(ptr_);
            delete refCounter_;
        }
        ptr_ = nullptr;
        refCounter_ = nullptr;
    }
}