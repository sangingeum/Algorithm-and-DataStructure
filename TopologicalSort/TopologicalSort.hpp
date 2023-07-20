#pragma once
#include <vector>
#include <stack>
#include "AdjacencyListGraph.hpp" // This header file is defined in the Graph folder

template <class Vertex>
class TopologicalSort
{
public:
	static std::vector<size_t> sort(AdjacencyListGraph<Vertex>& graph);
};

// Time Complexity: O(|V|+|E|)
// Topologically sort the given graph and return a sorted vector of vertices
// For every directed edge (u, v), vertex u will appear before vertex v.
template <class Vertex>
std::vector<size_t> TopologicalSort<Vertex>::TopologicalSort::sort(AdjacencyListGraph<Vertex>& graph) {
	size_t numVertices = graph.getNumVertices();
	// Create a stack that keeps track of what to search next
	std::stack<size_t> toSearch;
	// Create a vector for sorted vertices
	std::vector<size_t> sorted;
	sorted.reserve(numVertices);
	// Create a visited vector
	std::vector<bool> visited(numVertices, false);

	for (size_t i = 0; i < numVertices; ++i) {
		// If the current vertex is not visited, push it to the statck
		if (!visited[i]) {
			visited[i] = true;
			toSearch.push(i);
			// Run the DFS algorithm using the stack
			while (!toSearch.empty()) {
				auto cur = toSearch.top();
				auto& adj = graph.getAdjacent(cur);
				bool noValidAdj = true;
				for (size_t next : adj) {
					if (!visited[next]) {
						visited[next] = true;
						toSearch.push(next);
						noValidAdj = false;
						break; // Break to explore the newly found neighbor immediately
					}
				}
				// No more exploring
				if (noValidAdj) {
					toSearch.pop();
					sorted.push_back(cur);
				}
			}
		}
	}
	// Reverse the order
	return std::vector<size_t>(sorted.rbegin(), sorted.rend());
}