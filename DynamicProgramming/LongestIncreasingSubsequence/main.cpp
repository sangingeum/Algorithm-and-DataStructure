#include "LongestIncreasingSubsequence.hpp"
#include <iostream>

void testLIS(const std::vector<float>& nums) {
	auto [size, vec] = LongestIncreasingSubsequence::solve(nums);
	std::cout << size << "\n[ ";
	for (auto num : vec) { std::cout << num << " "; }
	std::cout << "]\n";
}

int main() {
	testLIS({ 1,5,2,7,3 });
	testLIS({ 13,1,3,4,8,4 });
	testLIS({ 13,1,3,4,8,19,17,8,0,20,14 });
	testLIS({ 50, 3, 10, 7, 40, 80 });




	return 0;
}