#include "QuickSort.hpp"
void QuickSort::sort(std::vector<int>& arr) {
	sort(arr, 0, arr.size() - 1);
}

void QuickSort::sort(std::vector<int>& arr, size_t p, size_t r) {
	while (p < r) {
		size_t q = m_strategy->partition(arr, p, r);
		if (q != 0) {
			sort(arr, p, q - 1);
		}
		p = q + 1;
	}
}