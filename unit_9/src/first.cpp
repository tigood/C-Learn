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

int main()
{
    text_1();

    return 0;
}