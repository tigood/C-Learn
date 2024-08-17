#include <iostream>
#include <vector>
#include <forward_list>

void text_1()
{
    /*it + 1这种加减操作对于不支持随机访问的容器是不可行的，只能使用it++*/
    std::vector<int> ivect = { 1, 2, 3, 4, 5, 6 };
    auto ivect_it = ivect.begin();
    std::forward_list<int> iforlist;
    // forward_list是一个单向链表
    auto it_1 = iforlist.before_begin(); // 返回首个元素的前一个位置，这个位置不指向任何元素
    auto it_2 = iforlist.cbefore_begin();  // 返回const版本的迭代器
    // 插入元素
    iforlist.insert_after(it_1, 1); // 在it_1迭代器之后插入一个元素
    iforlist.insert_after(it_1, 10, 1); // 在it_1迭代器之后插入10个元素1
    iforlist.insert_after(it_1, ivect_it, ivect_it + 2); // 将后两个迭代器之间的元素插入it_1之后
    iforlist.insert_after(it_1, {1, 2, 3, 4});// 在it_1迭代器之后插入列表中的元素
    // 创建元素
    iforlist.emplace_after(it_1, 1); // 在it_1迭代器之后创建一个元素
    // 删除元素
    iforlist.erase_after(it_1); // 删除迭代器之后的元素
    iforlist.erase_after(it_1, it_1++); // 删除这两个迭代器之间的元素
}

void text_2()
{
    // 操作单向链表的时候，我们需要注意两个值
    // 一个是被操作的值本身，另一个就是这个值的前一个位置
    std::forward_list<int> iforlist = {1, 2, 3, 4, 5, 6};
    auto prev = iforlist.before_begin();
    auto curr = iforlist.begin();
    while (curr != iforlist.end())
    {
        if (*curr % 2 == 0)
        {
            curr = iforlist.erase_after(prev);
        }
        else
        {
            prev = curr;
            curr++;
        }
    }
    // 遍历列表
    for (auto& item : iforlist) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void text_4(std::forward_list<std::string>& strlist, std::string str_1, std::string str_2)
{
    auto perv = strlist.before_begin();
    auto curr = strlist.begin();
    while (curr != strlist.end())
    {
        if (*curr == str_1) {
            strlist.insert_after(curr, str_2);
            return;
        }
        else
        {
            perv = curr;
            curr++;
        }
    }
    // 如果走到这里还没有插入元素，就说明没有找到
    strlist.insert_after(perv, str_2);
}

int main()
{
    std::forward_list<std::string> strlist = {"hello", "world"};
    text_4(strlist, "hello", "nihao");
    text_4(strlist, "hehe", "hehe");
    for (auto &item : strlist)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    return 0;
}
