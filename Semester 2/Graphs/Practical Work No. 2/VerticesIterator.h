#pragma once

#include <vector>
#include <stdexcept>

using namespace std;

class UnDirectedGraph;
class VerticesIterator {
	friend class UnDirectedGraph;
private:
	vector<int> vertices;
	vector<int>::iterator VectorIterator;
	bool IsItOver;
	int CurrentValue;
	VerticesIterator(vector<int> vertices);
public:
	bool Valid();
	int Next();
};
