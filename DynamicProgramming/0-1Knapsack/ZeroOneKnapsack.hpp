#pragma once
#include <vector>

class ZeroOneKnapsack
{
public:
	// Space O(n * capacity)
	// Time O(n * capacity)
	// Solves a 0/1 knapsack problem
	// Returns the total value of the selected items in the optimal case
	static float solve(const std::vector<float>& values, const std::vector<float>& weights, size_t capacity);
	// Space O(n * capacity)
	// Time O(n * capacity)
	// Solves a 0/1 knapsack problem
	// Returns a pair containing the total value of the selected items and a vector of indices representing the selected items in the optimal case
	static std::pair<float, std::vector<size_t>> solveAndTrace(const std::vector<float>& values, const std::vector<float>& weights, size_t capacity);
};

