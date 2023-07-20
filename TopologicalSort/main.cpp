#include "TopologicalSort.hpp"
#include <iostream>
#include <format>

struct Vertex {
	bool visited{ false };
};


int main() {
	// Create a graph with 10 vertices
	size_t numVertices = 10;
	AdjacencyListGraph<Vertex> graph(numVertices);

	// Create a directed acyclic graph(DAG)
	graph.addEdge(0, 2);
	graph.addEdge(0, 6);
	graph.addEdge(1, 0);
	graph.addEdge(2, 7);
	graph.addEdge(3, 0);
	graph.addEdge(4, 5);
	graph.addEdge(4, 6);
	graph.addEdge(6, 7);
	graph.addEdge(9, 6);

	// Topologically sort the graph
	std::vector<size_t> result = TopologicalSort<Vertex>::sort(graph);

	// Print the result
	for (auto vertex : result) {
		std::cout << std::format("Vertex:{}\n", vertex);
	}
	/*
	Vertex:9
	Vertex:8
	Vertex:4
	Vertex:5
	Vertex:3
	Vertex:1
	Vertex:0
	Vertex:6
	Vertex:2
	Vertex:7
	*/
	return 0;
}
