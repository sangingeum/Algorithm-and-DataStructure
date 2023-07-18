#include <ctime>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <format>
#include <stdexcept>
#include "RedBlackTree.hpp"

struct Data {
	size_t id;
	float grade;
};

int main() {
    // Generate 200 unique random keys
    std::size_t keySize = 200;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::unordered_set<long long> keyPool;
    while (keyPool.size() < keySize) {
        keyPool.insert(std::rand());
    }
    std::vector<long long> keys(keyPool.begin(), keyPool.end());

    // Create a Red Black Tree that stores Data instances
    RedBlackTree<Data> tree;

    // Insert data into the tree
    for (std::size_t i = 0; i < keySize; ++i) {
        tree.insert(keys[i], { i, 5.f * i });
    }

    // Test the get operation
    for (std::size_t i = 0; i < keySize; ++i) {
        auto& data = tree.get(keys[i]);
        std::cout << std::format("id:{}, grade:{}\n", data.id, data.grade);
    }

    // Test the remove and find operations
    for (std::size_t i = 0; i < keySize; ++i) {
        bool foundBefore = tree.find(keys[i]);
        tree.remove(keys[i]);
        bool foundAfter = tree.find(keys[i]);
        std::cout << std::format("foundBefore:{}, foundAfter:{}\n", foundBefore, foundAfter);
        // If foundBefore and foundAfter are the same, throw an exception
        if (foundBefore == foundAfter) {
            throw std::runtime_error("Found before and after removal are the same.");
        }
    }

    return 0;
}