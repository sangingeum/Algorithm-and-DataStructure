#pragma once
#include <vector>
#include <cmath>
class RadixSort
{
public:
	// Radix Sort
	// Time Complexity: O(d*n)
	// Sorts the given array by applying the stable counting sort d times,
	// where d is the maximum number of digits among the elements in the vector
	static void sort(std::vector<int>& arr);
private:

};

