#include <iostream>
#include <string>
#include <vector>

void text_1()
{
    std::vector<char> cvect = {'h', 'e', 'l', 'l', 'o', '\0'};
    std::string str_1(cvect.begin(), cvect.end());
    std::cout << str_1 << std::endl;
}

void text_2()
{
    // 每次插入一个字符，插入到一个字符串中，并且至少要插入100个字符，提升性能
    // 创建一个空字符串
    std::string str_1;
    // 为这个字符串提前手动分配好空间
    str_1.reserve(100);
    // 逐一添加字符串
    for (int i = 0; i < 100; i++)
    {
        str_1.push_back('a' + (i % 26));
    }
    std::cout << str_1 << std::endl;
}

void text_3()
{
    // append方法
    std::string str_1 = "hello", str_2 = str_1;
    // 通过append方法来扩充字符串
    str_1.append(" world");
    // string的插入操作，第一个参数可以是一个迭代器，也可以是一个下标
    // 迭代器版本返回指向第一个插入元素的迭代器，下标版本返回值为一个指向字符串的引用
    str_2.insert(str_2.size(), " world");
    std::cout << "str_1 : " << str_1 << std::endl;
    std::cout << "str_2 : " << str_2 << std::endl;
    // erase(pos, len) 从指定下标开始删除len长度的字符，返回值为一个指向该字符串的引用
    str_1.erase(0, 4);
    std::cout << "str_1 : " << str_1 << std::endl;
    // replace(range, args)
    // range可以是一对迭代器，也可以是一对下标。args是要插入的元素
    str_1.replace(3, 4, "tigood");
    std::cout << "str_1 : " << str_1 << std::endl;
}

void text_4()
{
    // 查找元素
    std::string str_1 = "hello world";
    auto result_1 = str_1.find('l');
    std::cout << "l 第一次出现的下标：" << result_1 << std::endl;
    auto result_2 = str_1.rfind('l');
    std::cout << "l 第一次出现的下标：" << result_2 << std::endl;
    auto result_3 = str_1.find_first_of({'o', 'd'});
    std::cout << "o和d 其中最先出现的一个的下标是：" << result_3 << std::endl;
    // find_last_of 与上面这个作用相反
    // find_last_not_of
    // find_first_not_of
    int a = 1;
    std::string str_3 = std::to_string(a);
}

void text_5()
{
    std::vector<std::string> svect = {"12", "23", "10"};
    int sum = 0;
    for (auto& item : svect)
    {
        sum += std::stoi(item);
    }
    std::cout << "sum = " << sum << std::endl;
}

int main()
{
    // text_1();
    // text_2();
    // text_3();
    text_5();
    return 0;
}