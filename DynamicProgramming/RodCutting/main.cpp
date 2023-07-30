#include "RodCutting.hpp"
#include <iostream>
#include <format>

void testRodCutting(const std::vector<float>& prices) {
	auto [opt, trace] = RodCutting::solveAndTrace(prices);
	std::cout << std::format("Opt: {}, [ ", opt);
	for (auto cut : trace) { std::cout << cut << " "; }
	std::cout << "]\n";
}


int main() {
	
	testRodCutting({ 1, 3, 4, 5, 7, 9, 10, 11 }); // Opt: 12, [ 2 2 2 2 ]
	testRodCutting({ 3, 5, 8, 10, 14, 15, }); //Opt: 18, [ 1 1 1 1 1 1 ]
	testRodCutting({ 2, 8, 11, 14, 15, 19, 21 }); // Opt: 27, [ 2 2 3 ]
	testRodCutting({ 1, 5, 8, 9, 10, 17, 17, 20 }); // Opt: 22, [ 2 6 ]
	testRodCutting({ 3, 5, 8, 9, 10, 17, 17, 20 }); // Opt: 24, [ 1 1 1 1 1 1 1 1 ]
	testRodCutting({ 1, 1, 1, 1 }); // Opt: 4, [ 1 1 1 1 ]
	testRodCutting({ 1, 1, 1, 100 }); // Opt: 100, [ 4 ]

	return 0;
}