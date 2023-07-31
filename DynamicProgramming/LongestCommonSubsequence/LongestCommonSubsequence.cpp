#include "LongestCommonSubsequence.hpp"
// Space O(n*m)
// Time O(n*m)
// Given two strings, returns the length of the LCS of them
size_t LongestCommonSubsequence::solve(const std::string& strA, const std::string& strB) {
	size_t n = strA.size(), m = strB.size();
	std::vector<std::vector<size_t>> dp(n + 1, std::vector<size_t>(m + 1, 0));

	// Fill up the DP table
	for (size_t i = 1; i <= n; ++i) {
		for (size_t j = 1; j <= m; ++j) {
			auto charA = strA[i - 1], charB = strB[j - 1];
			if (charA == charB) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	return dp[n][m];
}

// Space O(n*m)
// Time O(n*m)
// Given two strings, returns the length of the LCS and the LCS of them
std::pair<size_t, std::string> LongestCommonSubsequence::solveAndTrace(const std::string& strA, const std::string& strB) {
	size_t n = strA.size(), m = strB.size();
	std::vector<std::vector<size_t>> dp(n + 1, std::vector<size_t>(m + 1, 0));

	// Fill up the DP table
	for (size_t i = 1; i <= n; ++i) {
		for (size_t j = 1; j <= m; ++j) {
			auto charA = strA[i - 1], charB = strB[j - 1];
			if (charA == charB) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}

	// Construct LCS
	std::string lcs;
	size_t i = n, j = m;
	while (i > 0 && j > 0) {
		auto charA = strA[i - 1], charB = strB[j - 1];
		if (charA == charB) {
			lcs.push_back(charA);
			i--; j--;
		}
		else {
			if (dp[i - 1][j] > dp[i][j - 1])
				i--;
			else
				j--;
		}
	}
	std::reverse(lcs.begin(), lcs.end());

	return { dp[n][m], lcs };
}