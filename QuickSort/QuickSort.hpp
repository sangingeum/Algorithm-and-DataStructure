#pragma once
#include "Partition.hpp"
#include <memory>
#include <vector>

class QuickSort
{
public:
	QuickSort(std::unique_ptr<Partition>&& strategy)
		: m_strategy(std::move(strategy))
	{}
	void sort(std::vector<int>& arr) {
		sort(arr, 0, arr.size() - 1);
	}
private:
	// Partioning strategy
	std::unique_ptr<Partition> m_strategy;
	// Tail-recursive quick sort
	void sort(std::vector<int>& arr, size_t p, size_t r) {
		while (p < r) {
			size_t q = m_strategy->partition(arr, p, r);
			if (q != 0) {
				sort(arr, p, q - 1);
			}
			p = q + 1;
		}
	}
};

