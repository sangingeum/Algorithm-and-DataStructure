#pragma once
#include <vector>
#include <functional>
#include "Merger.hpp"

template <class Merger, class T = typename Merger::ValueType>
class SegmentTree
{
private:
	Merger m_merger{};
	std::function<T(T, T)> m_mergeFunction;
	size_t m_size;
	std::vector<T> m_tree;
public:
	SegmentTree(const std::vector<T>& nums);
	T query(size_t from, size_t to);
	void update(size_t index, T value);
private:
	static inline size_t left(size_t parent);
	static inline size_t right(size_t parent);
	static inline size_t parent(size_t child);
};


// O(n)
template <class Merger, class T>
SegmentTree<Merger, T>::SegmentTree(const std::vector<T>& nums)
	: m_mergeFunction(m_merger.getMerger()), m_size(nums.size()), m_tree(m_size)
{
	m_tree.insert(m_tree.begin() + m_size, nums.begin(), nums.end());
	for (size_t i = m_size - 1; i >= 1; --i) {
		m_tree[i] = m_mergeFunction(m_tree[left(i)], m_tree[right(i)]);
	}
}


// O(log(n))
// Get the aggregated value from the given range [from, to)
template <class Merger, class T>
T SegmentTree<Merger, T>::query(size_t from, size_t to) {
	from += m_size;
	to += m_size;
	T result = m_merger.getInitialValue();

	while (from < to) {
		if (from % 2 == 1) {
			result = m_mergeFunction(result, m_tree[from]);
			from++;
		}
		if (to % 2 == 1) {
			to--;
			result = m_mergeFunction(result, m_tree[to]);
		}
		from /= 2;
		to /= 2;
	}
	return result;
}


// O(log(n))
template <class Merger, class T>
void SegmentTree<Merger, T>::update(size_t index, T value) {
	index += m_size;
	m_tree[index] = value;
	while (index > 1) {
		index = parent(index);
		m_tree[index] = m_mergeFunction(m_tree[left(index)], m_tree[right(index)]);
	}
}

template <class Merger, class T>
size_t SegmentTree<Merger, T>::left(size_t parent) {
	return parent << 1;
}

template <class Merger, class T>
size_t SegmentTree<Merger, T>::right(size_t parent) {
	return (parent << 1) + 1;
}

template <class Merger, class T>
size_t SegmentTree<Merger, T>::parent(size_t child) {
	return child >> 1;
}