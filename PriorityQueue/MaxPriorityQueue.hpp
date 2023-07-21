#pragma once
#include <vector>
#include <utility>

template<class T>
class MaxPriorityQueue
{
public:
	// Time complexity: O(1)
	// Peeks an element with the highest priority 
	std::pair<float, T> front();
	// Time complexity: O(log(n))
	// Pops an element with the highest priority 
	void pop();
	// Time complexity: O(1)
	// Checks if the queue is empty
	bool empty() const;
	// Time complexity: O(log(n))
	// Insert an element with priority p to the queue
	void push(float p, T element);

private:
	std::vector<std::pair<float, T>> m_array;
	// Time complexity: O(log(n))
	// Maintains the max heap property for a node at the given index
	void heapify(size_t index);

	// Time complexity: O(1)
	// Returns the index of the left child, the right child, or the parent
	static inline size_t left(size_t parent);
	static inline size_t right(size_t parent);
	static inline size_t parent(size_t child);
};


template<class T>
std::pair<float, T> MaxPriorityQueue<T>::front() {
	return m_array[0];
}

template<class T>
void MaxPriorityQueue<T>::pop() {
	std::swap(m_array.front(), m_array.back());
	m_array.pop_back();
	if(!empty())
		heapify(0);
}

template<class T>
bool MaxPriorityQueue<T>::empty() const {
	return m_array.empty();
}

template<class T>
void MaxPriorityQueue<T>::push(float p, T element) {
	m_array.emplace_back(p, element);
	size_t curIndex = m_array.size() - 1;
	while (curIndex != 0) {
		size_t parentIndex = parent(curIndex);
		if (m_array[parentIndex].first < p) {
			std::swap(m_array[parentIndex], m_array[curIndex]);
		}
		curIndex = parentIndex;
	}
}
template<class T>
void MaxPriorityQueue<T>::heapify(size_t index) {
	size_t heapSize = m_array.size() - 1;
	auto curP = m_array[index].first;
	auto leftIndex = left(index);
	auto rightIndex = right(index);
	size_t largest = index;
	if (leftIndex <= heapSize && m_array[leftIndex].first > curP)
		largest = leftIndex;
	if (rightIndex <= heapSize && m_array[rightIndex].first > m_array[largest].first)
		largest = rightIndex;
	if (largest != index) {
		std::swap(m_array[index], m_array[largest]);
		heapify(largest);
	}
}
template<class T>
inline size_t MaxPriorityQueue<T>::left(size_t parent) {
	return (parent << 1) + 1;
}
template<class T>
inline size_t MaxPriorityQueue<T>::right(size_t parent) {
	return (parent << 1) + 2;
}
template<class T>
inline size_t MaxPriorityQueue<T>::parent(size_t child) {
	return (child - 1) >> 1;
}