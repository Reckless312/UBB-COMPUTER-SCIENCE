#pragma once

#include <vector>
#include <map>
#include <string>
#include <tuple>
#include <fstream>

using namespace std;

class UnDirectedGraph;
class EdgesIterator
{
	friend class UnDirectedGraph;
private:
	map<int, vector<int>> edges;
	map<int, vector<int>>::iterator mapIterator;
	int currentFr;
	bool IsItOver;
	int CurrentKey;
	EdgesIterator(map <int, vector<int>>& edges);
	bool Valid();
	tuple <int, int> Next();
public:
};
