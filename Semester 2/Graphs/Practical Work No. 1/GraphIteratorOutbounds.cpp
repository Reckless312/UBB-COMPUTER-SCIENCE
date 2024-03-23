#include "GraphIteratorOutbounds.h"
DirectedGraphIteratorOutbounds::DirectedGraphIteratorOutbounds(vector<string> vertices)
{
	this->vertices = vertices;
	this->KeyIterator = this->vertices.begin();
	this->IsItOver = false;
	if (KeyIterator != this->vertices.end())
	{
		this->CurrentValue = *this->KeyIterator;
	}
	else
	{
		this->IsItOver = true;
	}
}

bool DirectedGraphIteratorOutbounds::Valid(void)
{
	return !this->IsItOver;
}

string DirectedGraphIteratorOutbounds::Next(void)
{
	if (this->KeyIterator != this->vertices.end())
	{
		this->CurrentValue = *this->KeyIterator;
		this->KeyIterator++;
		return this->CurrentValue;
	}
	else
	{
		throw out_of_range("Iterator reached the end!\n");
	}
}