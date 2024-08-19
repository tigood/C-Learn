#include <iostream>
#include <vector>

void text_1()
{
    std::vector<int> ivect;
    for (std::vector<int>::value_type i = 0; i != 24; i++)
    {
        ivect.push_back(i);
    }
    std::cout << "容器的容量为：" << ivect.size() << std::endl;
    std::cout << "容器的预留空间为：" << ivect.capacity() << std::endl;
}

int main()
{
    text_1();

    return 0;
}