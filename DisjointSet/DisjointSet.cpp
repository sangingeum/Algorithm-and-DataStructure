#include "DisjointSet.hpp"

DisjointSet::DisjointSet(size_t n) : m_size(n), parent(n), rank(n, 0) {
	for (size_t i = 0; i < n; ++i)
		parent[i] = i;
}

size_t DisjointSet::find(size_t index) {
	if (parent[index] != index)
		parent[index] = find(parent[index]); // Path compression
	return parent[index];
}

void DisjointSet::unionSets(size_t u, size_t v) {
	size_t uRoot = find(u);
	size_t vRoot = find(v);
	// If they have the same root, stop
	if (uRoot == vRoot)
		return;
	size_t uRank = rank[uRoot];
	size_t vRank = rank[vRoot];
	// Lower ranked root is attached to the higher ranked root
	if (uRank < vRank) {
		parent[uRoot] = vRoot;
	}
	else if (uRank > vRank) {
		parent[vRoot] = uRoot;
	}
	else {
		// If they have the same rank,
		// attach one to the other and
		// increment the rank of the upper root
		parent[vRoot] = uRoot;
		rank[uRoot]++;
	}
}
size_t DisjointSet::size() {
	return m_size;
}