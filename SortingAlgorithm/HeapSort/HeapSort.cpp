#include "HeapSort.hpp"

// O(nlog(n))
void HeapSort::maxHeapSort(std::vector<int>& arr) {
	buildMaxHeap(arr);
	size_t heapSize = arr.size() - 1;
	for (size_t i = heapSize; i >= 1; --i) {
		std::swap(arr[i], arr[0]);
		maxHeapify(arr, 0, i - 1);
	}
}
// O(nlog(n))
void HeapSort::minHeapSort(std::vector<int>& arr) {
	buildMinHeap(arr);
	size_t heapSize = arr.size() - 1;
	for (size_t i = heapSize; i >= 1; --i) {
		std::swap(arr[i], arr[0]);
		minHeapify(arr, 0, i - 1);
	}
}


// O(log(heapSize))
void HeapSort::maxHeapify(std::vector<int>& arr, size_t index, size_t heapSize) {
	auto curVal = arr[index];
	auto leftIndex = left(index);
	auto rightIndex = right(index);
	size_t largest = index;
	if (leftIndex <= heapSize && arr[leftIndex] > curVal)
		largest = leftIndex;
	if (rightIndex <= heapSize && arr[rightIndex] > arr[largest])
		largest = rightIndex;
	if (largest != index) {
		std::swap(arr[index], arr[largest]);
		maxHeapify(arr, largest, heapSize);
	}
}
// O(n)
void HeapSort::buildMaxHeap(std::vector<int>& arr) {
	size_t heapSize = arr.size() - 1;
	size_t lastNonLeafIndex = parent(heapSize);
	for (size_t i = lastNonLeafIndex;; --i) {
		maxHeapify(arr, i, heapSize);
		if (i == 0)
			break;
	}
}

// O(log(heapSize))
void HeapSort::minHeapify(std::vector<int>& arr, size_t index, size_t heapSize) {
	auto curVal = arr[index];
	auto leftIndex = left(index);
	auto rightIndex = right(index);
	size_t lowest = index;
	if (leftIndex <= heapSize && arr[leftIndex] < curVal)
		lowest = leftIndex;
	if (rightIndex <= heapSize && arr[rightIndex] < arr[lowest])
		lowest = rightIndex;
	if (lowest != index) {
		std::swap(arr[index], arr[lowest]);
		minHeapify(arr, lowest, heapSize);
	}
}
// O(n)
void HeapSort::buildMinHeap(std::vector<int>& arr) {
	size_t heapSize = arr.size() - 1;
	size_t lastNonLeafIndex = parent(heapSize);
	for (size_t i = lastNonLeafIndex;; --i) {
		minHeapify(arr, i, heapSize);
		if (i == 0)
			break;
	}
}

inline size_t HeapSort::left(size_t parent) {
	return (parent << 1) + 1;
}
inline size_t HeapSort::right(size_t parent) {
	return (parent << 1) + 2;
}
inline size_t HeapSort::parent(size_t child) {
	return (child - 1) >> 1;
}