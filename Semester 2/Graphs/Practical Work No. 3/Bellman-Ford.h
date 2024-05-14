#pragma once

#include "Graph.h"
#include <limits>
#include <queue>
#include <set>

class Bellman_Ford_Algorithm
{
	friend class DirectedGraph;
	friend class DirectedGraphIteratorEdges;
private:
	DirectedGraph graph;
	int starting_vertex;
	int destination_vertex;
	int** distance;
public:
	Bellman_Ford_Algorithm(DirectedGraph graph, int vertex, int vertex2);
	vector<int> Relax();
};