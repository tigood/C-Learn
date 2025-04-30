#include <iostream>

template<typename Printable>
void print(std::ostream &os, Printable printable)
{
    os << printable << std::endl;
}

template<typename Printable, typename... Args>
void print(std::ostream &os, Printable printable, Args const &...args)
{
    os << printable << ", ";
    return print(os, args...);
}

int main()
{
    print(std::cout, 1, 2, 3, 5, 6);
    print(std::cout, 1);
    print(std::cout, "hello", 1, 2, "world", "!");

    return 0;
}