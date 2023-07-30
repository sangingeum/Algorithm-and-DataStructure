#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
class BucketSort
{
public:
	// This algorithm assumes that the values in the vector
	// are in [0, 1) and from a uniform dist. 
	// Average Time Complexity: O(n) as long as the assumption holds.
	static void sort(std::vector<float>& arr, size_t numBucket);

};

