#include <map>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, std::string> buildMap(std::ifstream& map_file) {
    // 读取一个文件数据，将文件中的数据填充到一个字典中
    std::map<std::string, std::string> trans_map;
    std::string key;
    std::string value;
    // 将数据读入字典
    while (map_file >> key && std::getline(map_file, value))
    {
        // 检查是否有转换内容
        if (value.size() >= 1) {
            trans_map[key] = value.substr(1); // 跳过第一个空白字符
        } else {
            throw std::runtime_error("没有" + key);
        }
    }
    return trans_map;
}

std::string transform(std::string word, std::map<std::string, std::string> trans_map) {
    // 查找该单词是否在映射表中，如果在返回对应的值，否则返回原字符串
    if (trans_map.find(word) != trans_map.end())
        return trans_map[word];
    return word;
}

void word_transform(std::ifstream& map_file, std::ifstream& input) {
    // 1. 将替换规则从文件中读取出来存取到一个字典中
    // 2. 从代替换文件中读取数据，然后将单体替换掉
    auto trans_map = buildMap(map_file);
    std::string text;
    while (getline(input, text))
    {
        // 对该字符串创建一个字符串读取流
        std::istringstream stream(text);
        std::string word;
        // 设置一个标志检测是否是第一行的第一个单词
        bool firstword_flag = true;
        while (stream >> word)
        {
            if (firstword_flag) {
                firstword_flag = false;
            } else {
                std::cout << " ";
            }
            std::cout << transform(word, trans_map);
        }
        std::cout << std::endl;
    }
}

int main() {
    // 创建两个文件读取流
    std::ifstream map_file("map_file.txt");
    std::ifstream target_file("target_post.txt");
    word_transform(map_file, target_file);

    return 0;
}