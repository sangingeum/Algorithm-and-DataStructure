#include "Dijkstra.hpp"

	// Given a graph with positive edges and a source vertex,
	// return a shortest path tree whose root is source
	// This implementation uses a min priority queue
AdjacencyListGraph<Vertex> Dijkstra::singleSourceShortestPath(AdjacencyListGraph<Vertex>& graph, size_t source) {
	// Initialize the min priority queue and the source distance
	size_t numVertices = graph.getNumVertices();
	graph.getVertexAttribute(source).distance = 0;
	MinPriorityQueue<size_t> minQ;
	for (size_t i = 0; i < numVertices; ++i) {
		minQ.push(graph.getVertexAttribute(i).distance, i);
	}
	// Extract a vertex with the minimum distance from the min priority queue
	// and relax adjacent vertices
	std::vector<bool> visited(numVertices, false);
	while (!minQ.empty()) {
		auto [key, u] = minQ.front(); minQ.pop();
		if (!visited[u]) {
			visited[u] = true;
			// Relax(u, v) for all edges adjacent to u
			auto& adjs = graph.getAdjacent(u);
			auto& edgeAtts = graph.getEdgeAttributes(u);
			auto& uAtt = graph.getVertexAttribute(u);
			size_t adjSize = adjs.size();
			for (size_t i = 0; i < adjSize; ++i) {
				size_t v = adjs[i];
				auto& vAtt = graph.getVertexAttribute(v);
				// Relax(u, v)
				if (vAtt.distance > uAtt.distance + edgeAtts[i]) {
					// Update vertex v
					vAtt.distance = uAtt.distance + edgeAtts[i];
					vAtt.weightToParent = edgeAtts[i];
					vAtt.parent = u;
					// Push newly updated vertex v
					minQ.push(vAtt.distance, v);
				}
			}
		}
	}

	// Construct a shortest path tree using the vertex attributes calculated above
	AdjacencyListGraph<Vertex> shortestPathTree(numVertices);
	for (size_t i = 0; i < numVertices; ++i) {
		auto& att = graph.getVertexAttribute(i);
		auto& newAtt = shortestPathTree.getVertexAttribute(i);
		newAtt.distance = att.distance;
		newAtt.parent = att.parent;
		newAtt.weightToParent = att.weightToParent;
		if (att.parent < numVertices) {
			shortestPathTree.addEdge(att.parent, i, att.weightToParent);
		}
	}

	return shortestPathTree;
}