#include "Levenshtein.hpp"
#include <iostream>
int main() {
	std::cout << Levenshtein::distance("taken", "fishcake") << "\n"; // 6
	std::cout << Levenshtein::distance("piza", "pizzaa") << "\n"; // 2
	std::cout << Levenshtein::distance("pineapple", "apple") << "\n"; // 4
	std::cout << Levenshtein::distance("johnber", "johnson") << "\n"; // 3
	std::cout << Levenshtein::distance("waccine", "vaccine") << "\n"; // 1
	std::cout << Levenshtein::distance("aaaardvark", "aardvark") << "\n"; // 2
	std::cout << Levenshtein::distance("kitten", "sitting") << "\n"; // 3
	std::cout << Levenshtein::distance("flaw", "lawn") << "\n"; // 2
	std::cout << Levenshtein::distance("abcdef", "azced") << "\n"; // 3
	return 0;
}