#pragma once

#include "Graph.h"
#include <queue>
class P4
{
	friend class DirectedGraph;
public:
	DirectedGraph graph;
	vector<int> PredecessorCount();
	vector<int> GetHighestCostPath(vector<int> sorted, int starting_vertex, int ending_vertex);
};