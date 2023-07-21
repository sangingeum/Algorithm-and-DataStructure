#include "AStar.hpp"
#include <iostream>
#include <format>

struct Vertex {
	std::pair<float, float> pos;
	float gScore, fScore;
	size_t parent;
};

// Calculate the path from A to B using the the A* algorithm and print the calculated path
void printResult(AdjacencyListGraph<Vertex>& graph, size_t A, size_t B, size_t n) {
	// Run the A* algorithm
	auto path = AStar<Vertex>::shortestPath(graph, A, B);
	for (auto& step : path) {
		std::cout << std::format("Vertex: {}, Coordinates: [{}, {}], Distance: {}\n", step.first, step.first / n, step.first % n, step.second);
	}
	std::cout << "\n";
}

// Make an n x n grid graph 
void constructNxNGraph(AdjacencyListGraph<Vertex>& graph, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			size_t cur = j + 5 * i;
			// Add edges (from, to, weight)
			if (j != 0)
				graph.addEdge(cur, cur - 1, 1);
			if (j != n - 1)
				graph.addEdge(cur, cur + 1, 1);
			if (i != 0)
				graph.addEdge(cur, cur - n, 1);
			if (i != n - 1)
				graph.addEdge(cur, cur + n, 1);
			graph.getVertexAttribute(cur).pos = { i, j };
		}
	}
}


int main() {
	// Create a graph with 25 vertices
	size_t numVertices = 25, n = 5;
	AdjacencyListGraph<Vertex> graph(numVertices);

	// Make a 5 x 5 grid graph 
	constructNxNGraph(graph, n);

	// Calculate the path from A to B using the the A* algorithm and print the calculated path
	printResult(graph, 0, 24, n);
	/*
	Vertex: 0, Coordinates: [0, 0], Distance: 0
	Vertex: 1, Coordinates: [0, 1], Distance: 1
	Vertex: 6, Coordinates: [1, 1], Distance: 2
	Vertex: 7, Coordinates: [1, 2], Distance: 3
	Vertex: 12, Coordinates: [2, 2], Distance: 4
	Vertex: 13, Coordinates: [2, 3], Distance: 5
	Vertex: 18, Coordinates: [3, 3], Distance: 6
	Vertex: 19, Coordinates: [3, 4], Distance: 7
	Vertex: 24, Coordinates: [4, 4], Distance: 8
	*/
	printResult(graph, 22, 11, n);
	/*
	Vertex: 22, Coordinates: [4, 2], Distance: 0
	Vertex: 17, Coordinates: [3, 2], Distance: 1
	Vertex: 16, Coordinates: [3, 1], Distance: 2
	Vertex: 11, Coordinates: [2, 1], Distance: 3
	*/
	printResult(graph, 16, 5, n);
	/*
	Vertex: 16, Coordinates: [3, 1], Distance: 0
	Vertex: 11, Coordinates: [2, 1], Distance: 1
	Vertex: 10, Coordinates: [2, 0], Distance: 2
	Vertex: 5, Coordinates: [1, 0], Distance: 3
	*/

	return 0;
}


