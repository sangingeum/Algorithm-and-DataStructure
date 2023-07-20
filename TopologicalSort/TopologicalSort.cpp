#include "TopologicalSort.hpp"

// Time Complexity: O(|V|+|E|)
// Topologically sort the given graph and return a sorted vector of vertices
// For every directed edge (u, v), vertex u will appear before vertex v.
std::vector<size_t> TopologicalSort::sort(AdjacencyListGraph<Vertex>& graph) {
	size_t numVertices = graph.getNumVertices();
	// Create a stack that keeps track of what to search next
	std::stack<size_t> toSearch;
	// Create a vector for sorted vertices
	std::vector<size_t> sorted;
	sorted.reserve(numVertices);
	
	for (size_t i = 0; i < numVertices; ++i) {
		// If the current vertex is not visited, push it to the statck
		if (!graph.getVertexAttribute(i).visited) {
			graph.getVertexAttribute(i).visited = true;
			toSearch.push(i);
			// Run the DFS algorithm using the stack
			while (!toSearch.empty()) {
				auto cur = toSearch.top();
				auto& curAtt = graph.getVertexAttribute(cur);
				auto& adj = graph.getAdjacent(cur);
				bool noValidAdj = true;
				for (size_t next : adj) {
					auto& att = graph.getVertexAttribute(next);
					if (!att.visited) {
						att.visited = true;
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