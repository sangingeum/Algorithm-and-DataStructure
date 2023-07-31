#pragma once
#include <vector>
#include <string>
class LongestCommonSubsequence
{
public:
	// Space O(n*m)
	// Time O(n*m)
	// Given two strings, returns the length of the LCS of them
	static size_t solve(const std::string& strA, const std::string& strB);
	// Space O(n*m)
	// Time O(n*m)
	// Given two strings, returns the length of the LCS and the LCS of them
	static std::pair<size_t, std::string> solveAndTrace(const std::string& strA, const std::string& strB);
};

