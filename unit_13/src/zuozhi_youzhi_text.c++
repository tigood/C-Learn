#include <iostream>
#include <vector>
#include <utility>

void text_5() {
    int i = 10;
    int &a = i;
    const int &b = i + 10;
    std::cout << "i = " << i << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    i = 20;
    std::cout << "i = " << i << std::endl;
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
}

void text_1() {
    int &&i = 1;  // 这样是正确的，将一个右值引用绑定到一个右值上
    // int &&i2 = i;  // 这样是不对的，变量i被认为是一个左值，而不是一个右值
    // 使用move
    int &&i2 = std::move(i); // 这个move的意思就是告诉编译器，我们希望将i这个左值当作一个右值来处理
}

int fun1() {
    return 1;
}

void text_2() {
    int &&i = fun1();
    std::vector<int> ivect{1, 2, 3, 4};
    int &i1 = ivect[1];
    int &a = i1;
    int &&b = ivect[1] * fun1();
}

int main() {
    text_5();
}