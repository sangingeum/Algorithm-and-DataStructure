#pragma once
#include <vector>

class HeapSort {

public:
	// Time complexity: O(nlog(n))
	// Sorts the given array
	static void maxHeapSort(std::vector<int>& arr);
	static void minHeapSort(std::vector<int>& arr);
private:
	// Time complexity: O(1)
	// Returns the index of the left child, the right child, or the parent
	static inline size_t left(size_t parent);
	static inline size_t right(size_t parent);
	static inline size_t parent(size_t child);

	// Time complexity: O(log(heapSize))
	// Maintains the heap property for a node at the given index
	static void maxHeapify(std::vector<int>& arr, size_t index, size_t heapSize);
	static void minHeapify(std::vector<int>& arr, size_t index, size_t heapSize);
	// Time complexity: O(n)
	// Converts the given array into a heap
	static void buildMaxHeap(std::vector<int>& arr);
	static void buildMinHeap(std::vector<int>& arr);
};


