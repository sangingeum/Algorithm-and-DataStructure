#pragma once
#include <vector>
#include <stack>
#include "AdjacencyListGraph.hpp" // This header file is defined in the Graph folder

struct Vertex {
	bool visited{ false };
};

class TopologicalSort
{
public:
	// Time Complexity: O(|V|+|E|)
	// Topologically sort the given graph and return a sorted vector of vertices
	// For every directed edge (u, v), vertex u will appear before vertex v.
	static std::vector<size_t> sort(AdjacencyListGraph<Vertex>& graph);
};

