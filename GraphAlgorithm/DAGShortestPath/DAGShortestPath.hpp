#pragma once
#include "AdjacencyListGraph.hpp"
#include "TopologicalSort.hpp"
#include <limits>
#include <stdexcept>

/*Example Vertex
struct Vertex {
    size_t parent{ std::numeric_limits<size_t>::max() };
    float weightToParent{ std::numeric_limits<float>::infinity() };
    float distance{ std::numeric_limits<float>::infinity() };
};
*/
template <class Vertex>
class DAGShortestPath
{
public:
    static AdjacencyListGraph<Vertex> singleSourceShortestPath(AdjacencyListGraph<Vertex>& graph, size_t source);
private:
    static void initialize(AdjacencyListGraph<Vertex>& graph, size_t source);
};

// O(|V| + |E|)
// Given a DAG(Directed Acyclic Graph), construct a shortest path tree
// whose root is source
template <class Vertex>
AdjacencyListGraph<Vertex> DAGShortestPath<Vertex>::singleSourceShortestPath(AdjacencyListGraph<Vertex>& graph, size_t source) {
    size_t numVertices = graph.getNumVertices();
    // Initialize the graph
    initialize(graph, source);
    // Topologically sort the graph. For every edge (u, v) in the graph, u precedes v in the sorted array
    auto sortedVertices = TopologicalSort<Vertex>::sort(graph);

    // For vertex u, get all the adjacent edges (u, v) and relax(u, v)
    for (size_t u : sortedVertices) {
        auto& adjs = graph.getAdjacent(u);
        auto& edgeAtts = graph.getEdgeAttributes(u);
        auto& uAtt = graph.getVertexAttribute(u);
        size_t adjSize = adjs.size();
        for (size_t i = 0; i < adjSize; ++i) {
            size_t v = adjs[i];
            auto& vAtt = graph.getVertexAttribute(v);
            // relax(u, v)
            if (vAtt.distance > uAtt.distance + edgeAtts[i]) {
                vAtt.distance = uAtt.distance + edgeAtts[i];
                vAtt.parent = u;
                vAtt.weightToParent = edgeAtts[i];
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
        if (att.parent < numVertices) {
            shortestPathTree.addEdge(att.parent, i, att.weightToParent);
        }
    }

    return shortestPathTree;
}


template <class Vertex>
void DAGShortestPath<Vertex>::initialize(AdjacencyListGraph<Vertex>& graph, size_t source) {
    auto& vertextAtts = graph.getVertexAttributes();
    for (auto& att : vertextAtts) {
        att.parent = std::numeric_limits<size_t>::max();
        att.distance = std::numeric_limits<float>::infinity();
        att.weightToParent = std::numeric_limits<float>::infinity();
    }
    // Set the distance of the source to 0
    graph.getVertexAttribute(source).distance = 0;
}