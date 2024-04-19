#pragma once
#include "Graph.h"
#include <iostream>
#include <stack>

using namespace std;

class UnDirectedGraph;

class P3 {
	friend class UnDirectedGraph;
private:
	UnDirectedGraph graph;
public:
	P3(UnDirectedGraph& graph);
	void ConnectedComponents();
	void DFS(int vertex, bool visited[]);
	void UpdateGraph(UnDirectedGraph& graph);
};