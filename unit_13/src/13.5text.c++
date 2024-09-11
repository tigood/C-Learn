#include <iostream>
#include "../include/13.5text.hpp"

// Message类的实现
// 拷贝构造函数
Message::Message(const Message &other):
    contents(other.contents), folders(other.folders) {
        // 将该文件添加到other存在的文件夹中
        add_to_Folders(other);
}

void Message::save(Folder &f) {
    // 将该消息保存到指定的文件夹中
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f) {
    folders.erase(&f);
    f.remMsg(this);
}

// 辅助函数
void Message::add_to_Folders(const Message &m) {
    for (auto &item : m.folders) {
        item->addMsg(this);
    }
}

void Message::remove_from_Folders() {
    for (auto &f : folders) {
        f->remMsg(this);  // 从文件目录中删除该消息文件
    }
}

// 析构函数
Message::~Message() {
    remove_from_Folders();
}

// 重载运算符
Message &Message::operator=(const Message &other) {
    // 为了处理自赋值的情况，先将本身清空
    remove_from_Folders();
    // 然后再拷贝数据
    contents = other.contents;
    folders = other.folders;
    add_to_Folders(other); // 将本消息添加到他们指向的那些文件列表中
    return *this;
}

void swap(Message &m1, Message &m2) {
    using std::swap;
    // 由于不仅仅要交换他们两个的数据，他们在各自文件列表中存储的信息也需要交换
    // 所以首先将他们在各自文件列表中清除，再重新标注
    m1.remove_from_Folders();
    m2.remove_from_Folders();
    // 执行两个属性的数据交换
    swap(m1.contents, m2.contents);
    swap(m1.folders, m2.folders);
    // 重新在各自的文件列表中标注
    m1.add_to_Folders(m1);
    m2.add_to_Folders(m2);
}

void Message::addFolder(Folder *f) {
    folders.insert(f);
}

void Message::remFolder(Folder *f) {
    folders.erase(f);
}

// Folder类的实现

void Folder::addMsg(Message *m) {
    messages.insert(m);
}

void Folder::remMsg(Message *m) {
    messages.erase(m);
}

void Folder::add_to_Message(const Folder &f) {
    for (auto &item : f.messages) {
        item->addFolder(this);
    }
}

void Folder::remove_from_Message() {
    for (auto &item : messages) {
        item->remFolder(this);
    }
}

// 赋值构造函数
Folder::Folder(const Folder &other): messages(other.messages) {
    add_to_Message(other);
}

// 重载赋值符号
Folder &Folder::operator=(const Folder &other) {
    // 将自己从消息列表中清空
    remove_from_Message();
    messages = other.messages;
    add_to_Message(other);
    return *this;
}

// 析构函数
Folder::~Folder() {
    remove_from_Message();
}

void swap(Folder &f1, Folder &f2) {
    using std::swap;
    f1.remove_from_Message();
    f2.remove_from_Message();
    swap(f1.messages, f2.messages);
    f1.add_to_Message(f1);
    f2.add_to_Message(f2);
}

void Folder::print_debug() {
    for (const auto &item : messages) {
        std::cout << item->contents << std::endl;
    }
}