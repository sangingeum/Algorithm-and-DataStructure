#include "BellmanFord.hpp"
// Time Complexity: O(|V||E|)
// Given a directed, weighted graph that does not contain a negative cycle and a source vertex,
// return a shortest path tree whose root is the given source vertex
AdjacencyListGraph<Vertex> BellmanFord::singleSourceShortestPath(AdjacencyListGraph<Vertex>& graph, size_t source) {
    size_t numVertices = graph.getNumVertices();
    // Set the source distance to 0
    graph.getVertexAttribute(source).distance = 0;

    // Iterate for |V| - 1 times
    for (size_t i = 1; i < numVertices; ++i) {
        // For edge (u, v) in the graph, relax(u, v)
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

    // Check negative cycles in the graph
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