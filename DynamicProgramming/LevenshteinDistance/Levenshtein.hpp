#pragma once
#include <vector>
#include <string>
class Levenshtein
{
public:
	// Space O(MIN(strA.size(), strB.size()))
	// Time O(strA.size() * strB.size())
	// Given two strings, returns the Levenshtein distance between them
	static size_t distance(const std::string& strA, const std::string& strB);
private:
	// Private helper method
	static size_t distance_(const std::string& strA, const std::string& strB);
};

