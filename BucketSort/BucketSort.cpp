#include "BucketSort.hpp"

// This algorithm assumes that the values in the vector
// are in [0, 1) and from a uniform dist. 
// Average Time Complexity: O(n) as long as the assumption holds.
void BucketSort::sort(std::vector<float>& arr, size_t numBucket) {
	// Create buckets
	std::vector<std::vector<float>> buckets(numBucket, std::vector<float>());
	// Append each value to the correct bucket
	size_t size = arr.size();
	for (size_t i = 0; i < size; ++i) {
		buckets[std::floorf(arr[i] * numBucket)].push_back(arr[i]);
	}
	// Sort the buckets and concatenate them
	std::vector<float> output;
	output.reserve(size);
	for (auto& bucket : buckets) {
		std::sort(bucket.begin(), bucket.end());
		output.insert(output.end(), bucket.begin(), bucket.end());
	}
	arr = std::move(output);
}