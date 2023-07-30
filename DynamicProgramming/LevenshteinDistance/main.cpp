#include "Levenshtein.hpp"
#include <iostream>
int main() {
	std::cout << Levenshtein::distance("taken", "fishcake") << "\n";
	std::cout << Levenshtein::distance("piza", "pizzaa") << "\n";
	std::cout << Levenshtein::distance("pineapple", "apple") << "\n";
	std::cout << Levenshtein::distance("johnber", "johnson") << "\n";
	std::cout << Levenshtein::distance("village", "willy") << "\n";
	std::cout << Levenshtein::distance("waccine", "vaccine") << "\n";
	return 0;
}