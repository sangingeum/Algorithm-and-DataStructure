#include "IntervalScheduling.hpp"
#include <iostream>

int main() {
	std::vector<std::pair<int, int>> intervals{
		{1, 4}, {3, 4}, {0, 6}, {5, 7}, {3, 8}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14} };
	size_t count = IntervalScheduling::solve(intervals);
	std::cout << count << "\n"; // 4  (1,4), (5,7), (8,11), (12,14)
	return 0;
}