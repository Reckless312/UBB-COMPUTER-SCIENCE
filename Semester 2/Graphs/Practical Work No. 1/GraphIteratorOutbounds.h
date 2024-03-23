#pragma once
#include <tuple>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <cctype>
#include <random>
using namespace std;
class DirectedGraph;
class DirectedGraphIteratorOutbounds
{
	friend class DirectedGraph;
private:
	vector<string> vertices;
	vector<string>::iterator KeyIterator;
	bool IsItOver;
	string CurrentValue;
	DirectedGraphIteratorOutbounds(vector<string> vertices);
	bool Valid(void);
	string Next(void);
public:
};