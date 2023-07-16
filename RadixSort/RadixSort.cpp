#include "RadixSort.hpp"

// Radix Sort
// Time Complexity: O(d*n)
// Sorts the given array by applying the stable counting sort d times,
// where d is the maximum number of digits among the elements in the vector
void RadixSort::sort(std::vector<int>& arr) {
	size_t size = arr.size();
	std::vector<int> digits(size);
	// Iterate the counting sort d times
	for (size_t exp = 0; ; ++exp) {
		bool isOver = true;
		long long divider = std::powl(10, exp);
		std::vector<int> count(10, 0);
		std::vector<int> output(size);
		for (size_t i = 0; i < size; ++i) {
			int currentDigit = (arr[i] / divider) % 10;
			digits[i] = currentDigit;
			if (currentDigit != 0) {
				isOver = false;
			}
			count[currentDigit] += 1;
		}
		// If all of the currentDigits are 0, break
		if (isOver) {
			break;
		}
		// Calculate the cummulative sum of the counts
		for (size_t i = 1; i < 10; ++i) {
			count[i] += count[i - 1];
		}
		for (size_t i = size - 1; i < size; --i) {
			int currentDigit = digits[i];
			output[count[currentDigit] - 1] = arr[i];
			count[currentDigit] -= 1;
		}
		arr = std::move(output);
	}
}