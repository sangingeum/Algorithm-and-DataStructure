#pragma once
#include <vector>
class CoinChange
{
public:
	// Space O(sum)
	// Time O(n * sum)
	// coins: positive integer coins
	// Assumes that there are an infinite number of each coin
	// Returns the number of possible coin combinations that sum up to the given sum
	static size_t solve(size_t sum, const std::vector<size_t> coins);
};

