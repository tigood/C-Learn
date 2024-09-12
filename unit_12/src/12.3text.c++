#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    using line_no = std::vector<std::string>::size_type;
    std::string in_file_name;
    std::cout << "请输入您要读取的文件的名称：" << std::endl;
    std::getline(std::cin, in_file_name);
    // 根据这个文件创建一个文件流
    std::ifstream in_file(in_file_name);
    // 创建一个vector容器来根据行存储整个文件，map存储每个单词出现的行号
    std::vector<std::string> file_content;
    std::map<std::string, std::set<line_no>> word_info;
    // 存储单词出现的次数
    std::map<std::string, int> word_count;
    std::string line;
    line_no current_line_no = 0;
    while (std::getline(in_file, line))
    {
        current_line_no++;  // 递增行号
        // 将这一行存储到vector中
        file_content.push_back(line);
        // 创建一个文本流
        std::istringstream in_word(line);
        std::string temp_word;
        while (in_word >> temp_word)
        {
            word_info[temp_word].insert(current_line_no);
            word_count[temp_word]++;
        }
    }
    // 存储完毕，输出文件内容
    std::cout << "文件内容为：" << std::endl;
    for (auto &item : file_content) {
        std::cout << item << std::endl;
    }
    std::cout << std::endl;
    // 查询功能
    std::string q_word;
    while (true)
    {
        std::cout << "请输入你要查询的单词：" << std::endl;
        if (!(std::cin >> q_word) || q_word == "q") break;
        // 获得了要查询的值
        if (word_info.count(q_word) == 0) {
            std::cout << "该单词在文件中不存在！" << std::endl;
            continue;
        }
        std::cout << q_word << "一共出现了" << word_count[q_word] << "次" << std::endl;
        for (auto &item : word_info[q_word]) {
            std::cout << item << ": " << file_content[item - 1] << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "Done!" << std::endl;

    return 0;
}