#include "Prim.hpp"
#include <iostream>
#include <format>

struct Vertex {
	float key{ std::numeric_limits<float>::max() };
	size_t parent{ std::numeric_limits<size_t>::max() };
};

int main() {
	// Make an undirected graph with 9 vertices 
	size_t numVertices = 9;
	AdjacencyListGraph<Vertex> graph(numVertices);

	// Make 14 edges. Edge: (IndexA, IndexB, Weight)
	graph.addUndirectedEdge(0, 1, 4);
	graph.addUndirectedEdge(0, 7, 8);
	graph.addUndirectedEdge(1, 7, 11);
	graph.addUndirectedEdge(1, 2, 8);
	graph.addUndirectedEdge(2, 8, 2);
	graph.addUndirectedEdge(2, 5, 4);
	graph.addUndirectedEdge(2, 3, 7);
	graph.addUndirectedEdge(3, 4, 9);
	graph.addUndirectedEdge(3, 5, 14);
	graph.addUndirectedEdge(4, 5, 10);
	graph.addUndirectedEdge(6, 5, 2);
	graph.addUndirectedEdge(6, 8, 6);
	graph.addUndirectedEdge(6, 7, 1);
	graph.addUndirectedEdge(7, 8, 7);

	// Run the Prim's algorithm on the graph
	auto mst = Prim<Vertex>::minimumSpanningTree(graph);

	// Print the minimum spanning tree
	for (size_t i = 0; i < numVertices; ++i) {
		auto& adj = mst.getAdjacent(i);
		std::cout << std::format("Vertex {} is connected to [ ", i);
		for (size_t next : adj) {
			std::cout << std::format("{} ", next);
		}
		std::cout << "]\n";
	}

	/*
	Vertex 0 is connected to [ 1 7 ]
	Vertex 1 is connected to [ 0 ]
	Vertex 2 is connected to [ 5 3 8 ]
	Vertex 3 is connected to [ 2 4 ]
	Vertex 4 is connected to [ 3 ]
	Vertex 5 is connected to [ 2 6 ]
	Vertex 6 is connected to [ 5 7 ]
	Vertex 7 is connected to [ 6 0 ]
	Vertex 8 is connected to [ 2 ]
	*/
	return 0;
}