#pragma once
#include <vector>

class HeapSort {

public:
	// O(nlog(n))
	static void maxHeapSort(std::vector<int>& arr);
	// O(nlog(n))
	static void minHeapSort(std::vector<int>& arr);
private:
	static inline size_t left(size_t parent) {
		return (parent << 1) + 1;
	}
	static inline size_t right(size_t parent) {
		return (parent << 1) + 2;
	}
	static inline size_t parent(size_t child) {
		return (child - 1) >> 1;
	}
	// O(log(heapSize))
	static void maxHeapify(std::vector<int>& arr, size_t index, size_t heapSize);
	// O(n)
	static void buildMaxHeap(std::vector<int>& arr);
	// O(log(heapSize))
	static void minHeapify(std::vector<int>& arr, size_t index, size_t heapSize);
	// O(n)
	static void buildMinHeap(std::vector<int>& arr);
	
};


