#include "QueryResult.h"

std::ostream &print(std::ostream &os, const QueryResult &qr) {
    // 输出查询到的结果
    std::cout << qr.sought_ << "一共在" << qr.lines_->size() << "行中：" << std::endl;
    for (auto &item : *qr.lines_) {
        std::cout << "(line " << item << ") " << *(qr.file_->begin() + item - 1) << std::endl;
    }
    std::cout << std::endl;
    // 再将这个标准输出函数返回，这样就可以支持链式操作了
    return os;
}