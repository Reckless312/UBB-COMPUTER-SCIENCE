#include "VertexEdgeIterator.h"

VertexEdgeIterator::VertexEdgeIterator(vector<int> vertices, int vertex)
{
	this->vertex = vertex;
	this->connected_points = vertices;
	this->VectorIterator = this->connected_points.begin();
	this->IsItOver = false;
	if (VectorIterator != this->connected_points.end())
	{
		this->CurrentValue = *this->VectorIterator;
	}
	else
	{
		this->IsItOver = true;
	}
}

bool VertexEdgeIterator::Valid(void)
{
	return !this->IsItOver;
}

tuple <int, int> VertexEdgeIterator::Next(void)
{
	if (this->VectorIterator != this->connected_points.end())
	{
		this->CurrentValue = *this->VectorIterator;
		this->VectorIterator++;
		return make_pair(this->vertex, this->CurrentValue);
	}
	else
	{
		throw out_of_range("Iterator reached the end!\n");
	}
}
