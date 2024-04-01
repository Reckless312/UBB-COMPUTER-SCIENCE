#include "GraphIteratorBounds.h"
DirectedGraphIteratorBounds::DirectedGraphIteratorBounds(vector<int> vertices, int start)
{
	this->start = start;
	this->bounds = vertices;
	this->KeyIterator = this->bounds.begin();
	this->IsItOver = false;
	if (KeyIterator != this->bounds.end())
	{
		this->CurrentValue = *this->KeyIterator;
	}
	else
	{
		this->IsItOver = true;
	}
}

bool DirectedGraphIteratorBounds::Valid(void)
{
	return !this->IsItOver;
}

tuple <int, int> DirectedGraphIteratorBounds::Next(void)
{
	if (this->KeyIterator != this->bounds.end())
	{
		this->CurrentValue = *this->KeyIterator;
		this->KeyIterator++;
		return make_pair(this->start, this->CurrentValue);
	}
	else
	{
		throw out_of_range("Iterator reached the end!\n");
	}
}