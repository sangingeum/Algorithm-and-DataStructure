#include "TopologicalSort.hpp"

std::vector<size_t> TopologicalSort::sort(AdjacencyListGraph<Vertex>& graph) {
	size_t numVertices = graph.getNumVertices();
	// Create a stack that keeps track of what to search next
	std::stack<size_t> toSearch;
	std::vector<size_t> sorted;

	for (size_t i = 0; i < numVertices; ++i) {
		// If the current vertex is not visited, push it to the statck
		if (!graph.getVertexAttribute(i).visited) {
			graph.getVertexAttribute(i).visited = true;
			toSearch.push(i);

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
	return sorted;
}