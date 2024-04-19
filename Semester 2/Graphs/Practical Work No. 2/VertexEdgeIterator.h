#pragma once

#include <vector>
#include <tuple>
#include <stdexcept>

using namespace std;

class UnDirectedGraph;

class VertexEdgeIterator
{
	friend class UnDirectedGraph;
private:
	int vertex;
	vector<int> connected_points;
	vector<int>::iterator VectorIterator;
	bool IsItOver;
	int CurrentValue;
	VertexEdgeIterator(vector<int> vertices, int vertex);
public:
	bool Valid(void);
	tuple<int, int> Next(void);
};