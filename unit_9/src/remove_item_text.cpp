#include <iostream>
#include <vector>

inline void show_item(const std::vector<int>& _ivect)
{
    if (!_ivect.empty())
    {
        std::cout << "容器数据如下：" << std::endl;
        for (auto& item : _ivect)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    else
        std::cout << "该容器为空！" << std::endl;
}

void text_1()
{
    std::vector<int> ivect = {1, 2, 3, 4, 5, 6, 7};
    show_item(ivect);
    // 删除一个尾部元素，vector不支持pop_front()
    ivect.pop_back(); // 返回值为void
    show_item(ivect);
    // 删除一个迭代器指向的元素 返回迭代器指向元素的下一个元素
    auto it_1 = ivect.erase(ivect.begin());
    std::cout << "it_1 = " << *it_1 << std::endl;
    show_item(ivect);
    // 删除两个迭代器范围之内的元素，返回一个迭代器，这个迭代器指向
    auto it_2 = ivect.erase(ivect.begin(), ivect.begin() + 2);
    std::cout << "it_2 = " << *it_2 << std::endl;
    show_item(ivect);
    // 清空容器
    ivect.clear();
    show_item(ivect);
}

void text_2()
{
    int a = 1;
    if (a == 1)
        std::cout << "hello world" << std::endl;
    else
        std::cout << "nihaoshijie" << std::endl;
}

int main()
{
    text_1();

    return 0;
}