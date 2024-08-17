#include <iostream>
#include <vector>
#include <list>

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

void text_3()
{
    int ai[] = {1, 1, 2, 3, 4, 5, 6, 7};
    std::vector<int> ivect;
    std::list<int> ilist;
    for (int item : ai)
    {
        ivect.push_back(item);
        ilist.push_back(item);
    }
    // 遍历两个容器
    for (auto it = ivect.begin(); it != ivect.end();)
    {
        if (*it % 2 == 0)
        {
            // 由于擦除数据之后之前的迭代器就会失效，所以通过返回值来更新it
            it = ivect.erase(it); // 擦除数据
        }
        else
        {
            it++;
        }
    }
    for (auto it = ilist.begin(); it != ilist.end();)
    {
        if (*it % 2 != 0)
        {
            it = ilist.erase(it);
        }
        else
        {
            it++;
        }
    }
    show_item(ivect);
}

int main()
{
    // text_1();
    text_3();

    return 0;
}