#pragma once
#include <vector>

template <class P>
class QuickSelect
{
public:
	// Given a vector and an integer k, return the kth element in the vector
	int select(std::vector<int>& vec, size_t k) {
		return select(vec, k, 0, vec.size() - 1);
	}

private:
	P m_strategy{};
	int select(std::vector<int>& vec, size_t k, size_t start, size_t end) {
		size_t p = m_strategy.partition(vec, start, end);
		if (p == k)
			return vec[p];
		else if (p < k)
			return select(vec, k, p + 1, end);
		else
			return select(vec, k, start, p - 1);
	}
};

