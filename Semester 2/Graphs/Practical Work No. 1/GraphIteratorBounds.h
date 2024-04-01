#pragma once
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
class DirectedGraphIteratorBounds
{
	friend class DirectedGraph;
private:
	int start;
	vector<int> bounds;
	vector<int>::iterator KeyIterator;
	bool IsItOver;
	int CurrentValue;
	DirectedGraphIteratorBounds(vector<int> vertices, int start);
public:
	bool Valid(void);
	tuple<int, int> Next(void);
};