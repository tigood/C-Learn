#include <iostream>
#include <vector>
#include <forward_list>
#include <list>

void text_1()
{
    std::vector<int> ivect(5, 42);  // 5个值都是43
    // 修改ivect的值
    ivect.resize(10);  // 容器的长度变为10，后半部分数据被初始化为0
    ivect.resize(2);  // 容器长度变为2,删除了后8位数据
    ivect.resize(10, 1); // 将容器的长度设置为10，任何新添加的数据都将被初始化为1
}

void text_2()
{
    std::vector<int> ivect = {1, 2, 3, 4, 5};
    // 傻瓜循环，复制单数，删除复数
    auto iter = ivect.begin();
    while (iter != ivect.end())
    {
        if (*iter % 2)
        {
            // 复制单数 返回值是一个指向新元素的迭代器
            iter = ivect.insert(iter, *iter);
            iter += 2;  // 将迭代器移向下一个下一个元素，跳过新插入的元素和原来的元素
        }
        else
        {
            // 擦除该复数，然后将指针指向该元素的下一个元素
            iter = ivect.erase(iter);
        }
    }
}

void text_3()
{
    // 链表模式的傻瓜循环
    std::forward_list<int> iforlist = {1, 2, 3, 4, 5, 6};
    auto perv = iforlist.before_begin();
    auto curr = iforlist.begin();
    while (curr != iforlist.end())
    {
        if (*curr % 2)
        {
            curr = iforlist.insert_after(curr, *curr);
            perv = curr;
            std::next(curr);
        }
        else
        {
            curr = iforlist.erase_after(perv);
        }
    }
}

int main()
{

    return 0;
}