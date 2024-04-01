#pragma once
#include <iostream>
#include <fstream>
#include <utility>
#include <map>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <cctype>
#include <random>
using namespace std;
class DirectedGraph;
class DirectedGraphIteratorEdges
{
	friend class DirectedGraph;
private:
	map<int, vector<int>> edges;
	map<int, vector<int>>::iterator KeyIterator;
	int currentFr;
	bool IsItOver;
	int CurrentKey;
	DirectedGraphIteratorEdges(map <int, vector<int>>& edges);
	bool Valid(void);
	tuple <int, int> Next(void);
public:
};