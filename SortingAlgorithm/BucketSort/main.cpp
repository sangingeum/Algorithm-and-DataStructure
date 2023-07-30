#include "BucketSort.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <memory>

void printVec(const std::vector<float>& vec) {
	for (auto num : vec) {
		std::cout << num << " ";
	}
	std::cout << "\n";
}
int main() {
	// Generate a random vector of length 20
	std::srand(unsigned(std::time(nullptr)));
	std::vector<float> vec(20);
	for (size_t i = 0; i < 20; ++i) {
		vec[i] = std::rand() / static_cast<float>(RAND_MAX + 1);
	}

	// Print the original unsorted vector
	printVec(vec);

	// Sort and print the vector
	BucketSort::sort(vec, 20);
	printVec(vec);


	return 0;
}