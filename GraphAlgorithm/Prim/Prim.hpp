#pragma once
#include "BinaryMinHeap.hpp"
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
	static void initialize(AdjacencyListGraph<Vertex>& graph);
};


// Find an MST of the given 'undirected' graph
// This function does not check if the given graph is directed or not
template <class Vertex>
AdjacencyListGraph<Vertex> Prim<Vertex>::minimumSpanningTree(AdjacencyListGraph<Vertex>& graph) {
	size_t numVertices = graph.getNumVertices();
	// Initialize the graph
	initialize(graph);

	// Make a BinaryMinHeap that stores vertices based on their keys
	// The initial key value for all vertices is set to infinity
	BinaryMinHeap<size_t> vertexQ;
	for (size_t i = 0; i < numVertices; ++i) {
		vertexQ.push(std::numeric_limits<float>::max(), i);
	}

	// Every vertex should be visited only once
	std::vector<bool> visited(numVertices, false);
	// Perform the Prim's algorithm until all vertices are visited
	while (!vertexQ.empty()) {
		// Extract a vertex with the minimum key
		auto [key, cur] = vertexQ.front(); vertexQ.pop();
		if (!visited[cur]) {
			visited[cur] = true;
			auto& adjs = graph.getAdjacent(cur);
			auto& edgeAtts = graph.getEdgeAttributes(cur);
			size_t adjSize = adjs.size();
			for (size_t i = 0; i < adjSize; ++i) {
				size_t target = adjs[i];
				float weight = edgeAtts[i];
				auto& targetAtt = graph.getVertexAttribute(target);
				if (!visited[target] && weight < targetAtt.key) {
					targetAtt.key = weight;
					targetAtt.parent = cur;
					// Instead of updating the key of the vertex in the queue,
					// Insert the same vertex with a new key to reflect the change
					vertexQ.push(targetAtt.key, target);
				}
			}
		}
	}

	// Add edges to construct the MST based on the vertex attributes
	AdjacencyListGraph<Vertex> mst(numVertices);
	auto& atts = graph.getVertexAttributes();
	for (size_t i = 0; i < numVertices; ++i) {
		auto& att = atts[i];
		if (att.parent < numVertices) {
			mst.addUndirectedEdge(i, att.parent);
		}
	}

	return mst;
}

template <class Vertex>
void Prim<Vertex>::initialize(AdjacencyListGraph<Vertex>& graph) {
	auto& vertextAtts = graph.getVertexAttributes();
	for (auto& att : vertextAtts) {
		att.parent = std::numeric_limits<size_t>::max();
		att.key = std::numeric_limits<float>::infinity();
	}
}