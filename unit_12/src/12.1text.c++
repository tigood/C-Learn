#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <new>
#include <fstream>

class StrBlobPtr;

class StrBlob {
public:
    friend class StrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();  // 默认构造函数
    StrBlob(std::initializer_list<std::string> il);  // 传入一个构造列表的构造函数
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // 添加和删除元素
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // 元素访问
    std::string &front();
    std::string &back();
    // 对front()和back()的重载
    const std::string &front() const;
    const std::string &back() const;
    // 返回首尾指针
    StrBlobPtr begin();
    StrBlobPtr end();

private:
    std::shared_ptr<std::vector<std::string>> data;
    // 如果data[i]不可法，抛出一个异常
    void check(size_type i, const std::string &msg) const;
};

// 核查指针类
class StrBlobPtr {
public:
    StrBlobPtr() : curr(0) {}
    StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
    std::string &deref() const;
    StrBlobPtr &incr(); // 前缀递增
    friend class StrBlob;
        // 友元函数声明
    friend bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs);
    friend bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs);

private:
    // 若检查成功,check返回一个指向vector的shared_ptr
    std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string &) const;
    // 保存一个weak_ptr，意味着底层vector可能被销毁
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

void
text_1()
{
    std::shared_ptr<std::string> ptr_str;
    std::string str_1{"hello, world"};
    if (!ptr_str)
    {
        std::cout << "该智能指针没有指向对象" << std::endl;
    }
    ptr_str = std::make_shared<std::string>();
    *ptr_str = str_1;
    if (!ptr_str) {
        std::cout << "该智能指针没有指向对象" << std::endl;
    } else {
        std::cout << "指针指向的对象为：" << *ptr_str << std::endl;
    }
}

void text_2() {
    StrBlob b1;
    {
        StrBlob b2({"hello", "world"});
        b1 = b2;
        b2.push_back("世界");
        std::cout << "b2.size() = " << b2.size() << std::endl;
    }
    std::cout << "b1.size() = " << b1.size() << std::endl;
}

// 练习12.6
std::vector<int>* func_1() {
    std::vector<int> *p_ivect = new std::vector<int>();
    return p_ivect;
}

std::vector<int>* func_2(std::vector<int> *p_ivect) {
    int num;
    while (std::cin >> num) {
        p_ivect->push_back(num);
    }
    return p_ivect;
}

void func_3(std::vector<int> *p_ivect) {
    for (auto &item : *p_ivect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    delete p_ivect;
}

// 12.7
std::shared_ptr<std::vector<int>> shared_func_1() {
    auto ptr_ivect = std::make_shared<std::vector<int>>();
    return ptr_ivect;
}

std::shared_ptr<std::vector<int>> shared_func_2(std::shared_ptr<std::vector<int>> ptr_ivect) {
    int num;
    while (std::cin >> num) {
        ptr_ivect->push_back(num);
    }
    return ptr_ivect;
}

void shared_func_3(std::shared_ptr<std::vector<int>> ptr_ivect) {
    for (auto &item : *ptr_ivect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// 12.1.4
// struct destination;
// struct connection {
//     int id;
// };
// connection connect(destination *);
// void disconnect(connection);

// void f(destination &d) {
//     connection c = connect(&d);
//     // 使用连接
//     // 如果我们在f退出前忘记调用disconnect，就无法关闭c了
// }

// // 使用智能指针

// // 定义自己的删除器
// void end_connection(connection *p) {
//     disconnect(*p);
// }

// void use_shared_ptr(destination &d) {
//     connection c = connect(&d);
//     // 使用智能指针
//     // std::shared_ptr<connection> p(&c, end_connection);

//     // 使用lambda函数
//     std::shared_ptr<connection> p(&c, [](connection *conn)
//                                   { disconnect(*conn); });
// }

//12.20
void text_3() {
    std::string file_name;
    // 创建两个类
    StrBlob sblob = StrBlob();
    std::cout << "请你输入你要读取的文件的名称：" << std::endl;
    std::getline(std::cin, file_name);
    // 创建一个该文件的读取流
    std::ifstream read_file(file_name);
    // 逐行读取文件
    std::string line;
    while (std::getline(read_file, line)) {
        sblob.push_back(line);
    }
    // 再通过StrBlobPtr将字符串打印出来
    auto end = sblob.end();
    StrBlobPtr ptr = sblob.begin();
    while (ptr != end) {
        std::cout << ptr.deref() << std::endl;
        ptr.incr();
    }
}

int main() {
    // text_1();
    // text_2();
    // func_3(func_2(func_1()));
    // shared_func_3(shared_func_2(shared_func_1()));
    text_3();

    return 0;
}

// StrBlob对象
StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

// 检测是否超出了数据长度
void StrBlob::check(size_type i, const std::string &msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

// 返回前面的首个元素
std::string& StrBlob::front() {
    // 如果vector为空，则抛出异常
    check(0, "试图对一个空对象执行front()");
    return data->front();
}

// 返回后面最后一个元素
std::string& StrBlob::back() {
    // 如果vector为空，抛出异常
    check(0, "试图对一个空对象执行back()");
    return data->back();
}

const std::string& StrBlob::front() const {
    check(0, "试图对一个空对象执行front()");
    return data->front();
}

const std::string& StrBlob::back() const {
    check(0, "试图对一个空对象执行back()");
    return data->back();
}

// 删除最后一个元素
void StrBlob::pop_back() {
    check(0, "试图对一个空对象执行pop_back()");
    data->pop_back();
}

StrBlobPtr
StrBlob::begin() {
    return StrBlobPtr(*this);
}

StrBlobPtr
StrBlob::end() {
    return StrBlobPtr(*this, data->size());
}

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg) const {
    auto ret = wptr.lock();
    // 检查是否正确的返回了
    if (!ret) {
        throw std::runtime_error("没有绑定的StrBolb指针");
    }
    if (i >= ret->size()) {
        throw std::out_of_range(msg);
    }

    return ret;  // 否则，返回指向vector的shared_ptr
}

std::string&
StrBlobPtr::deref() const {
    auto p = check(curr, "检测失败");
    return (*p)[curr];
}

StrBlobPtr&
StrBlobPtr::incr() {
    // 如果curr已经指向了绑定容器的末尾，就不能再递增他了
    check(curr, "递增curr失败");
    curr++;
    return *this;
}

bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    if (!lhs.wptr.expired() && !rhs.wptr.expired()) {
        return (lhs.wptr.lock() == rhs.wptr.lock()) && (lhs.curr == rhs.curr);
    } else {
        return false;
    }
}

bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
    return !(lhs == rhs);
}

