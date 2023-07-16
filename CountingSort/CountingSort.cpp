#include "CountingSort.hpp"

// It assumes that all values in the array is between 0 and k
// Time complexity: O(n)
std::vector<int> CountingSort::sort(const std::vector<int>& arr, size_t k) {
	size_t size = arr.size();
	std::vector<int> count(k + 1, 0);
	std::vector<int> output(size);
	// Count the occurrences of each element in the input array
	for (size_t i = 0; i < size; ++i) {
		count[arr[i]] += 1;
	}
	// Calculate the cumulative sum of the counts
	for (size_t i = 1; i <= k; ++i) {
		count[i] += count[i - 1];
	}
	// Place each element from the input array 
	// into its correct position in the output array. 
	for (size_t i = 0; i < size; ++i) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]] -= 1;
	}
	return output;
}