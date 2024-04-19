#include "VerticesIterator.h"

VerticesIterator::VerticesIterator(vector<int> vertices)
{
	this->vertices = vertices;
	this->VectorIterator = this->vertices.begin();
	this->IsItOver = false;
	if (this->VectorIterator != this->vertices.end())
	{
		this->CurrentValue = *this->VectorIterator;
	}
	else
	{
		this->IsItOver = true;
	}
}

bool VerticesIterator::Valid()
{
	return !this->IsItOver;
}

int VerticesIterator::Next()
{
	if (this->VectorIterator != this->vertices.end())
	{
		this->CurrentValue = *this->VectorIterator;
		this->VectorIterator++;
		return this->CurrentValue;
	}
	else
	{
		throw out_of_range("Iterator reached the end!\n");
	}
}
