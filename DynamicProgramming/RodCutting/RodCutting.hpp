#pragma once
#include <vector>
class RodCutting
{
public:
	// Space O(n)
	// Time O(n^2)
	// prices : An array of prices of rods of lengths from 1 to n
	// Returns the maximum profit(optimal value) possible  
	// Assumes that the length of the rod is n
	static float solve(const std::vector<float>& prices);

	// Space O(n)
	// Time O(n^2)
	// prices : An array of prices of rods of lengths from 1 to n
	// Returns the profit and the rod cuts in the optimal case 
	// Assumes that the length of the rod is n
	static std::pair<float, std::vector<size_t>> solveAndTrace(const std::vector<float>& prices);

};

