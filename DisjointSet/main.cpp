#include "DisjointSet.hpp"
#include <iostream>
#include <format>
int main() {
	// Create a DisjointSet with 10 initial sets
	size_t size = 10;
	DisjointSet set(size);

	// Uniton sets
	set.unionSets(0, 5);
	set.unionSets(3, 2);
	set.unionSets(5, 2);
	set.unionSets(8, 6);
	set.unionSets(1, 6);

	// Print their roots
	for (size_t i = 0; i < size; ++i) {
		std::cout << std::format("Root of {}: {}\n", i, set.find(i));
	}
	/*
	Root of 0: 0
	Root of 1: 8
	Root of 2: 0
	Root of 3: 0
	Root of 4: 4
	Root of 5: 0
	Root of 6: 8
	Root of 7: 7
	Root of 8: 8
	Root of 9: 9
	*/

	return 0;
}