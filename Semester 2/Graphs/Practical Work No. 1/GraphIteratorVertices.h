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
	vector<string> vertices;
	vector<string>::iterator KeyIterator;
	bool IsItOver;
	string CurrentValue;
	DirectedGraphIteratorVertices(vector<string> vertices);
public:
	bool Valid(void);
	string Next(void);
};