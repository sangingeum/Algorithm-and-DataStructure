#include "Levenshtein.hpp"
// Space O(MIN(strA.size(), strB.size()))
// Time O(strA.size() * strB.size())
// Given two strings, returns the Levenshtein distance between them
size_t Levenshtein::distance(const std::string& strA, const std::string& strB) {
	// If B is longer, swap A and B to make strB shorter
	if (strB.size() > strA.size())
		return distance_(strB, strA);
	return distance_(strA, strB);
}

size_t Levenshtein::distance_(const std::string& strA, const std::string& strB) {

	size_t n = strA.size();
	size_t m = strB.size();

	std::vector<size_t> dp(m + 1, 0);
	for (size_t j = 0; j <= m; ++j) { dp[j] = j; }

	for (size_t i = 1; i <= n; ++i) {
		size_t diagonalDP = dp[0];
		size_t prevRowDP;
		dp[0] = i;
		for (size_t j = 1; j <= m; ++j) {
			prevRowDP = dp[j];
			char charA = strA[i - 1];
			char charB = strB[j - 1];
			if (charA == charB) {
				dp[j] = diagonalDP;
			}
			else {
				dp[j] = 1 + std::min({ diagonalDP, prevRowDP, dp[j - 1] });
			}
			diagonalDP = prevRowDP;
		}
	}

	return dp[m];
}