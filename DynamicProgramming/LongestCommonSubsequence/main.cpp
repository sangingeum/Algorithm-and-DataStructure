#include "LongestCommonSubsequence.hpp"
#include <iostream>
#include <format>

void testLCS(const std::string& strA, const std::string& strB) {
	auto [size, lcs] = LongestCommonSubsequence::solveAndTrace(strA, strB);
	std::cout << std::format("LCS Length: {}, LCS: {}\n", size, lcs);
}

int main() {

	testLCS("ABCDGH", "AEDFHR"); // LCS Length: 3, LCS: ADH
	testLCS("AGGTAB", "GXTXAYB"); // LCS Length: 4, LCS: GTAB
	testLCS("BD", "ABCD"); // LCS Length: 2, LCS: BD
	testLCS("abcde", "ace"); // LCS Length: 3, LCS: ace
	testLCS("abc", "abc"); // LCS Length: 3, LCS: abc
	testLCS("abc", "def"); // LCS Length: 0, LCS:

}