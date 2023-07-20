#pragma once
#include "AdjacencyListGraph.hpp"
#include <limits>
#include <stdexcept>

struct Vertex {
    size_t parent{ std::numeric_limits<size_t>::max() };
    float weightToParent{ 0.f };
    float distance{ std::numeric_limits<float>::max() };
};

class BellmanFord
{
public:
    // Time Complexity: O(|V||E|)
    // Given a directed, weighted graph that does not contain a negative cycle and a source vertex,
    // return a shortest path tree whose root is the given source vertex
    static AdjacencyListGraph<Vertex> singleSourceShortestPath(AdjacencyListGraph<Vertex>& graph, size_t source);
};
