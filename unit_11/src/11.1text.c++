#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <utility>
#include <numeric>

void text_1() {
    std::map<std::string, int> word_count;
    std::string word;
    // 创建一个忽略的单词集合
    std::set<std::string> exculds({"and", "or", "is"});
    // 在对一个还未创建的关键字使用下标运算的时候，系统会创建一个该键值对，值为0
    while (std::cin >> word)
    {
        if (exculds.find(word) == exculds.end()) {
            word_count[word]++;
        }
    }
    // 打印结果
    for (const auto& item : word_count) {
        std::cout << "单词：" << item.first << " 出现次数：" << item.second << std::endl;
    }
}

// 添加家庭信息
void add_family_info(std::map<std::string, std::vector<std::string>>& family) {
    std::cout << "请输入你要添加的人员的家庭姓：" << std::endl;
    std::string first_name;
    std::cin >> first_name;
    std::cout << "请输入您要添加的人员的名称" << std::endl;
    std::string last_name;
    std::cin >> last_name;
    family[first_name].push_back(last_name);
    std::cout << "添加成功" << std::endl;
}

// 展示当前家庭信息
void show_family_info(std::map<std::string, std::vector<std::string>>& family) {
    int count = 0;
    for (const auto &item : family)
    {
        std::cout << ++count << ". ";
        std::cout << "姓氏为：" << item.first << std::endl;
        std::cout << "  ";
        for (const auto& name : item.second) {
            std::cout << name << " ";
        }
        std::cout << std::endl;
    }
}

int show_choose() {
    int user_choose;
    std::cout << "0.退出" << std::endl;
    std::cout << "1.添加信息" << std::endl;
    std::cout << "2.查看信息" << std::endl;
    std::cin >> user_choose;
    return user_choose;
}

void text_2() {
    std::map<std::string, std::vector<std::string>> family;
    while(true)
    {
        switch (show_choose())
        {
        case 0:
            return;
        case 1:
            add_family_info(family);
        case 2:
            show_family_info(family);
        default:
            break;
        }
    }
}

