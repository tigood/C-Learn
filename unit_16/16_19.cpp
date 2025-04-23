#include <iostream>

template<typename Container>
std::ostream &print(Container &container, std::ostream &os)
{
    for (typename Container::size_type i = 0; i < container.size(); i++) {
        os << container[i] << " ";
    }
    os << std::endl;
    return os;
}

template<typename Container>
std::ostream &printByIterator(Container &container, std::ostream &os)
{
    for (typename Container::iterator it = container.begin(); it != container.end(); it++)
    {
        os << *it << " ";
    }
    std::cout << std::endl;

    return os;
}

int main()
{
    std::string s("hello");
    print(s, std::cout);
    printByIterator(s, std::cout);
    return 0;
}