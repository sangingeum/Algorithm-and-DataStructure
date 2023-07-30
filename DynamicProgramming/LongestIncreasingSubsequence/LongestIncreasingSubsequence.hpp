#pragma once
#include <vector>
#include <algorithm>
class LongestIncreasingSubsequence
{
public:
	// Space O(n)
	// Time O(nlog(n))
	// Returns a pair of the length of the LIS and the LIS of the given array. 
	static std::pair<size_t, std::vector<float>> solve(const std::vector<float>& nums) {
		size_t n = nums.size();

		// Records what is in front of i 
		// front[i] == n means nothing is in front of it.
		std::vector<size_t> front(n, n); 
		
		// Keeps track of intermediate results
		std::vector<size_t> lisIndices;
		std::vector<float> lis; 
		lis.emplace_back(nums[0]);
		lisIndices.emplace_back(0);
		size_t lastIndex = 0;

		for (size_t i = 1; i < n; ++i) {
			auto cur = nums[i];
			
			if (lis.back() < cur) {
				front[i] = lisIndices.back();
				lisIndices.emplace_back(i);
				lis.emplace_back(cur);
				lastIndex = i;
			}
			else {
				size_t pos = std::lower_bound(lis.begin(), lis.end(), cur) - lis.begin();
				lis[pos] = cur;
				lisIndices[pos] = i;
				if (pos > 0)
					front[i] = lisIndices[pos - 1];
			}
		}

		std::vector<float> ans;
		while (lastIndex < n) {
			ans.emplace_back(nums[lastIndex]);
			lastIndex = front[lastIndex];
		}
		std::reverse(ans.begin(), ans.end());
		return { lis.size(), ans };
	}
};

