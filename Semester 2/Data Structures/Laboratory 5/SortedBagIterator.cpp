#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->stack = new int[bag.Size];
	this->current = bag.root;
	this->stack_position = 0;
	this->current_frequency = 0;
	while (this->current != -1)
	{
		this->stack[this->stack_position] = this->current;
		this->stack_position++;
		this->current = bag.nodes[this->current].left;
	}
	if (bag.root != -1)
	{
		this->current = this->stack[this->stack_position - 1];
		this->stack_position--;
		this->current_frequency = bag.nodes[this->current].frequency;
	}
}
//Complexity -> T(h) - all cases, where h is the minimum height required to reach the "minimum" (depends) of the left side

TComp SortedBagIterator::getCurrent() {
	if (!valid())
	{
		throw exception();
	}
	return bag.nodes[this->current].info;
}
//Complexity -> T(1) - all cases

bool SortedBagIterator::valid() {
	return this->current != -1;
}
//Complexity -> T(1) - all cases
void SortedBagIterator::next() {
	if (!valid())
	{
		throw exception();
	}
	if (this->current_frequency > 1)
	{
		this->current_frequency--;
	}
	else
	{
		this->current = bag.nodes[this->current].right;
		while (this->current != -1)
		{
			this->stack[this->stack_position] = this->current;
			this->stack_position++;
			this->current = bag.nodes[this->current].left;
		}
		if (this->stack_position != 0)
		{
			this->current = this->stack[this->stack_position - 1];
			this->stack_position--;
			this->current_frequency = bag.nodes[this->current].frequency;
		}
		else
		{
			this->current = -1;
		}
	}
}
//Complexity-> T(1) - Best case if the element appears multiple times
//          -> T(h) - Worst case if we need to fix the "next minimum" after we considered the previous ones
//          -> O(h) - Total complexity

void SortedBagIterator::first() {
	this->current = bag.root;
	this->stack_position = 0;
	this->current_frequency = 0;
	while (this->current != -1)
	{
		this->stack[this->stack_position] = this->current;
		this->stack_position++;
		this->current = bag.nodes[this->current].left;
	}
	if (bag.root != -1)
	{
		this->current = this->stack[this->stack_position - 1];
		this->stack_position--;
		this->current_frequency = bag.nodes[this->current].frequency;
	}
}
//Same complexity with the constructor

