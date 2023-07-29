#include "SegmentTree.hpp"
#include <iostream>

int main() {
	// Create a vector
	std::vector<float> vec;
	for (int i = 1; i <= 5; ++i)
		vec.push_back(i);
	// 1, 2, 3, 4, 5

	// Create a segment tree for sum queries
	SegmentTree<SumMerger<float>> tree1(vec);
	// query(from, to) : queries the aggregated value from [from, to).
	// Note that 'from' is inclusive and 'to' is exclusive
	for (int i = 0; i < 5; ++i)
		for (int j = i + 1; j <= 5; ++j)
			std::cout << tree1.query(i, j) << " ";
	std::cout << "\n";
	// 1 3 6 10 15 2 5 9 14 3 7 12 4 9 5

	// Create a segment tree for max queries
	SegmentTree<MaxMerger<float>> tree2(vec);
	for (int i = 0; i < 5; ++i)
		for (int j = i + 1; j <= 5; ++j)
			std::cout << tree2.query(i, j) << " ";
	std::cout << "\n";
	// 1 2 3 4 5 2 3 4 5 3 4 5 4 5 5

	// Create a segment tree for min queries
	SegmentTree<MinMerger<float>> tree3(vec);
	for (int i = 0; i < 5; ++i)
		for (int j = i + 1; j <= 5; ++j)
			std::cout << tree3.query(i, j) << " ";
	std::cout << "\n";
	// 1 1 1 1 1 2 2 2 2 3 3 3 4 4 5

	// Test the update operation
	tree3.update(0, 10);
	tree3.update(2, 99);
	tree3.update(3, 16);
	for (int i = 0; i < 5; ++i)
		for (int j = i + 1; j <= 5; ++j)
			std::cout << tree3.query(i, j) << " ";
	std::cout << "\n";
	// 10 2 2 2 2 2 2 2 2 99 16 5 16 5 5


	return 0;
}