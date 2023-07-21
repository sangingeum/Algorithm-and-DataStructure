#include "DAGShortestPath.hpp"
#include <iostream>
#include <format>

struct Vertex {
	size_t parent{ std::numeric_limits<size_t>::max() };
	float weightToParent{ 0.f };
	float distance{ std::numeric_limits<float>::max() };
};

int main() {
	// Create a graph with 6 vertices
	size_t numVertices = 6;
	AdjacencyListGraph<Vertex> graph(numVertices);

	// Add edges to form a DAG(directed acyclic graph)
	graph.addEdge(0, 1, 7);
	graph.addEdge(0, 4, 4);
	graph.addEdge(1, 3, 1);
	graph.addEdge(1, 4, 5);
	graph.addEdge(2, 0, 2);
	graph.addEdge(2, 1, 6);
	graph.addEdge(4, 3, -2);
	graph.addEdge(5, 0, 3);
	graph.addEdge(5, 2, -1);

	// Set the source vertex to 5
	size_t source = 5;

	// Run the DAGShortestPath algorithm
	auto spt = DAGShortestPath<Vertex>::singleSourceShortestPath(graph, source);

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
	Vertex: 0, Shortest distance: 1, Next vertices: [ 4 ]
	Vertex: 1, Shortest distance: 5, Next vertices: [ ]
	Vertex: 2, Shortest distance: -1, Next vertices: [ 0 1 ]
	Vertex: 3, Shortest distance: 3, Next vertices: [ ]
	Vertex: 4, Shortest distance: 5, Next vertices: [ 3 ]
	Vertex: 5, Shortest distance: 0, Next vertices: [ 2 ]
	*/

	return 0;
}