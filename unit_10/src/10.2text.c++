#include <iostream>
#include <numeric>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

void text_1()
{
    std::vector<int> ivect({1, 2, 3, 4, 5});
    // 这个accumulate算法的第三个参数决定了运算要使用那种类型的加法，和返回值的类型
    int sum = std::accumulate(ivect.cbegin(), ivect.cend(), 0);
    std::cout << "数组如下：" << std::endl;
    for (auto& item : ivect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    std::cout << "和为:" << sum << std::endl;
}

void text_2()
{
    std::vector<const char *> cvect({"hello", "world", "hi"});
    std::vector<const char *> cvect_2({"hello", "world", "nihao"});
    bool flag = std::equal(cvect.cbegin(), cvect.cend(), cvect_2.begin());
    if (flag) {
        std::cout << "这两个序列相等！" << std::endl;
    }
    else {
        std::cout << "这两个序列不相等" << std::endl;
    }
}

void text_3()
{
    std::vector<int> ivect;  // 声明了一个空容器
    auto it = std::back_inserter(ivect);  // 为该空容器指定了一个插入迭代器
    *it = 10;  // 使用该插入迭代器
    *it = 20;
    for (auto &item : ivect)
    {
        std::cout << item << " ";  // 查看容器的元素
    }
    std::cout << std::endl;
}

void text_4()
{
    std::vector<int> ivect;
    // 在一个空容器中通过fill_n添加10个1
    std::fill_n(std::back_inserter(ivect), 10, 1);
    for (auto& item : ivect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    // 将这个容器范围内的数值改为2
    std::fill(ivect.begin(), ivect.end(), 2);
    for (auto& item : ivect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    // 将这个容器范围内所有的数值改为0
    std::fill_n(ivect.begin(), ivect.size(), 0);
    for (auto& item : ivect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void text_5()
{
    std::vector<int> ivect;
    std::list<int> ilist;
    int i;
    while (std::cin >> i)
    {
        ilist.push_back(i);
    }
    // 将ilist的值拷贝到vector中
    auto it = std::back_inserter(ivect);
    std::copy(ilist.cbegin(), ilist.cend(), it);
    std::cout << "ivect容器内容如下：" << std::endl;
    for (auto &item : ivect)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    // 剩余的写容器方法
    // replace(c.begin(), c.end(), 0, 42); 查找迭代器范围内的所有0,并替换为42
    // replace_copy(c.begin(), c.end(), target_iter, 0, 42)  效果同上，不过把调整的结果保存到了target_iter所指向的容器中
}

void text_6()
{
    std::vector<std::string> svect;
    std::string word;
    while (std::cin >> word)
    {
        svect.push_back(word);
    }
    std::cout << "原容器中的值为：" << std::endl;
    for (const auto& item : svect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    // 对容器进行排序
    std::sort(svect.begin(), svect.end());
    // 将容器中的重复项筛选
    auto end_unique = std::unique(svect.begin(), svect.end());
    // 容器大小没有改变，而是将没有重复的部分提到了end_unique之前，剩余部分内容是不可知的
    svect.erase(end_unique, svect.end());
    std::cout << "排序之后的容器内容为:" << std::endl;
    for (const auto& item : svect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// 谓词
bool isShorter(const std::string& s1, const std::string& s2)
{
    return s1.size() > s2.size();
}

void text_7()
{
    std::vector<std::string> svect({"ni", "hello", "hao", "x"});
    // 输入源数据
    for (auto& item : svect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    // 对数据进行排序
    std::sort(svect.begin(), svect.end(), isShorter);
    // 输入排完序的数据
    for (auto& item : svect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

int main()
{
    // text_1();
    // text_2();
    // text_3();
    // text_4();
    // text_5();
    // text_6();
    text_7();

    return 0;
}
