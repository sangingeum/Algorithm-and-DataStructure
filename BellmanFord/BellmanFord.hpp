#pragma once
#include "AdjacencyListGraph.hpp"
#include <limits>
#include <stdexcept>

/*Example Vertex
struct Vertex {
    size_t parent{ std::numeric_limits<size_t>::max() };
    float weightToParent{ 0.f };
    float distance{ std::numeric_limits<float>::max() };
};
*/
template <class Vertex>
class BellmanFord
{
public:
    static AdjacencyListGraph<Vertex> singleSourceShortestPath(AdjacencyListGraph<Vertex>& graph, size_t source);
private:
    static void initialize(AdjacencyListGraph<Vertex>& graph, size_t source);
};

// Time Complexity: O(|V||E|)
// Given a directed, weighted graph that does not contain a negative cycle and a source vertex,
// return a shortest path tree whose root is the given source vertex
template <class Vertex>
AdjacencyListGraph<Vertex> BellmanFord<Vertex>::singleSourceShortestPath(AdjacencyListGraph<Vertex>& graph, size_t source) {
    size_t numVertices = graph.getNumVertices();
    // Initialize the graph
    initialize(graph, source);

    // Iterate for |V| - 1 times
    for (size_t i = 1; i < numVertices; ++i) {
        // For every edge (u, v) in the graph, relax(u, v)
        for (size_t u = 0; u < numVertices; ++u) {
            auto& adjs = graph.getAdjacent(u);
            auto& edgeAtts = graph.getEdgeAttributes(u);
            auto& uAtt = graph.getVertexAttribute(u);
            size_t adjSize = adjs.size();
            for (size_t j = 0; j < adjSize; ++j) {
                size_t v = adjs[j];
                auto& vAtt = graph.getVertexAttribute(v);
                // relax(u, v)
                if (vAtt.distance > uAtt.distance + edgeAtts[j]) {
                    vAtt.distance = uAtt.distance + edgeAtts[j];
                    vAtt.weightToParent = edgeAtts[j];
                    vAtt.parent = u;
                }
            }
        }
    }

    // Check if a negative cycle exists in the graph
    for (size_t u = 0; u < numVertices; ++u) {
        auto& adjs = graph.getAdjacent(u);
        auto& edgeAtts = graph.getEdgeAttributes(u);
        auto& uAtt = graph.getVertexAttribute(u);
        size_t adjSize = adjs.size();
        for (size_t j = 0; j < adjSize; ++j) {
            size_t v = adjs[j];
            auto& vAtt = graph.getVertexAttribute(v);
            // If a negative cycle is found, throw an error
            if (vAtt.distance > uAtt.distance + edgeAtts[j]) {
                throw std::runtime_error("Negative cycle detected.");
            }
        }
    }

    // Construct a shortest path tree using the vertex attributes calculated above
    AdjacencyListGraph<Vertex> shortestPathTree(numVertices);
    for (size_t i = 0; i < numVertices; ++i) {
        auto& att = graph.getVertexAttribute(i);
        auto& newAtt = shortestPathTree.getVertexAttribute(i);
        newAtt.distance = att.distance;
        newAtt.parent = att.parent;
        newAtt.weightToParent = att.weightToParent;
        if (i != source) {
            shortestPathTree.addEdge(att.parent, i, att.weightToParent);
        }
    }

    return shortestPathTree;
}


template <class Vertex>
void BellmanFord<Vertex>::initialize(AdjacencyListGraph<Vertex>& graph, size_t source) {
    auto& vertextAtts = graph.getVertexAttributes();
    for (auto& att : vertextAtts) {
        att.parent = std::numeric_limits<size_t>::max();
        att.distance = std::numeric_limits<float>::max();
        att.weightToParent = 0;
    }
    // Set the distance of the source to 0
    graph.getVertexAttribute(source).distance = 0;
}