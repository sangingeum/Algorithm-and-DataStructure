#include "HeapSort.hpp"
#include <iostream>
#include <algorithm>
#include <ctime>

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
	// Print the vector
	printVec(vec);
	// Sort & Print the vector
	HeapSort::maxHeapSort(vec);
	printVec(vec);
	// Sort & Print the vector
	HeapSort::minHeapSort(vec);
	printVec(vec);

	return 0;
}