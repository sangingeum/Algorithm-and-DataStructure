#include "Dijkstra.hpp"
#include <iostream>
#include <format>

struct Vertex {
	size_t parent{ std::numeric_limits<size_t>::max() };
	float distance{ std::numeric_limits<float>::max() };
	float weightToParent{};
};

int main() {
	// Create a graph with 5 vertices
	size_t numVertices = 5;
	AdjacencyListGraph<Vertex> graph(numVertices);

	// Add positive edges to the graph
	graph.addEdge(0, 1, 10);
	graph.addEdge(0, 2, 3);
	graph.addEdge(1, 2, 1);
	graph.addEdge(1, 3, 2);
	graph.addEdge(2, 1, 4);
	graph.addEdge(2, 3, 8);
	graph.addEdge(2, 4, 2);
	graph.addEdge(3, 4, 7);
	graph.addEdge(4, 3, 9);

	// Set the source vertex to 0
	size_t source = 0;

	// Run the Dijkstra's algorithm
	auto spt = Dijkstra<Vertex>::singleSourceShortestPath(graph, source);

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
	Vertex: 0, Shortest distance: 0, Next vertices: [ 2 ]
	Vertex: 1, Shortest distance: 7, Next vertices: [ 3 ]
	Vertex: 2, Shortest distance: 3, Next vertices: [ 1 4 ]
	Vertex: 3, Shortest distance: 9, Next vertices: [ ]
	Vertex: 4, Shortest distance: 5, Next vertices: [ ]
	*/

	return 0;
}