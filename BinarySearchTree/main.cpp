#include "BinarySearchTree.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <format>

struct Data {
	size_t id;
	float grade;
};

int main() {
	// Generate 18 random keys, 1 very small key, and 1 very large key
	std::srand(unsigned(std::time(nullptr)));
	std::vector<long long> vec(18);
	std::generate(vec.begin(), vec.end(), std::rand);
	vec.push_back(INT32_MIN);
	vec.push_back(INT32_MAX);

	// Create a binary search tree which stores Data instances
	BinarySearchTree<Data> tree;

	// Insert 20 data instances to the tree
	for (size_t i = 0; i < 20; ++i) {
		tree.insert(vec[i], { i, i * 5.f });
	}

	// Print the keys in the increasing order
	tree.inOrderTreeWalk();

	// Test the get operation
	for (size_t i = 0; i < 20; ++i) {
		auto& data = tree.get(vec[i]);
		std::cout << std::format("id:{}, grade:{}\n", data.id, data.grade);
	}
	
	// data with the smallest key
	auto data = tree.min();
	std::cout << std::format("id:{}, grade:{}\n", data.id, data.grade);
	// data with the largest key
	data = tree.max();
	std::cout << std::format("id:{}, grade:{}\n", data.id, data.grade);

	// Test the remove and find operations
	for (size_t i = 0; i < 20; ++i) {
		bool foundBefore = tree.find(vec[i]);
		tree.remove(vec[i]);
		bool foundAfter = tree.find(vec[i]);
		std::cout << std::format("foundBefore:{}, foundAfter:{}\n", foundBefore, foundAfter);
	}

	return 0;
}