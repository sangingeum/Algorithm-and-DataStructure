#include "FloydWarshall.hpp"
#include <iostream>

class Vertex {

};

int main() {
	// Create an adjacency matrix graph with 5 vertices
	AdjacencyMatrixGraph<Vertex> graph(5, std::numeric_limits<float>::max());

	// Add directed edges
	graph.addEdge(0, 1, 4);
	graph.addEdge(0, 3, 5);
	graph.addEdge(1, 2, 1);
	graph.addEdge(1, 4, 6);
	graph.addEdge(2, 0, 2);
	graph.addEdge(2, 3, 3);
	graph.addEdge(3, 2, 1);
	graph.addEdge(3, 4, 2);
	graph.addEdge(4, 0, 1);
	graph.addEdge(4, 3, 4);

	// Run the FloydWarshall algorithm
	std::vector<std::vector<float>> distance = FloydWarshall<Vertex>::shortestDistance(graph);

	// Print the result
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			std::cout << distance[i][j] << " ";
		}
		std::cout << "\n";
	}

	/*
	0 4 5 5 7
	3 0 1 4 6
	2 6 0 3 5
	3 7 1 0 2
	1 5 5 4 0
	*/

	return 0;
}