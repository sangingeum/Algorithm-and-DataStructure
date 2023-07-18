#pragma once
#include "Graph.hpp"
#include <stdexcept>
template <class N, class D = float>
class AdjacencyListGraph : public Graph<N, D>
{
    
public:
    AdjacencyListGraph<N, D>(size_t numVertices) : Graph<N, D>(numVertices) {}
    virtual void addEdge(size_t fromIndex, size_t toIndex) {
        this->m_edges[fromIndex].push_back(toIndex);
    }
    virtual void addEdge(size_t fromIndex, size_t toIndex, const D& attribute) {
        addEdge(fromIndex, toIndex);
        this->m_edgeAttributes[fromIndex].push_back(attribute);
    }
    virtual std::vector<size_t>& getAdjacent(size_t index) {
        return this->m_edges[index];
    }
    virtual std::vector<D>& getAdjacentEdgeAttributes(size_t index) {
        return this->m_edgeAttributes[index];
    }
    virtual D& getEdgeAttribute(size_t fromIndex, size_t toIndex) {
        auto& vertices = getAdjacent(fromIndex);
        size_t size = vertices.size();
        for (size_t i = 0; i < size; ++i) {
            if (vertices[i] == toIndex) {
                return getAdjacentEdgeAttributes(fromIndex)[i];
            }
        }
        throw std::out_of_range("out_of_range in getEdge");
    }
    virtual std::vector<N>& getVertexAttributes() {
        return this->m_vertices;
    }
    virtual N& getVertexAttribute(size_t index) {
        return this->m_vertices[index];
    }

};

