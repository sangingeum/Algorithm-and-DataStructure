#include "CoinChange.hpp"
// Space O(sum)
// Time O(n * sum)
// coins: positive integer coins
// Assumes that there are an infinite number of each coin
// Returns the number of possible coin combinations that sum up to the given sum
size_t CoinChange::solve(size_t sum, const std::vector<size_t> coins) {
	size_t n = coins.size();
	std::vector<size_t> dp(sum + 1, 0);
	dp[0] = 1;
	for (size_t i = 0; i < n; ++i) {
		size_t curCoin = coins[i];
		for (size_t j = curCoin; j <= sum; ++j) {
			dp[j] += dp[j - curCoin];
		}
	}
	return dp[sum];
}