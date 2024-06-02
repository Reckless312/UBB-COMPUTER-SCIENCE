#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//TODO - Representation
	int* stack;
	int current;
	int stack_position;
	int current_frequency;
public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

