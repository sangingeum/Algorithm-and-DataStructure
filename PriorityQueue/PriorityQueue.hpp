#pragma once
#include <vector>
#include <utility>
#include <queue>


template<class T>
class PriorityQueue
{
public:
	std::pair<size_t, T> front() const;
	std::pair<size_t, T> pop();
	bool empty() const;
	void push(size_t p, T element);
private:
	std::vector<std::pair<int, T>> m_array;
	void heapify(size_t index);
	static inline size_t left(size_t parent);
	static inline size_t right(size_t parent);
	static inline size_t parent(size_t child);
};


template<class T>
std::pair<size_t, T> PriorityQueue<T>::front() const {
	return m_array[0];
}

template<class T>
std::pair<size_t, T> PriorityQueue<T>::pop() {
	auto toPop = m_array.front();
	std::swap(m_array.front(), m_array.back());
	m_array.pop_back();
	if (!empty())
		heapify(0);
	return toPop;
}

template<class T>
bool PriorityQueue<T>::empty() const {
	return m_array.empty();
}

template<class T>
void PriorityQueue<T>::push(size_t p, T element) {
	m_array.push_back({ p, element });
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
void PriorityQueue<T>::heapify(size_t index) {
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
inline size_t PriorityQueue<T>::left(size_t parent) {
	return (parent << 1) + 1;
}
template<class T>
inline size_t PriorityQueue<T>::right(size_t parent) {
	return (parent << 1) + 2;
}
template<class T>
inline size_t PriorityQueue<T>::parent(size_t child) {
	return (child - 1) >> 1;
}