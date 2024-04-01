#pragma once
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
class DirectedGraphIteratorVertices
{
	friend class DirectedGraph;
private:
	vector<int> vertices;
	vector<int>::iterator KeyIterator;
	bool IsItOver;
	int CurrentValue;
	DirectedGraphIteratorVertices(vector<int> vertices);
public:
	bool Valid(void);
	int Next(void);
};