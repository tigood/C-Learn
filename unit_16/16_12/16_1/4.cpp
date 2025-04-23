#include <iostream>

template<typename T = int>
class MyNumber
{
public:
    MyNumber(T value) : value_(value) {}

    inline void print() const { std::cout << value_ << std::endl; }

private:
    T value_;
};

int main()
{
    MyNumber<> myNumber(10);
    myNumber.print();

    MyNumber<double> myNumber2(10.5);
    myNumber2.print();
    return 0;
}