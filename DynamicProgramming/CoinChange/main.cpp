#include "CoinChange.hpp"
#include <iostream>
int main() {

	std::cout << CoinChange::solve(4, { 1,2,3 }) << "\n"; // 4
	std::cout << CoinChange::solve(10, { 2,5,3,6 }) << "\n"; // 5
	std::cout << CoinChange::solve(13, { 5,2,4 }) << "\n"; // 3

	return 0;
}