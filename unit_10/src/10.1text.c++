#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

void text_1()
{
    std::vector<int> ivect({1, 2, 3, 4, 5, 1, 2, 3});
    int user_input;
    std::cout << "请输入一个指定数字：" << std::endl;
    std::cin >> user_input;
    // count算法，接受一对迭代器和一个指定值，将返回这个值在这个范围内出现的次数
    auto result = std::count(ivect.cbegin(), ivect.cend(), user_input);
    std::cout << "有" << result << "个元素等于给定值" << std::endl;
}

void text_2()
{
    std::list<std::string> slist({"hi", "hi", "hello"});
    std::string user_input;
    std::cout << "请输入一个字符串我们将查看他出现的次数" << std::endl;
    std::cin >> user_input;
    auto result = std::count(slist.cbegin(), slist.cend(), user_input);
    std::cout << "有" << result << "个指定值" << std::endl;
}

int main()
{
    // text_1();
    text_2();
    return 0;
}
