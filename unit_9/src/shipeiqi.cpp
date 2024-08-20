#include <stack>
#include <iostream>

void text_1()
{
    std::stack<int> istack;
    for (int i = 0; i < 5; i++)
        istack.push(i);
    while (!istack.empty())
    {
        auto val = istack.top();  // 获取顶部元素
        istack.pop();  // 弹出顶部元素
        std::cout << val << std::endl;
    }
    if (istack.empty()) {
        std::cout << "该栈已经为空！" << std::endl;
    }
}

void text_2()
{
    std::string target_str("this is a (shizi)");
    bool is_inside = false;
    std::stack<char> sstack;
    for (auto& item : target_str)
    {
        if (item == '(') {
            is_inside = true;
            continue;
        }
        else if(item == ')') {
            is_inside = false;
        }
        if (is_inside) {
            sstack.push(item);
        }
    }
    std::string result;
    while (!sstack.empty())
    {
        result += sstack.top();
        sstack.pop();
    }
    target_str.replace(target_str.find('(') + 1, result.size(), result);
    std::cout << target_str << std::endl;
}

int main()
{
    // text_1();
    text_2();
    return 0;
}