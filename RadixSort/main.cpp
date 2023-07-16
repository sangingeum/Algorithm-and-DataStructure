#include "RadixSort.hpp"
#include <algorithm>
#include <ctime>
#include <iostream>

void printVec(const std::vector<int>& vec) {
	for (auto num : vec) {
		std::cout << num << " ";
	}
	std::cout << "\n";
}

int main() {
	// Generate a random vector of length 20
	std::srand(unsigned(std::time(nullptr)));
	std::vector<int> vec(20);
	std::generate(vec.begin(), vec.end(), std::rand);

	// Print the original unsorted vector
	printVec(vec);

	// Sort and print the vector
	RadixSort::sort(vec);
	printVec(vec);
	return 0;
}