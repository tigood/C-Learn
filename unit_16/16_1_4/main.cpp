#include "QueryResult.h"
#include "TextQuery.h"

int main()
{
    // 询问用户
    std::string fileName;
    std::cout << "Please enter the file name: ";
    std::cin >> fileName;

    // 获取一个文件流
    std::ifstream ifs(fileName);
    if (!ifs) {
        std::cerr << "Error: cannot open file " << fileName << std::endl;
        return -1;
    }

    TextQuery   tq(ifs);
    std::string queryWord;
    while (true) {
        std::cout << "Please enter the word you want to query: ";
        std::cin >> queryWord;
        QueryResult qr = tq.query(queryWord);
        print(std::cout, qr);
        std::cout << "Do you want to continue? (y/n): ";
        char ch;
        std::cin >> ch;
        if (ch == 'n') {
            break;
        }
        else if (ch != 'y') {
            std::cerr << "Error: invalid input" << std::endl;
            return -1;
        }
        else {
            continue;
        }
    }

    return 0;
}