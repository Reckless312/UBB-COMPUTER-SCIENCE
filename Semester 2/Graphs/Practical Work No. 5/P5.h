#pragma once
#include "Graph.h"
#include <set>
#include <stack>

using namespace std;

class UnDirectedGraph;

class P5 {
	friend class UnDirectedGraph;
private:
	UnDirectedGraph graph;
	set<int> Vertices;
	vector<set<int>> allCliques;
public:
	P5(UnDirectedGraph& graph);
	void bronKerbosch();
	set<int> MaxClique();
};
