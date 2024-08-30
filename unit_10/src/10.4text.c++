#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <numeric>

void text_1() {
    std::vector<std::string> words({"hello", "world", "ni", "hello", "ni"});
    std::vector<std::string> result;
    // 获得result的一个插入迭代器
    auto binsert_it = std::back_inserter(result);
    // 将容器按字典序排序
    std::sort(words.begin(), words.end());
    // 将不重复的单词放到result中
    std::unique_copy(words.begin(), words.end(), binsert_it);
    // 分别查看两个容器
    std::cout << "words容器中：" << std::endl;
    for (auto &item : words) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    std::cout << "result容器中：" << std::endl;
    for (auto& item : result) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void show_item (std::list<int>& ilist) {
    for (auto& item : ilist) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void text_2() {
    std::vector<int> ivect({1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::list<int> result_1, result_2, result_3;
    // 分别使用三个插入迭代器
    auto finsert_it = std::front_inserter(result_1);
    auto binsert_it = std::back_inserter(result_2);
    auto insert_it = std::inserter(result_3, result_3.begin());
    for (auto& item : ivect) {
        *finsert_it = item;
        *binsert_it = item;
        *insert_it = item;
    }
    std::cout << "result_1如下：" << std::endl;
    show_item(result_1);
    std::cout << "result_2如下：" << std::endl;
    show_item(result_2);
    std::cout << "result_3如下：" << std::endl;
    show_item(result_3);
}

void text_3() {
    std::vector<int> ivect;
    std::istream_iterator<int> in_iter(std::cin); // 从cin读取整数
    std::istream_iterator<int> eof;  // istream尾后迭代器
    while (in_iter != eof) {
        ivect.push_back(*in_iter++);
    }
    for (auto& item : ivect) {
        std::cout << item << std::endl;
    }
}

void text_4() {
    std::istream_iterator<int> in_iter(std::cin), eof;
    std::vector<int> ivect(in_iter, eof);
    for (auto& item : ivect) {
        std::cout << item << std::endl;
    }
}

void text_5() {
    // 使用io迭代器来使用加法算法
    std::istream_iterator<int> in_iter(std::cin), eof;
    std::cout << std::accumulate(in_iter, eof, 0) << std::endl;
}

void text_6() {
    // 使用输出迭代器
    std::ostream_iterator<std::string> out_iter(std::cout, " ");
    std::vector<std::string> words({"hello", "world", "ni", "hao"});
    for (auto& item : words) {
        // 这里的*和++其实没有实际作用，删除没有影响，但是为了和其他迭代器一致，就这样用了
        *out_iter++ = item;
    }
    std::cout << std::endl;
    std::cout << "通过copy算法打印数据" << std::endl;
    std::copy(words.begin(), words.end(), out_iter);
    std::cout << std::endl;
}

void text_7() {
    // 从一个文件中读取数据存储到一个容器中
    std::vector<std::string> words;
    // 获取一个文件的迭代器
    std::ifstream in("../src/text.txt"); // 创建读取文件的流
    std::istream_iterator<std::string> str_iter(in), eof; // 为该流创建一个读取迭代器
    // 为容器创建一个插入迭代器
    auto binsert_it = std::back_inserter(words);
    // 通过copy算法将文件流中的数据写到容器中
    std::copy(str_iter, eof, binsert_it);
    // 展示words容器的数据
    // 创建一个容器的输出迭代器
    std::cout << "容器结果如下：" << std::endl;
    std::ostream_iterator<std::string> out_iter(std::cout, " ");
    std::copy(words.begin(), words.end(), out_iter);
    std::cout << std::endl;
}

void text_8() {
    // 通过流迭代器 copy sort算法读取一系列数存储到容器中并排序再输出
    std::vector<int> nums;
    // 创建一个容器的插入迭代器
    auto binsert_it = std::back_inserter(nums);
    // 创建标准输入流迭代器
    std::istream_iterator<int> in_iter(std::cin), eof;
    std::copy(in_iter, eof, binsert_it);
    // 或者通过
    // while (in_iter != eof) {
    //     nums.push_back(*in_iter++);
    // }
    std::sort(nums.begin(), nums.end());
    // 将容器中的数据输出
    std::ostream_iterator<int> out_iter(std::cout, " ");
    std::copy(nums.begin(), nums.end(), out_iter);
    // 如果要打印不重复的数据
    // std::unique_copy(nums.begin(), nums.end(), out_iter);
    std::cout << std::endl;
}

void text_9(std::string in_file, std::string out_file1, std::string out_file2) {
    // 输入文件中是int，从中读取数据，将奇数输出到第一个文件，用空格分割，偶数输出到第二个文件，用\n分割
    // 创建读文件流
    std::ifstream in(in_file);
    std::istream_iterator<int> in_iter(in), eof;
    // 创建一个容器
    std::vector<int> nums;
    // 为容器创建一个插入迭代器
    auto binsert_it = std::back_inserter(nums);
    std::copy(in_iter, eof, binsert_it);
    // 为两个输出文件分别创建两个输出流
    std::ofstream out_1(out_file1), out_2(out_file2);
    std::ostream_iterator<int> out_iter_1(out_1, " "), out_iter_2(out_2, "\n");
    for (auto& item : nums) {
        if (item % 2 != 0) {
            *out_iter_1++ = item;
        } else {
            *out_iter_2++ = item;
        }
    }
}

int main() {
    // text_1();
    // text_2();
    // text_3();
    // text_4();
    // text_5();
    // text_6();
    // text_7();
    // text_8();
    text_9("../src/nums.txt", "../src/jishu.txt", "../src/oushu.txt");

    return 0;
}