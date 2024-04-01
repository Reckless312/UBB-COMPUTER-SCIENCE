#include "GraphIteratorEdges.h"
DirectedGraphIteratorEdges::DirectedGraphIteratorEdges(map <int, vector<int>>& edges)
{
	this->edges = edges;
	this->currentFr = 0;
	this->KeyIterator = this->edges.begin();
	this->IsItOver = false;
	if (KeyIterator != this->edges.end())
	{
		this->CurrentKey = KeyIterator->first;
	}
	else
	{
		this->IsItOver = true;
	}
}

bool DirectedGraphIteratorEdges::Valid(void)
{
	return !this->IsItOver;
}

tuple <int, int> DirectedGraphIteratorEdges::Next(void)
{
	if (this->currentFr < this->edges[this->CurrentKey].size())
	{
		this->currentFr += 1;
		return make_pair(this->CurrentKey, this->edges[this->CurrentKey][this->currentFr - 1]);
	}
	else
	{
		this->KeyIterator++;
		if (this->KeyIterator != this->edges.end())
		{
			this->CurrentKey = this->KeyIterator->first;
			this->currentFr = 1;
			return make_pair(this->CurrentKey, this->edges[this->CurrentKey][this->currentFr - 1]);
		}
		else
		{
			throw out_of_range("Iterator reached the end!\n");
		}
	}
}