#include "../include/query_word.hpp"
#include <string>
#include <iostream>
#include <fstream>

int main() {
    std::string file_name;
    std::cout << "请输入您要读取的文件的名字：" << std::endl;
    std::cin >> file_name;
    // 创建一个文件读取流
    std::ifstream in_file{file_name};
    // 创建一个查询对象
    TextQuery tq = TextQuery{in_file};
    std::string target_word;
    while (true)
    {
        std::cout << "请输入您要查询的单词，输入q退出：" << std::endl;
        if (!(std::cin >> target_word) || target_word == "q") break;
        print(std::cout, tq.query(target_word));
        std::cout << std::endl;
    }
}