#include "RodCutting.hpp"
// Space O(n)
// Time O(n^2)
// prices : An array of prices of rods of lengths from 1 to n
// Returns the maximum profit(optimal value) possible  
// Assumes that the length of the rod is n
float RodCutting::solve(const std::vector<float>& prices) {
	size_t n = prices.size();
	std::vector<float> dp(n + 1, 0);
	for (size_t i = 1; i <= n; ++i) {
		float curDP = dp[i - 1];
		for (size_t j = 0; j < i; ++j) {
			curDP = std::max(curDP, prices[j] + dp[i - j - 1]);
		}
		dp[i] = curDP;
	}
	return dp[n];
}

// Space O(n)
// Time O(n^2)
// prices : An array of prices of rods of lengths from 1 to n
// Returns the profit and the rod cuts in the optimal case 
// Assumes that the length of the rod is n
std::pair<float, std::vector<size_t>> RodCutting::solveAndTrace(const std::vector<float>& prices) {
	size_t n = prices.size();
	std::vector<float> dp(n + 1, 0);
	std::vector<float> cut(n + 1);
	for (size_t i = 1; i <= n; ++i) {
		float curDP = dp[i - 1];
		for (size_t j = 0; j < i; ++j) {
			float temp = prices[j] + dp[i - j - 1];
			if (curDP < temp) {
				curDP = temp;
				cut[i] = j + 1;
			}
		}
		dp[i] = curDP;
	}

	// Build trace
	std::vector<size_t> trace;
	size_t i = n;
	while (i > 0) {
		size_t curCut = cut[i];
		trace.emplace_back(curCut);
		i -= curCut;
	}

	return { dp[n], trace };
}