#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>

bool isShorter(const std::string s1, const std::string s2)
{
    return s1.size() < s2.size();
}

bool isShortFiveSize(const std::string s1)
{
    return s1.size() < 5;
}

void text_1()
{
    std::vector<std::string> svect({"hello world", "hi", "shijienihao", "hei"});
    std::cout << "原数组为：" << std::endl;
    for (const auto& item : svect) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    // 对数组进行分割
    auto it = std::partition(svect.begin(), svect.end(), isShortFiveSize);
    std::cout << "后半部分为：" << std::endl;
    // 输出数组的后半部分，即字符串长度大于5的那一部分
    while (it != svect.end())
    {
        std::cout << *it << std::endl;
        it++;
    }
}

void lambda_text() {
    auto f = [] { return 43; };
    auto d = []() -> int { return 100; };
    auto h = [](int a, int b) -> int
    {
        return a + b;
    };
    std::cout << f() << std::endl;
    std::cout << d() << std::endl;
    std::cout << h(1, 2) << std::endl;
}

void for_each_text() {
    std::vector<std::string> svect({"hello", "world", "nihao"});
    std::for_each(svect.begin(), svect.end(),
                  [](std::string &s) { std::cout << s << std::endl; });
}

void text_2() {
    int func_int = 10;
    auto f = [func_int](int a) { return func_int + a; };
    std::cout << f(1) << std::endl;
}

void biggies(std::vector<std::string>& svect, std::vector<std::string>::size_type sz) {
    // 将传入的容器按字典序排序并去除重复的单词
    std::sort(svect.begin(), svect.end());
    // 筛选出来重复的单词
    auto it = std::unique(svect.begin(), svect.end());
    // 手动擦除多余的重复元素
    svect.erase(it, svect.end());
    // 按长度排序，长度相同的维持字典序
    std::stable_sort(svect.begin(), svect.end(),
                     [](const std::string &s1, const std::string &s2)
                     { return s1.size() < s2.size(); });
    // 获取一个迭代器，指向第一个大于指定长度的单词
    auto wc = std::find_if(svect.begin(), svect.end(),
                           [sz](const std::string &s)
                           { return s.size() > sz; });
    // 计算大于指定长度的单词
    auto count = std::distance(wc, svect.end());
    // 输出信息
    std::cout << "一共有" << count << "个大于" << sz << "长度的单词" << std::endl;
    // 通过for_each来输出这些单词
    std::for_each(wc, svect.end(), [](const std::string &s)
                  { std::cout << s << std::endl; });
}

void text_3() {
    std::vector<std::string> words({"world", "hi", "ni", "hello", "world"});
    biggies(words, 3);
}

void partition_biggies(std::vector<std::string>& svect, std::vector<std::string>::size_type sz) {
    // 将传入的容器按字典序排序并去除重复的单词
    std::sort(svect.begin(), svect.end());
    // 筛选出来重复的单词
    auto it = std::unique(svect.begin(), svect.end());
    // 手动擦除多余的重复元素
    svect.erase(it, svect.end());
    // 按长度排序，长度相同的维持字典序
    std::stable_sort(svect.begin(), svect.end(),
                     [](const std::string &s1, const std::string &s2)
                     { return s1.size() < s2.size(); });
    // 获取一个迭代器，指向第一个大于指定长度的单词
    // partition算法将后面谓词返回为true的部分放到前半部分，而false的放到后半部分，返回第一个为false的元素的迭代器
    auto wc = std::partition(svect.begin(), svect.end(),
                             [sz](const std::string &s1)
                             { return s1.size() < sz; });
    // 计算大于指定长度的单词
    auto count = std::distance(wc, svect.end());
    // 输出信息
    std::cout << "一共有" << count << "个大于" << sz << "长度的单词" << std::endl;
    // 通过for_each来输出这些单词
    std::for_each(wc, svect.end(), [](const std::string &s)
                  { std::cout << s << std::endl; });
}

void text_4() {
    std::vector<std::string> words({"hello", "hello", "world", "hi", "ni"});
    partition_biggies(words, 3);
}

void text_5() {
    std::vector<int> ivect({1, 2, 3, -4, -5});
    std::vector<int> result(ivect.size());
    std::transform(ivect.begin(), ivect.end(), result.begin(),
                   [](int i) -> int
                   {if (i > 0) return i; else return -i; });
    for (auto& item : result) {
        std::cout << item << std::endl;
    }
}

void text_6() {
    std::vector<std::string> words({"hello", "ni", "hao", "hello", "world"});
    // 将列表按字典序排序
    std::sort(words.begin(), words.end());
    // 去除重复的单词
    auto it = std::unique(words.begin(), words.end());
    words.erase(it, words.end());
    // 计算剩下的单词中大于3字符的单词数量
    auto count = std::count_if(words.begin(), words.end(), [](const std::string &s1)
                               { return s1.size() > 3; });
    std::cout << "一共有" << count << "个单词的长度大于3" << std::endl;
}

void text_7() {
    int a = 5;
    while ([&a]() -> bool
           {
               if (a == 0)
                   return false;
               else {
                   a--;
                   return true;
               }
           }()) {
        std::cout << "a = " << a << std::endl;
    }
    std::cout << "程序结束" << std::endl;
}

int main()
{
    // text_1();
    //lambda_text();
    // for_each_text();
    // text_2();
    // text_3();
    // text_4();
    // text_5();
    // text_6();
    text_7();
    return 0;
}
