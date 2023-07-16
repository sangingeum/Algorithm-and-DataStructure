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
	// Time Complexity: O(nlog(n)) on average
	void sort(std::vector<int>& arr);
private:
	// Partioning strategy
	std::unique_ptr<Partition> m_strategy;
	// Tail-recursive quick sort
	void sort(std::vector<int>& arr, size_t p, size_t r);
};

