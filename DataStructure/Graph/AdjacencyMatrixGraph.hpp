#pragma once
#include "Graph.hpp"

template <class N, class D = float>
class AdjacencyMatrixGraph : public Graph<N, D>
{
public:
    AdjacencyMatrixGraph<N, D>(size_t numVertices);
    void addEdge(size_t fromIndex, size_t toIndex);
    void addEdge(size_t fromIndex, size_t toIndex, const D& attribute);
    std::vector<size_t>& getAdjacent(size_t index);
    std::vector<D>& getEdgeAttributes(size_t index);
    D& getEdgeAttribute(size_t fromIndex, size_t toIndex);
    std::vector<N>& getVertexAttributes();
    N& getVertexAttribute(size_t index);
};

// Create (numVertices x numVertices) AdjacencyMatrices
template <class N, class D>
AdjacencyMatrixGraph<N, D>::AdjacencyMatrixGraph<N, D>(size_t numVertices) : Graph<N, D>(numVertices) {
    for (auto& edges : this->m_edges) {
        edges = std::move(std::vector<size_t>(numVertices, 0));
    }
    for (auto& atts : this->m_edgeAttributes) {
        atts = std::move(std::vector<D>(numVertices));
    }
}

template <class N, class D>
void AdjacencyMatrixGraph<N, D>::addEdge(size_t fromIndex, size_t toIndex) {
    // Set the edge between two vertices as 1
    this->m_edges[fromIndex][toIndex] = 1;
}

template <class N, class D>
void AdjacencyMatrixGraph<N, D>::addEdge(size_t fromIndex, size_t toIndex, const D& attribute) {
    addEdge(fromIndex, toIndex);
    this->m_edgeAttributes[fromIndex][toIndex] = attribute;
}

// The caller should handle 0s and 1s in the output
template <class N, class D>
std::vector<size_t>& AdjacencyMatrixGraph<N, D>::getAdjacent(size_t index) {
    return this->m_edges[index];
}

// getAdjacent should be called first to know which edge is valid
template <class N, class D>
std::vector<D>& AdjacencyMatrixGraph<N, D>::getEdgeAttributes(size_t index) {
    return this->m_edgeAttributes[index];
}

// getAdjacent should be called first to know which edge is valid
template <class N, class D>
D& AdjacencyMatrixGraph<N, D>::getEdgeAttribute(size_t fromIndex, size_t toIndex) {
    return this->m_edgeAttributes[fromIndex][toIndex];
}

template <class N, class D>
std::vector<N>& AdjacencyMatrixGraph<N, D>::getVertexAttributes() {
    return this->m_vertices;
}

template <class N, class D>
N& AdjacencyMatrixGraph<N, D>::getVertexAttribute(size_t index) {
    return this->m_vertices[index];
}