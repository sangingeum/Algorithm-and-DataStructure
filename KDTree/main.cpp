#include "KDTree.hpp"
#include <iostream>


// Find a point nearest to the given point in the K-D tree and print it 
void testFindNearest(KDTree<2>& tree, std::array<float, 2> point) {
	auto result = tree.findNearest(point);
	std::cout << std::format("x:{}, y:{}\n", result[0], result[1]);
}

int main() {

	// Construct a vector of 25 points forming a 5 x 5 grid
	std::vector<std::array<float, 2>> pointVector;
	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 5; ++j) {
			pointVector.push_back({ i*1.f, j*1.f });
		}
	}

	// Build a K-D tree using the point vector
	// The tree can effectively balance itself if points are given to its constructor
	KDTree<2, float> tree(pointVector);

	// Test the findNearest operation
	testFindNearest(tree, { 0.5f, 0.5f }); // Nearest point to (0.5, 0.5): (0, 0)
	testFindNearest(tree, { 0.2f, 0.4f }); // Nearest point to (0.2, 0.4): (0, 0)
	testFindNearest(tree, { 1.0f, 4.5f }); // Nearest point to (1.0, 4.5): (1, 4)
	testFindNearest(tree, { 3.4f, 2.6f }); // Nearest point to (3.4, 2.6): (3, 3)
	testFindNearest(tree, { 0.0f, 0.0f }); // Nearest point to (0.0, 0.0): (0, 0)
	testFindNearest(tree, { 6.5f, 2.5f }); // Nearest point to (6.5, 2.5): (4, 2)
	testFindNearest(tree, { 2.2f, -10.0f }); // Nearest point to (2.2, -10.0): (2, 0)
	testFindNearest(tree, { -20.0f, -10.0f }); // Nearest point to (-20.0, -10.0): (0, 0)
	testFindNearest(tree, { 20.2f, 50.0f }); // Nearest point to (20.2, 50.0): (4, 4)


	return 0;
}