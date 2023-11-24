#pragma once
#include "AdjacencyMatrixGraph.hpp"
#include <limits>
template<class T>
class FloydWarshall
{
public:
	// Given a directed graph with positive and negative edges, 
	// returns a 2D vector which stores shortest distances between vertices
	// No negative cycles are allowed
	static std::vector<std::vector<float>> shortestDistance(AdjacencyMatrixGraph<T>& graph) {
		size_t numVertices = graph.getNumVertices();
		std::vector<std::vector<float>> distance(numVertices, std::vector<float>(numVertices, std::numeric_limits<float>::max()));

		// Initialization
		for (int u = 0; u < numVertices; ++u) {
			for (int v = 0; v < numVertices; ++v) {
				distance[u][v] = graph.getEdgeAttribute(u, v);
			}
		}
		for (int i = 0; i < numVertices; ++i) {
			distance[i][i] = 0;
		}
		// FloydWarshall
		for (int k = 0; k < numVertices; ++k) {
			for (int u = 0; u < numVertices; ++u) {
				for (int v = 0; v < numVertices; ++v) {
					distance[u][v] = std::min(distance[u][v], distance[u][k] + distance[k][v]);
				}
			}
		}
		return distance;
	}
};

