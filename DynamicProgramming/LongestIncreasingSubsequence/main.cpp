#include "LongestIncreasingSubsequence.hpp"
#include <iostream>

void testLIS(const std::vector<float>& nums) {
	auto [size, vec] = LongestIncreasingSubsequence::solve(nums);
	std::cout << size << " [ ";
	for (auto num : vec) { std::cout << num << " "; }
	std::cout << "]\n";
}

int main() {

	testLIS({ 1,5,2,7,3 }); // 3 [ 1 2 7 ]
	testLIS({ 13,1,3,4,8,4 }); // 4 [ 1 3 4 8 ]
	testLIS({ 13,1,3,4,8,19,17,8,0,20,14 }); // 6 [ 1 3 4 8 17 20 ]
	testLIS({ 50,3,10,7,40,80 }); // 4 [ 3 7 40 80 ]
	testLIS({ 1,2,3,4,5,4,3,2,1 }); // 5 [ 1 2 3 4 5 ]

	return 0;
}