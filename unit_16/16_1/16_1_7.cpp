#include <iostream>
#include <string>

template <typename T, unsigned size>
constexpr unsigned get_size(const T (&p)[size]) {
	return size;
}

int main() {
	std::string s[]{"sssss"};
	std::cout << get_size(s) << std::endl;

	char c[] = "s22";
	std::cout << get_size(c) << std::endl;

	return 0;
}