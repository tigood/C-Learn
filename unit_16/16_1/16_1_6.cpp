#include <iostream>
#include <string>

template <typename T, unsigned size>
T* begin_def(T (&arr)[size]) {
	return arr;
}

template <typename T, unsigned size>
T* end_def(T (&arr)[size]) {
	return arr + size;
}

int main() {
	std::string str[]{"sssss", "hello", "aaa", "adfafadfafa"};
	std::cout << *(begin_def(str) + 1) << std::endl;
	std::cout << *(end_def(str) - 1) << std::endl;

	return 0;
}