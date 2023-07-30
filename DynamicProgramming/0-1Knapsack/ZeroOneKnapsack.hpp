#pragma once
#include <vector>


class ZeroOneKnapsack
{
public:
	// Space O(n * capacity)
	// Time O(n * capacity)
	// Solves a 0/1 knapsack problem
	// Returns the total value of the selected items in the optimal case
	static float solve(const std::vector<float>& values, const std::vector<float>& weights, size_t capacity) {
		size_t n = values.size();
		std::vector<std::vector<float>> dp(n + 1, std::vector<float>(capacity + 1, 0));
		for (size_t i = 1; i <= n; ++i) {
			for (size_t w = 0; w <= capacity; ++w) {
				if (w >= weights[i - 1]) {
					dp[i][w] = std::max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
				}
				else {
					dp[i][w] = dp[i - 1][w];
				}
			}
		}
		return dp[n][capacity];
	}

	// Space O(n * capacity)
	// Time O(n * capacity)
	// Solves a 0/1 knapsack problem
	// Returns a pair containing the total value of the selected items and a vector of indices representing the selected items in the optimal case
	static std::pair<float, std::vector<size_t>> solveAndTrace(const std::vector<float>& values, const std::vector<float>& weights, size_t capacity) {
		size_t n = values.size();
		std::vector<std::vector<float>> dp(n + 1, std::vector<float>(capacity + 1, 0));
		std::vector<std::vector<bool>> isChosen(n + 1, std::vector<bool>(capacity + 1, false));
		std::vector<size_t> chosenItems;

		for (size_t i = 1; i <= n; ++i) {
			for (size_t w = 0; w <= capacity; ++w) {
				if (w >= weights[i - 1]) {
					dp[i][w] = std::max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
					isChosen[i][w] = true;
				}
				else {
					dp[i][w] = dp[i - 1][w];
				}
			}
		}

		size_t curItem = n;
		size_t curCapacity = capacity;
		while (curItem > 0) {
			if (isChosen[curItem][curCapacity]) {
				chosenItems.push_back(curItem - 1);
				curCapacity -= weights[curItem - 1];
			}
			curItem--;
		}

		return { dp[n][capacity], chosenItems };
	}
};

