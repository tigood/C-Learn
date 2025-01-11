#include "Query.h"
#include "TextQuery.h"
#include "QueryResult.h"
#include <fstream>
#include <iostream>

int main() {
    std::ifstream file("post.txt");
    if (!file) {
        std::cerr << "Failed to open file: post.txt" << std::endl;
        return 1;
    }

    TextQuery tq(file);
    Query q = Query(",") | Query("she");

    std::cout << q << std::endl;

    print(std::cout, q.eval(tq));

    return 0;
}
