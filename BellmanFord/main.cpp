#include "BellmanFord.hpp"
#include <iostream>
#include <format>

int main() {
	// Create a graph with 5 vertices
	size_t numVertices = 5;
	AdjacencyListGraph<Vertex> graph(numVertices);

	// Add edges to the graph. 
	// The algorithm can handle negative weights, but negative cycles are not allowed
	graph.addEdge(0, 1, -1);
	graph.addEdge(0, 2, 4);
	graph.addEdge(1, 2, 3);
	graph.addEdge(1, 3, 2);
	graph.addEdge(1, 4, 2);
	graph.addEdge(3, 1, 1);
	graph.addEdge(3, 2, 5);
	graph.addEdge(4, 3, -3);
	
	// Set the source vertex to 0
	size_t source = 0;

	// Run Bellman-Ford algorithm
	auto spt = BellmanFord::singleSourceShortestPath(graph, source);

	// Print the shortest path tree
	for (size_t i = 0; i < numVertices; ++i) {
		auto& att = spt.getVertexAttribute(i);
		std::cout << std::format("Vertex: {}, Shortest distance: {}, Next vertices: [ ", i, att.distance);
		auto& adjs = spt.getAdjacent(i);
		for (auto adj : adjs) {
			std::cout << std::format("{} ", adj);
		}
		std::cout << "]\n";
	}
	/*
	Vertex: 0, Shortest distance: 0, Next vertices: [ 1 ]
	Vertex: 1, Shortest distance: -1, Next vertices: [ 2 4 ]
	Vertex: 2, Shortest distance: 2, Next vertices: [ ]
	Vertex: 3, Shortest distance: -2, Next vertices: [ ]
	Vertex: 4, Shortest distance: 1, Next vertices: [ 3 ]
	*/

	return 0;
}