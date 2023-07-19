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
	static std::vector<size_t> sort(AdjacencyListGraph<Vertex>& graph);
};

