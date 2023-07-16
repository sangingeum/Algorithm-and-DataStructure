#include "CountingSort.hpp"
#include <algorithm>
#include <iostream>
#include <ctime>

void printVec(const std::vector<int>& vec) {
	for (auto num : vec) {
		std::cout << num << " ";
	}
	std::cout << "\n";
}

int main() {
	// Generate a random vector of length 20 whose maximum possible value is k
	std::srand(unsigned(std::time(nullptr)));
	std::vector<int> vec;
	vec.reserve(20);
	size_t k = 15;
	for (size_t i = 0; i < 20; ++i) {
		vec.push_back(std::rand() % (k + 1));
	}

	// Print the original unsorted vector
	printVec(vec);

	// Sort and print the vector
	auto sorted = CountingSort::sort(vec, k);
	printVec(sorted);

	return 0;
}