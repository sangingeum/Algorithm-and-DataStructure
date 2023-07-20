#pragma once
#include "AdjacencyListGraph.hpp"
#include "MinPriorityQueue.hpp"
#include <limits>

struct Vertex {
	size_t parent{ std::numeric_limits<size_t>::max() };
	float distance{ std::numeric_limits<float>::max() };
	float weightToParent{};
};

class Dijkstra
{
public:
	// Given a graph with positive edges and a source vertex,
	// return a shortest path tree whose root is source
	// This implementation uses a min priority queue
	static AdjacencyListGraph<Vertex> singleSourceShortestPath(AdjacencyListGraph<Vertex>& graph, size_t source);
};

