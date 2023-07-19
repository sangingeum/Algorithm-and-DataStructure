#pragma once
#include "AdjacencyListGraph.hpp"
#include "DisjointSet.hpp"
#include <vector>
#include <algorithm>
#include <tuple>

struct Vertex {};

class Kruskal
{
	using Edge = typename std::tuple<size_t, size_t, float>;
public:
	// Return a minimum spanning tree of the given 'undirected' graph
	// This method does not check whether the given graph is directed or not
	static AdjacencyListGraph<Vertex> minimumSpanningTree(AdjacencyListGraph<Vertex>& graph);

};

