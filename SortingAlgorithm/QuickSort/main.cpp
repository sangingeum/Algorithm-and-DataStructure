#include "QuickSort.hpp"
#include "Partition.hpp"
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

	// Create three different quick sort algorithms
	QuickSort<Partition> basicQS;
	QuickSort<RandomizedPartition> randomizedQS;
	QuickSort<MedianOfThreePartition> medianOfThreeQS;
	
	// Print the original unsorted vector
	printVec(vec);
	
	// Sort and print the vector
	auto copy = vec;
	basicQS.sort(copy);
	printVec(copy);

	// Sort and print the vector
	copy = vec;
	randomizedQS.sort(copy);
	printVec(copy);

	// Sort and print the vector
	copy = vec;
	medianOfThreeQS.sort(copy);
	printVec(copy);

	return 0;
}