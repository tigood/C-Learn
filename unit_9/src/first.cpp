#include <iostream>
#include <vector>

void text_1()
{
    std::cout << "这是一个C++项目！" << std::endl;
    std::vector<int> ivect({1, 2, 3, 4});
    for (auto& item : ivect)
    {
        std::cout << item << std::endl;
    }
    std::cout << "首元素：" << *ivect.begin() << std::endl;
    std::cout << "首元素的第二种获取方式：" << ivect.front() << std::endl;
    std::cout << "尾元素：" << ivect.back() << std::endl;
}

void text_2()
{
    std::vector<int> ivect = { 1, 2, 3 };
    auto value1 = ivect.at(0);
    auto value2 = ivect[0];
    auto value3 = *ivect.begin();
    auto value4 = ivect.front();
    std::cout << "value1 = " << value1 << std::endl;
    std::cout << "value2 = " << value2 << std::endl;
    std::cout << "value3 = " << value3 << std::endl;
    std::cout << "value4 = " << value4 << std::endl;
}

int main()
{
    // text_1();
    text_2();

    return 0;
}