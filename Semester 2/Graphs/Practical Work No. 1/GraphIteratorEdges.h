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
	map<string, vector<string>> edges;
	map<string, vector<string>>::iterator KeyIterator;
	int currentFr;
	bool IsItOver;
	string CurrentKey;
	DirectedGraphIteratorEdges(map <string, vector<string>>& edges);
	bool Valid(void);
	tuple <string, string> Next(void);
public:
};