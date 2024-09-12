#include <iostream>
#include <cstring>
#include <memory>

void text_1() {
    // 使用new分配数组
    int *p1 = new int[5](); // 添加()将值初始化为0;
    for (int i = 0; i < 5; i++)
        p1[i] = i;
    for (int i = 0; i < 5; i++)
        std::cout << p1[i] << " ";
    std::cout << std::endl;
    // 使用delete释放一个动态内存的数组的时候，需要在后面加上[]
    delete[] p1;
}

// 12.23
void text_2() {
    const char *str_1 = "hello world";
    const char *str_2 = "tigood";
    char *p_ch = new char[strlen(str_1) + strlen(str_2) + 1]();
    strcpy(p_ch, str_1);
    strcat(p_ch, str_2);
    // 输出结果
    std::cout << p_ch << std::endl;
    delete[] p_ch;
}

void text_3() {
    // 重写上一个函数，使用标准库string
    std::string s1{"hello world"};
    std::string s2{"tigood"};
    size_t result_len = s1.length() + s2.length() + 1;
    char *result = new char[result_len]();
    // c_str()方法从一个string对象变为一个C类型的字符串类型
    strcpy(result, (s1 + s2).c_str());
    std::cout << result << std::endl;
    delete[] result;
}

void text_4() {
    // 12.24
    std::cout << "请输入您要输入的字符串的长度：" << std::endl;
    int str_len;
    std::cin >> str_len;
    std::cin.ignore();
    char *input = new char[str_len + 1];
    std::cout << "请输入一个字符串：" << std::endl;
    std::cin.get(input, str_len + 1);
    std::cout << input << std::endl;
    delete[] input;
}

void text_5() {
    // 12.26
    // 使用allocator开辟一块大内存
    // 创建一个string的分配至
    int n = 10;
    std::allocator<std::string> alloc;
    // 分配n个未初始化的std::string，并声明一个指针常量指向空间开头
    auto const p = alloc.allocate(n);
    // 添加内容
    auto q = p;
    std::string s;
    while (std::getline(std::cin, s) && q != p + n)
    {
        *q++ = s;
    }
    // 记录我们读取了多少了字符串
    size_t count = q - p;
    for (int i = 0; i < count; i++) {
        std::cout << p[i] << std::endl;
    }
    // 将空间释放
    alloc.deallocate(p, n);
}

int main() {
    // text_1();
    // text_2();
    // text_3();
    // text_4();
    text_5();

    return 0;
}