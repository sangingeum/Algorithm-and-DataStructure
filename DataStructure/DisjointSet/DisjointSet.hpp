#pragma once
#include <vector>

class DisjointSet
{
public:
	DisjointSet(size_t n);
	size_t find(size_t index);
	void unionSets(size_t u, size_t v);
	size_t size();

private:
	size_t m_size;
	std::vector<size_t> parent;
	std::vector<size_t> rank;
};


