#include <ctime>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <format>
#include <stdexcept>
#include "BinarySearchTree.hpp"

struct Data {
	size_t id;
	float grade;
};

int main() {
	// Generate 18 unique random keys, 1 very small key, and 1 very large key
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	std::unordered_set<long long> keyPool;
	while (keyPool.size() < 18) {
		keyPool.insert(std::rand());
	}
	std::vector<long long> keys(keyPool.begin(), keyPool.end());
	keys.push_back(INT32_MIN);
	keys.push_back(INT32_MAX);

	// Create a binary search tree that stores Data instances
	BinarySearchTree<Data> tree;

	// Insert 20 data instances to the tree
	for (size_t i = 0; i < 20; ++i) {
		tree.insert(keys[i], { i, i * 5.f });
	}

	// Print the keys in increasing order
	tree.inOrderTreeWalk();

	// Test the get operation
	for (size_t i = 0; i < 20; ++i) {
		auto& data = tree.get(keys[i]);
		std::cout << std::format("id:{}, grade:{}\n", data.id, data.grade);
	}
	
	// Data with the smallest key
	auto data = tree.min();
	std::cout << std::format("id:{}, grade:{}\n", data.id, data.grade);
	// Data with the largest key
	data = tree.max();
	std::cout << std::format("id:{}, grade:{}\n", data.id, data.grade);

	// Test the remove and find operations
	for (size_t i = 0; i < 20; ++i) {
		bool foundBefore = tree.find(keys[i]);
		tree.remove(keys[i]);
		bool foundAfter = tree.find(keys[i]);
		std::cout << std::format("foundBefore:{}, foundAfter:{}\n", foundBefore, foundAfter);
	}

	return 0;
}