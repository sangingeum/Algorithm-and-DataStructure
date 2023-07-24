#include "QuickSelect.hpp"
#include "Partition.hpp" // This header is defined in $(SolutionDir)/QuickSort
#include <iostream>
#include <format>
#include <algorithm>
#include <ctime>


void printVec(const std::vector<int>& vec) {
	for (auto num : vec)
		std::cout << num << " ";
	std::cout << "\n";
}


int main() {
	// Generate a random vector of length 20
	std::srand(unsigned(std::time(nullptr)));
	std::vector<int> vec(20);
	std::generate(vec.begin(), vec.end(), std::rand);

	// Create three quick select algorithms with different partitioning strategies
	QuickSelect<Partition> basicQS;
	QuickSelect<RandomizedPartition> randomizedQS;
	QuickSelect<MedianOfThreePartition> medianOfThreeQS;

	// Print the random vector
	printVec(vec);
	
	// Print the 0th element
	size_t k = 0;
	std::cout << std::format("{}th element\n", k);
	std::cout << std::format("basicQS:{}, randomizedQS:{}, medianOfThreeQS:{}\n",
		basicQS.select(vec, k), randomizedQS.select(vec, k), medianOfThreeQS.select(vec, k));
	// Print the 5th element
	k = 5;
	std::cout << std::format("{}th element\n", k);
	std::cout << std::format("basicQS:{}, randomizedQS:{}, medianOfThreeQS:{}\n",
		basicQS.select(vec, k), randomizedQS.select(vec, k), medianOfThreeQS.select(vec, k));
	// Print the 10th element
	k = 10;
	std::cout << std::format("{}th element\n", k);
	std::cout << std::format("basicQS:{}, randomizedQS:{}, medianOfThreeQS:{}\n",
		basicQS.select(vec, k), randomizedQS.select(vec, k), medianOfThreeQS.select(vec, k));
	// Print the 15th element
	k = 15;
	std::cout << std::format("{}th element\n", k);
	std::cout << std::format("basicQS:{}, randomizedQS:{}, medianOfThreeQS:{}\n",
		basicQS.select(vec, k), randomizedQS.select(vec, k), medianOfThreeQS.select(vec, k));
	
	// Sort and print the vector to see if the answers are correct
	std::sort(vec.begin(), vec.end());
	printVec(vec);

	return 0;
}