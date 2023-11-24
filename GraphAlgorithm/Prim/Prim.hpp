#pragma once
#include "FibonacciHeap.hpp"
#include "AdjacencyListGraph.hpp"
#include <limits>


/* Example Vertex type
struct Vertex {
	float key{std::numeric_limits<float>::infinity()};
	size_t parent{std::numeric_limits<size_t>::max()};
};
*/

template <class Vertex>
class Prim
{
public:
	// Find an MST of the given 'undirected' graph
	// This function does not check if the given graph is directed or not
	static AdjacencyListGraph<Vertex> minimumSpanningTree(AdjacencyListGraph<Vertex>& graph);
private:
	static void addEdgesToQueue(AdjacencyListGraph<Vertex>& graph, size_t vertex, FibonacciHeap<std::pair<size_t, size_t>>& queue);
};


// Find an MST of the given 'undirected' graph
// This function does not check if the given graph is directed or not
template <class Vertex>
AdjacencyListGraph<Vertex> Prim<Vertex>::minimumSpanningTree(AdjacencyListGraph<Vertex>& graph) {
	size_t numVertices = graph.getNumVertices();
	size_t verticesInTree = 0;
	// Make a FibonacciHeap that stores edges which are sorted based on their key
	FibonacciHeap<std::pair<size_t, size_t>> edgeQ;
	// Every vertex should be included in the tree only once
	std::vector<bool> isIntree(numVertices, false);
	// Initialize the queue (assumes the graph has at least one vertex)
	addEdgesToQueue(graph, 0, edgeQ);
	isIntree[0] = true;
	++verticesInTree;
	// Create an empty MST graph
	AdjacencyListGraph<Vertex> mst(numVertices);
	// Perform the Prim's algorithm until all vertices are included
	while (!edgeQ.empty() && verticesInTree < numVertices) {
		// Extract an edge with the minimum key
		auto [edge, key] = edgeQ.topWithKey(); edgeQ.pop();
		auto [u, v] = std::move(edge);
		if (!isIntree[v]) { // Already in the tree. Skip.
			isIntree[v] = true;
			addEdgesToQueue(graph, v, edgeQ);
			++verticesInTree;
			// Add the edge to the MST
			mst.addUndirectedEdge(u, v);
		}
	}

	return mst;
}


template<class Vertex>
inline void Prim<Vertex>::addEdgesToQueue(AdjacencyListGraph<Vertex>& graph, size_t vertex, FibonacciHeap<std::pair<size_t, size_t>>& queue)
{
	auto& adjs = graph.getAdjacent(vertex);
	auto& edgeAtts = graph.getEdgeAttributes(vertex);
	size_t adjSize = adjs.size();
	for (size_t i = 0; i < adjSize; ++i) {
		size_t target = adjs[i];
		float weight = edgeAtts[i];
		queue.push(weight, { vertex, target });
	}

}
