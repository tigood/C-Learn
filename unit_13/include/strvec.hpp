#ifndef _STR_VEC
#define _STR_VEC
#include <string>
#include <memory>
#include <initializer_list>

class StrVec{
public:
    StrVec():  // 默认构造函数
        elements_(nullptr), first_free_(nullptr), cap_(nullptr) {}
    StrVec(const StrVec &);  // 拷贝构造函数
    // 不抛出异常的移动构造函数和移动赋值运算都应该被声明为noexcept，表示这个函数不会抛出错误
    StrVec(StrVec &&s) noexcept;  // 移动构造函数
    StrVec &operator=(StrVec &&s) noexcept;  // 移动赋值运算符
    StrVec(std::initializer_list<std::string>); // 初始化列表构造对象
    StrVec &operator=(const StrVec &); // 拷贝运算符重载
    ~StrVec();  // 析构函数
    // 公开方法
    void push_back(const std::string&);  // 拷贝元素
    size_t size() const { return first_free_ - elements_; }  // 返回存储元素的数量
    size_t capacity() const { return cap_ - elements_; }  // 返回容器当前的最大容量
    std::string *begin() const { return elements_; }  // 返回指向首元素的指针
    std::string *end() const { return first_free_; }  // 返回最后一个实际元素之后的位置

private:
    // 将分配器定义成一个静态成员
    static std::allocator<std::string> alloc;  // 构造器，用来分配内存
    // 辅助函数
    // 被拷贝构造函数，拷贝运算符重载和析构函数使用
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string *);
    void range_initialize(const std::string *, const std::string *);
    void free();        // 销毁对象并且释放内存
    void reallocate();  // 重新分配一个更大的内存，并将原来的元素们拷贝进去
    // 被添加元素函数使用
    void chk_n_alloc() {
        // 保证StrVec至少有容纳一个新元素的空间，如果没有就重新分配内存
        if (size() == capacity())
            reallocate();
    }
    // 属性变量
    std::string *elements_;   // 指向数组首元素的指针
    std::string *first_free_;  // 指向最后一个实际元素之后的位置
    std::string *cap_;  // 指向分配的内存的末尾之后的位置
};

#endif