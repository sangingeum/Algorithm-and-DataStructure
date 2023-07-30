#pragma once
#include <vector>
#include <string>
class Levenshtein
{
public:
	// Space O(MIN(strA.size(), strB.size())) where n is the length of the shorter string
	// Time O(strA.size() * strB.size())
	// Given two strings, returns the Levenshtein distance between them
	static size_t distance(const std::string& strA, const std::string& strB) {
		// If B is longer, swap A and B to make strB shorter
		if (strB.size() > strA.size())
			return distance_(strB, strA);
		return distance_(strA, strB);
	}
private:
	// Private helper method
	static size_t distance_(const std::string& strA, const std::string& strB) {

		size_t n = strA.size();
		size_t m = strB.size();

		std::vector<std::vector<size_t>> dp(2, std::vector<size_t>(m + 1, 0));
		for (size_t j = 0; j <= m; ++j) { dp[0][j] = j; }

		for (size_t i = 1; i <= n; ++i) {
			dp[1][0] = i;
			for (size_t j = 1; j <= m; ++j) {
				char charA = strA[i - 1];
				char charB = strB[j - 1];
				if (charA == charB) {
					dp[1][j] = dp[0][j - 1];
				}
				else {
					dp[1][j] = 1 + std::min({ dp[0][j - 1], dp[1][j - 1], dp[0][j] });
				}
			}
			std::swap(dp[0], dp[1]);
		}

		return dp[0][m];
	}
};

