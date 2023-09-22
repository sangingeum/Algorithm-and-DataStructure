#include "Partition.hpp"


size_t Partition::partition(std::vector<int>& arr, size_t p, size_t r) {
	auto x = arr[r];
	size_t i = p;
	for (size_t j = p; j < r; ++j) {
		if (arr[j] < x) {
			std::swap(arr[i++], arr[j]);
		}
	}
	std::swap(arr[i], arr[r]);
	return i;
};

// Pick a random pivot
size_t RandomizedPartition::partition(std::vector<int>& arr, size_t p, size_t r) {
	size_t randomIndex = (rand() % (r - p + 1)) + p;
	std::swap(arr[randomIndex], arr[r]);
	return Partition::partition(arr, p, r);
}

// Pick a median pivot among three randomly selected pivots
size_t RandomMedianOfThreePartition::partition(std::vector<int>& arr, size_t p, size_t r) {
	size_t randomIndex1 = (rand() % (r - p + 1)) + p;
	size_t randomIndex2 = (rand() % (r - p + 1)) + p;
	size_t randomIndex3 = (rand() % (r - p + 1)) + p;
	size_t medianIndex;
	if ((arr[randomIndex1] < arr[randomIndex2] && arr[randomIndex2] < arr[randomIndex3]) ||
		(arr[randomIndex3] < arr[randomIndex2] && arr[randomIndex2] < arr[randomIndex1]))
		medianIndex = randomIndex2;
	else if ((arr[randomIndex2] < arr[randomIndex1] && arr[randomIndex1] < arr[randomIndex3]) ||
		(arr[randomIndex3] < arr[randomIndex1] && arr[randomIndex1] < arr[randomIndex2]))
		medianIndex = randomIndex1;
	else
		medianIndex = randomIndex3;
	std::swap(arr[medianIndex], arr[r]);
	return Partition::partition(arr, p, r);
}


size_t MedianOfThreePartition::partition(std::vector<int>& arr, size_t p, size_t r) {
	size_t mid = (p + r) / 2;
	size_t medianIndex;
	if ((arr[p] < arr[mid] && arr[mid] < arr[r]) || (arr[r] < arr[mid] && arr[mid] < arr[p]))
		medianIndex = mid;
	else if ((arr[mid] < arr[p] && arr[p] < arr[r]) || (arr[r] < arr[p] && arr[p] < arr[mid]))
		medianIndex = p;
	else
		medianIndex = r;
	std::swap(arr[medianIndex], arr[r]);
	return Partition::partition(arr, p, r);
}