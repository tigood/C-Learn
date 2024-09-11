#ifndef _13_5_TEXT
#define _13_5_TEXT
#include <iostream>
#include <set>

class Folder;

// Message类
class Message{
    friend void swap(Message &, Message &);
    friend class Folder;

public:
    // folders被隐式的初始化为空集合
    explicit Message(const std::string &str = ""):
        contents(str) {}
    // 拷贝构造函数
    Message(const Message &);
    // 拷贝运算符重载
    Message &operator=(const Message &);
    // 析构函数
    ~Message();
    // 从给定的Folder目录中删除或者添加本消息
    void save(Folder &);
    void remove(Folder &);

private:
    std::string contents;  // 实际文本消息
    std::set<Folder *> folders;  // 包含本消息的文件夹集合
    // 在析构函数和拷贝构造函数和赋值拷贝运算符重载中用到的辅助函数
    // 将本消息添加到指定参数的Folder列表中
    void add_to_Folders(const Message &);
    // 从folders中删除本消息
    void remove_from_Folders();

    void addFolder(Folder *);
    void remFolder(Folder *);
};

void swap(Message &, Message &);

// Folder类
class Folder{
    friend void swap(Folder &, Folder &);
    friend class Message;

public:
    Folder() = default;                                       // 默认构造函数
    Folder(const Folder &other);                              // 拷贝构造函数
    // 赋值拷贝重载符
    Folder &operator=(const Folder &);
    // 析构函数
    ~Folder();
    
    // 调试方法
    void print_debug();

private:
    std::set<Message *> messages;  // 该文件夹包含的所有消息的集合

    // 辅助函数
    // 将该目录指针添加到指针目录的消息列表中
    void add_to_Message(const Folder &);
    // 从该目录的消息列表中将目录删除掉
    void remove_from_Message();

    void addMsg(Message *);
    void remMsg(Message *);
};

void swap(Folder &, Folder &);

#endif