#include <iostream>
#include <format>
#include <queue>
#include "AdjacencyListGraph.hpp"
#include "AdjacencyMatrixGraph.hpp"
class Node {
public:
	float distance{100000.0f};
};


int main() {
	// Create a AdjacencyListGraph with 7 vertices
	size_t numVertex = 7;
	AdjacencyListGraph<Node> graph(numVertex);

	// Add edges to the graph (from, to, weight)
	graph.addEdge(0, 1, 1);
	graph.addEdge(1, 2, 1);
	graph.addEdge(1, 5, 1.5f);
	graph.addEdge(2, 3, 1);
	graph.addEdge(2, 5, 1);
	graph.addEdge(3, 4, 1);
	graph.addEdge(3, 6, 1);
	graph.addEdge(5, 4, 0.5f);
	graph.addEdge(6, 1, 1);

	/*  
	Graph Structure    
	    ¡ç ¡ç ¡ç ¡ç 6
	    ¡é       ¡è
	0 ¡æ 1 ¡æ 2 ¡æ 3 ¡æ 4
	    ¡é   ¡é       ¡è
		¡é ¡æ 5 ¡æ ¡æ ¡æ ¡è
	*/


	// Make a queue that keeps track of what to
	// search next
	std::queue<size_t> toSearch;
	toSearch.push(0);
	auto& attribute = graph.getVertexAttribute(0);
	attribute.distance = 0;
	
	// Run the BFS algorithm to calculate the shortest path from vertex 0
	while (!toSearch.empty()) {
		auto cur = toSearch.front(); toSearch.pop();
		auto curDist = graph.getVertexAttribute(cur).distance;
		auto& adj = graph.getAdjacent(cur);
		auto& weights = graph.getAdjacentEdgeAttributes(cur);
		size_t size = adj.size();
		for (size_t i = 0; i < size; ++i) {
			auto& targetIndex = adj[i];
			auto& targetWeight = weights[i];
			auto& targetAtt = graph.getVertexAttribute(targetIndex);
			if (targetAtt.distance > curDist + targetWeight) {
				targetAtt.distance = curDist + targetWeight;
				toSearch.push(targetIndex);
			}
		}
	}

	// Print the calculated distance for each vertex
	size_t index = 0;
	for (auto& vertex : graph.getVertexAttributes()) {
		std::cout << std::format("Vertex: {}, Distance: {}\n", index++, vertex.distance);
	}
	/*
	Vertex: 0, Distance: 0
	Vertex: 1, Distance: 1
	Vertex: 2, Distance: 2
	Vertex: 3, Distance: 3
	Vertex: 4, Distance: 3
	Vertex: 5, Distance: 2.5
	Vertex: 6, Distance: 4
	*/

	return 0;
}