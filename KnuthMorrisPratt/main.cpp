#include "KnuthMorrisPratt.hpp"
#include <iostream>

// Print indices at which the given pattern appears in the text
void testPatternMatching(const std::string& text, const std::string& pattern) {
	std::cout << "[ ";
	for (auto index : KnuthMorrisPratt::findStrings(text, pattern)) {
		std::cout << index << " ";
	}
	std::cout << "]\n";
}


int main() {

	testPatternMatching("abcdefg", "xyz"); // [ ]
	testPatternMatching("aaaaa", "a"); // [ 0 1 2 3 4 ]
	testPatternMatching("abcabcabcabcabcabcabc", "abc"); // [ 0 3 6 9 12 15 18 ]
	testPatternMatching("banana", "na"); // [ 2 4 ]
	testPatternMatching("The quick brown fox jumps over the lazy dog.", "fox"); // [ 16 ]
	testPatternMatching("testPatternMatching", "tern"); // [ 7 ]

	return 0;
}