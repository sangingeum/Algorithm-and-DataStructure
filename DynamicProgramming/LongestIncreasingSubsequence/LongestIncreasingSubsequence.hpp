#pragma once
#include <vector>
#include <algorithm>
class LongestIncreasingSubsequence
{
public:
	// Space O(n)
	// Time O(nlog(n))
	// Returns a pair of the length of the LIS and the LIS of the given array. 
	static std::pair<size_t, std::vector<float>> solve(const std::vector<float>& nums);
};

