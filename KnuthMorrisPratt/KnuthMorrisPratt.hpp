#pragma once
#include <string>
#include <vector>

// O(n + m), where n is the length of the text and m is the length of the pattern
class KnuthMorrisPratt
{
public:
	static int findString(const std::string& text, const std::string& pattern);
	static std::vector<int> findStrings(const std::string& text, const std::string& pattern);
private:
	static std::vector<int> preprocess(const std::string& pattern);
};

