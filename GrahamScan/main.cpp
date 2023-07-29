#include "GrahamScan.hpp"
#include <iostream>
#include <format>
#include <fstream>
int main() {
	// Create a 5x5 grid points. The center point is (0, 0)
	std::vector<std::pair<float, float>> points;
	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 5; ++j) {
			points.push_back({ 2.0 - i, 2.0 - j });
		}
	}
	// Print the convex hull of the points
	for (const auto& point : GrahamScan::convexHull(points)) {
		std::cout << std::format("x:{}, y:{}\n", point.first, point.second);
	}
	/*
	x:-2, y:-2
	x:2, y:-2
	x:2, y:2
	x:-2, y:2
	*/


	// Clear the points
	points.clear();
	// Load a set of points from a file
	std::ifstream stream("testCase.txt");
	while (stream) {
		float x, y;
		stream >> x >> y;
		points.push_back({ x, y });
	}
	// Print the convex hull of the points
	for (const auto& point : GrahamScan::convexHull(points)) {
		std::cout << std::format("x:{}, y:{}\n", point.first, point.second);
	}
	/*
	x:0.48238963, y:-0.477617
	x:0.49161983, y:-0.3453917
	x:0.4932167, y:0.4928094
	x:0.050542958, y:0.47549295
	x:-0.3521488, y:0.43526563
	x:-0.4907368, y:0.18658268
	x:-0.44042894, y:-0.2894856
	x:-0.16192096, y:-0.40553397

	The test case is from
	https://stackoverflow.com/questions/482278/test-case-data-for-convex-hull
	*/


	return 0;
}