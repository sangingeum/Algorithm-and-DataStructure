#include "HashFunction.hpp"
#include "HashTable.hpp"
#include <iostream>
#include <format>
#include <algorithm>
#include <ctime>

struct Data {
	size_t id;
	float grade;
};

void printVec(const std::vector<int>& vec) {
	for (auto num : vec) {
		std::cout << num << " ";
	}
	std::cout << "\n";
}

int main() {
	// Generate 20 random keys
	std::srand(unsigned(std::time(nullptr)));
	std::vector<long long> vec(20);
	std::generate(vec.begin(), vec.end(), std::rand);
	
	// Create a ChainedHashTable with size 17 => Collisions are inevitable
	ChainedHashTable<Data, MultiplicationHashFunction> table(17);

	// Insert 20 data instances to the table 
	for (size_t i = 0; i < 20; ++i) {
		table.insert(vec[i], {i, i*5.f});
	}

	// Test the get operation
	for (size_t i = 0; i < 20; ++i) {
		auto& data = table.get(vec[i]);
		std::cout << std::format("id:{}, grade:{}\n", data.id, data.grade);
	}

	// Test the find and remove operations
	for (size_t i = 0; i < 20; ++i) {
		bool foundBefore = table.find(vec[i]);
		table.remove(vec[i]);
		bool foundAfter = table.find(vec[i]);
		std::cout << std::format("foundBefore:{}, foundAfter:{}\n", foundBefore, foundAfter);
	}
}