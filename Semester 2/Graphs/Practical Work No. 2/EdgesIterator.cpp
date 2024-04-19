#include "EdgesIterator.h"

EdgesIterator::EdgesIterator(map<int, vector<int>>& edges)
{
	this->edges = edges;
	this->currentFr = 0;
	this->mapIterator = this->edges.begin();
	this->IsItOver = false;
	if (this->mapIterator != this->edges.end())
	{
		this->CurrentKey = this->mapIterator->first;
	}
	else
	{
		this->IsItOver = true;
	}
}

bool EdgesIterator::Valid()
{
	return !this->IsItOver;
}

tuple<int, int> EdgesIterator::Next()
{
	if (this->currentFr < this->edges[this->CurrentKey].size())
	{
		this->currentFr++;
		return make_pair(this->CurrentKey, this->edges[this->CurrentKey][this->currentFr - 1]);
	}
	else
	{
		this->mapIterator++;
		if (this->mapIterator != this->edges.end())
		{
			this->CurrentKey = this->mapIterator->first;
			this->currentFr = 1;
			return make_pair(this->CurrentKey, this->edges[this->CurrentKey][this->currentFr - 1]);
		}
		else
		{
			throw out_of_range("Iterator reached the end!\n");
		}
	}
}
