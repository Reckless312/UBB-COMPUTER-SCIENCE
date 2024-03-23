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
	string start;
	vector<string> bounds;
	vector<string>::iterator KeyIterator;
	bool IsItOver;
	string CurrentValue;
	DirectedGraphIteratorBounds(vector<string> vertices, string start);
public:
	bool Valid(void);
	tuple<string, string> Next(void);
};