#include "../include/String.hpp"
#include <vector>
#include <iostream>

void text_1() {
    std::vector<String> svect;
    svect.reserve(3);
    svect.push_back("hello");
    svect.push_back("world");
    svect.push_back("tigood");
    std::cout << "Done" << std::endl;
}

int main() {
    text_1();

    return 0;
}