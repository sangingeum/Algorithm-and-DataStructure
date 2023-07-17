#pragma once
#include <vector>

template <class P>
class QuickSort
{
public:
	// Time Complexity: O(nlog(n)) on average
	void sort(std::vector<int>& arr);
private:
	// Partioning strategy
	P m_strategy{};
	// Tail-recursive quick sort
	void sort(std::vector<int>& arr, size_t p, size_t r);
};

template <class P>
void QuickSort<P>::sort(std::vector<int>& arr) {
	sort(arr, 0, arr.size() - 1);
}
template <class P>
void QuickSort<P>::sort(std::vector<int>& arr, size_t p, size_t r) {
	while (p < r) {
		size_t q = m_strategy.partition(arr, p, r);
		if (q != 0) {
			sort(arr, p, q - 1);
		}
		p = q + 1;
	}
}