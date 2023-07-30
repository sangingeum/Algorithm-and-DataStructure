#pragma once
#include "AdjacencyListGraph.hpp"
#include "DisjointSet.hpp"
#include <vector>
#include <algorithm>
#include <tuple>


template <class Vertex>
class Kruskal
{
	using Edge = typename std::tuple<size_t, size_t, float>;
public:
	static AdjacencyListGraph<Vertex> minimumSpanningTree(AdjacencyListGraph<Vertex>& graph);
};

// Return a minimum spanning tree of the given 'undirected' graph
// This method does not check whether the given graph is directed or not
template <class Vertex>
AdjacencyListGraph<Vertex> Kruskal<Vertex>::minimumSpanningTree(AdjacencyListGraph<Vertex>& graph) {
	// Make a new graph to store a minimum spanning tree (MST)
	size_t numVertices = graph.getNumVertices();
	AdjacencyListGraph<Vertex> mst(numVertices);

	// Extract all edges from the input graph
	std::vector<Edge> edges;
	for (size_t i = 0; i < numVertices; ++i) {
		auto& adj = graph.getAdjacent(i);
		auto& weights = graph.getEdgeAttributes(i);
		size_t adjSize = adj.size();
		for (size_t j = 0; j < adjSize; ++j) {
			edges.push_back({ i, adj[j], weights[j] });
		}
	}

	// Sort the edges in increasing order based on their weights
	std::sort(edges.begin(), edges.end(), [](const Edge& edgeA, const Edge& edgeB) {
		return std::get<float>(edgeA) < std::get<float>(edgeB);
		});

	// Include light edges
	// Use the disjoint set data structure to check if u and v are in the same set
	DisjointSet set(numVertices);
	for (auto& [u, v, w] : edges) {
		if (set.find(u) != set.find(v)) {
			set.unionSets(u, v);
			mst.addUndirectedEdge(u, v, w);
		}
	}

	return mst;
}