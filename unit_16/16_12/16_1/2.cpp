#include <iostream>

template<typename T>
typename T::value_type top(const T &c)
{
    if (!c.empty())
        return c.back();
    else
        return typename T::value_type();
}

int main()
{
    std::string s("hello");
    std::cout << top(s) << std::endl;
    std::cout << top(std::string()) << std::endl;

    return 0;
}