void text_3() {
    // 使用vector来保存不重复的单词
    std::vector<std::string> words;
    std::string word;
    while (std::cin >> word)
    {
        if (std::find(words.cbegin(), words.cend(), word) == words.cend()) {
            words.push_back(word);
        }
    }
    // 展示最终的容器值
    for (auto& item : words) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void text_4() {
    // 一个map，其中键是一个word，而值是一个list里面装着word出现的行号
    std::map<std::string, std::list<int>> myMap;
    int line_count = 0;
    std::string line;
    while (std::getline(std::cin, line))
    {
        line_count++;
        // 创建一个字符串流
        std::string word;
        std::istringstream stristream(line);
        while (stristream >> word)
        {
            // 这说明该单词已经出现过一次了
            if (myMap.find(word) != myMap.end()) {
                // 在该单词中的行号中，查处该行是不是已经记录过一次了
                if (std::find(myMap[word].cbegin(), myMap[word].cend(), line_count) == myMap[word].cend()) {
                    myMap[word].push_back(line_count);
                }
            } else {
                myMap[word].push_back(line_count);
            }
        }
    }
    // 输出结果
    std::cout << "记录如下：" << std::endl;
    for (const auto& item : myMap) {
        std::cout << "单词：" << item.first << " 行号：";
        for (const auto& line_count : item.second) {
            std::cout << line_count << " ";
        }
        std::cout << std::endl;
    }
}

void text_5() {
    std::pair<std::string, std::string> myPair{"hello", "world"};

}

void text_6() {
    std::vector<std::string> words{"hello", "world", "ni", "hao"};
    std::vector<int> nums{1, 2, 3, 4};
    // 创建一个包含pair的容器
    std::vector<std::pair<std::string, int>> myPair;
    // 预先分配空间  resever 预定的意思
    // resever 预定  reverse 反转
    myPair.reserve(words.size());
    for (int i = 0; i < words.size(); i++)
    {
        myPair.emplace_back(words[i], nums[i]);
    }
    // 遍历展示
    for (const auto& item : myPair) {
        std::cout << "first: " << item.first << " second:" << item.second << std::endl;
    }
}

void text_7() {
    std::vector<std::string> words{"hello", "world", "ni", "hao"};
    std::vector<int> nums{1, 2, 3, 4};
    // 创建一个包含pair的容器
    std::vector<std::pair<std::string, int>> myPair;
    for (int i = 0; i < words.size(); i++) {
        // 创建一个pair;
        std::pair<std::string, int> temp{words[i], nums[i]};
        // std::pair<std::string, int> temp = std::make_pair(words[i], nums[i]);
        // std::pair<std::string, int> temp(words[i], nums[i]);
        // std::pair<std::string, int> temp = {words[i], nums[i]};  
        myPair.push_back(temp);
    }
    // 展示数据
    for (const auto& item : myPair) {
        std::cout << "first: " << item.first << " second:" << item.second << std::endl;
    }
}

void text_8() {
    // set的key_type和value_type是一样的，都是指的键值
    // map的key_type是一个键值，value_type是一个pair对象<const key_type, mapped_type>
    // 注意这个key_type是const不可变的，而这个mapped_type是可以改变的
    // 当解引用一个关联对象的迭代器的时候的时候，得到的是一个value_type对象
    std::map<int, int> imap{{1, 2}, {2, 3}};
    // 展示数据
    auto map_it = imap.begin();
    while (map_it != imap.end())
    {
        std::cout << "first： " << map_it->first << " second: " << map_it->second << std::endl;
        map_it->second += 10;
        map_it++;
    }
    // 再次展示数据
    for (const auto& item : imap) {
        std::cout << "first: " << item.first << " seconde: " << item.second << std::endl;
    }

}

void text_9() {
    // 使用一种更繁琐的方式来实现计算一句话中单词出现的次数
    std::map<std::string, int> word_count;
    std::string word;
    while (std::cin >> word)
    {
        // 将一个pair插入map，如果该单词已经存在，那么他什么也不会做，因为这里是map不允许出现重复元素
        // 而如果这里是multimap效果就不一样了
        // multimap总是可以插入一个元素，返回值是一个指向新元素的迭代器，而不是一个pair对象
        auto result = word_count.insert({word, 1});
        // 通过返回值判断是否插入成功
        // 如果没有成功，说明已经存在，将次数叠加一次
        if (!result.second) {
            // result是一个pair对象，第一个是一个指向map的迭代器，第二个是一个布尔值
            // 对map迭代器解引用得到的也是一个pair对象，first是key_type,second是mapped_type
            result.first->second++;
        }
    }
    // 检查是否是因为eof结束的，如果是清除eof标记
    if (std::cin.eof()) {
        std::cin.clear(); // 清除eof标记
        std::cin.ignore(); // 清空输入流
    }

    // 输出结果
    std::cout << "删除元素之前" << std::endl;
    for (const auto &item : word_count)
    {
        std::cout << "单词：" << item.first << " 次数：" << item.second << std::endl;
    }
    // 删除元素
    std::cout << "删除hei单词" << std::endl;
    std::string remove_word{"hei"};
    // 如果传入的是一个迭代器，返回值为一个指向删除元素的下一个元素
    // 如果传入的是一对迭代器，返回后面的迭代器(b, e)返回e
    // 关联容器还有一个专属的操作是传入一个key，返回值为实际删除的值的数量
    // 所以如果是一个普通的set或者map，返回值为0或者1 删除成功或者删除失败
    // 但是如果是multiset或者multimap则返回0或者一个int，因为可能有多个值
    if (word_count.erase(remove_word))
    {
        std::cout << "删除成功" << std::endl;
    }
    else
    {
        std::cout << "删除失败，该键值不存在" << std::endl;
    }
    // 再次展示数据
    for (const auto& item : word_count) {
        std::cout << "单词：" << item.first << " 次数：" << item.second << std::endl;
    }
}

void text_10() {
    std::map<std::string, int> myMap{{"one", 1}, {"two", 2}, {"three", 3}};
    // 通过下标获取第一个值
    std::cout << "one：" << myMap["one"] << std::endl;
    // 通过at获取第二个值
    std::cout << "two：" << myMap.at("two") << std::endl;
}

void text_11() {
    std::map<std::string, int> myMap{{"one", 1}, {"two", 2}, {"three", 3}};
    std::map<std::string, int>::iterator it = myMap.find("one");
    std::cout << it->second << std::endl;
}

void text_12() {
    std::multimap<std::string, std::vector<std::string>> books = {
        {"tigood", {"python开发实战", "fastapi开发"}},
        {"hello", {"word的编写", "all is well"}}};
    // 展示数据
    for (const auto& item : books) {
        std::cout << "作者: " << item.first << " 书籍：";
        for (const auto& book : item.second) {
            std::cout << book << " ";
        }
        std::cout << std::endl;
    }
    // 输入要删除的键值
    std::string remove_word;
    std::cout << "请输入你要删除的图书的作者名字:" << std::endl;
    std::getline(std::cin, remove_word);
    if (books.find(remove_word) != books.end()) {
        books.erase(remove_word);
    } else {
        std::cout << "没有找到相关数据，删除失败" << std::endl;
        return;
    }
    // 删除成功之后再次展示
    std::cout << "删除之后的效果为：" << std::endl;
        for (const auto& item : books) {
        std::cout << "作者: " << item.first << " 书籍：";
        for (const auto& book : item.second) {
            std::cout << book << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    // text_1();
    // text_2();
    // text_3();
    // text_4();
    // text_6();
    // text_8();
    // text_9();
    // text_10();
    // text_11();
    text_12();

    return 0;
}