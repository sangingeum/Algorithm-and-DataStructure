#pragma once
#include <vector>
#include <algorithm>

class IntervalScheduling
{
public:
	// Caution: The given array will be sorted in this method
	template<class T>
	static size_t solve(std::vector<std::pair<T, T>>& intervals) {
		// Sort intervals based on their end points
		std::sort(intervals.begin(), intervals.end(),
			[](const std::pair<T, T>& a, const std::pair<T, T>& b) {
				if (a.second < b.second) {
					return true;
				}
				else if (a.second == b.second) {
					return a.first < b.first;
				}
				return false;
			});

		size_t count = 0;
		size_t n = intervals.size();
		T curEndPoint = 0;

		for (size_t i = 0; i < n; ++i) {
			const auto& cur = intervals[i];
			if (curEndPoint <= cur.first) {
				curEndPoint = cur.second;
				++count;
			}
		}
		return count;
	}
};
