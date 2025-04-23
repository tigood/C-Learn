#include <iostream>
#include <string>

template <typename Array>
void print(const Array& array) {
	for (auto item : array) {
		std::cout << item << " ";
	}
	std::cout << std::endl;
}

int main() {
	char c[] = {'a', 'b', 'c', 'd', 'e'};
	int i[] = {1, 2, 3, 4, 5, 6};
	std::string str[] = {"hello", "world", "ni", "hao", "hello world"};
	print(c);
	print(i);
	print(str);

	return 0;
}