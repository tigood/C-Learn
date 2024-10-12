#ifndef _STRING
#define _STRING
#include <memory>

// String类
class String{
public:
    friend std::ostream &operator<<(std::ostream &, const String &);
    friend std::istream &operator>>(std::istream &, String &);
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    String() : String("") {}; // 默认构造函数
    String(const char *);  // 有参构造函数
    String(const String &); // 拷贝构造函数
    String(String &&) noexcept;  // 移动构造函数
    String &operator=(String &&) noexcept; // 移动运算符重载
    String &operator=(const String &); // 拷贝符号重载
    String &operator+=(const String &);
    // 输出运算符
    ~String(); // 析构函数

private:
    // 辅助函数
    std::pair<char *, char *> alloc_n_copy(const char *, const char *);
    void range_initalizer(const char *, const char *);
    void free();  // 释放空间
    static std::allocator<char> alloc;
    char *elements_;  // 指向首字符元素的指针
    char *end_;  // 指向最后一个实际元素后面的指针
};

#endif