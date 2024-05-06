#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//TODO - Implementation
	this->cap = 1;
	this->Size = 0;
	this->firstEmpty = 0;
	this->head = -1;
	this->tail = -1;
	this->nodes = new DLLANode[cap];
	this->nodes[0].prev = -1;
	this->nodes[0].next = -1;
}


void Bag::add(TElem elem) {
	// Check if the DLLA has any values in it
	if (this->head == -1)
	{
		if (this->firstEmpty != -1)
		{
			this->head = this->firstEmpty;
			this->tail = this->firstEmpty;
			if (this->nodes[this->firstEmpty].next != -1)
			{
				this->firstEmpty = this->nodes[this->firstEmpty].next;
;				this->nodes[this->firstEmpty].prev = -1;
			}
			else
			{
				this->firstEmpty = this->nodes[this->firstEmpty].next;
			}
			this->nodes[this->head].frequency = 1;
			this->nodes[this->head].info = elem;
			this->nodes[this->head].next = -1;
			this->nodes[this->head].prev = -1;
		}
		this->Size++;
		return;
	}
	else
	{
		int current = this->head;
		int capacity_used = 0;
		//Check if the value is found in the dlla
		while (this->nodes[current].next != -1)
		{
			if (this->nodes[current].info == elem)
			{
				this->nodes[current].frequency++;
				this->Size++;
				return;
			}
			current = this->nodes[current].next;
			capacity_used++;
		}
		//Check for the last element if it's the same
		if (this->nodes[this->tail].info == elem)
		{
			this->nodes[this->tail].frequency++;
			this->Size++;
			return;
		}
		capacity_used++;
		//Check if in need of a resize
		if (capacity_used == this->cap)
		{
			this->cap = this->cap * 2;
			DLLANode* copy = new DLLANode[this->cap];
			for (int i = 0; i < capacity_used; i++)
			{
				copy[i] = this->nodes[i];
			}
			for (int i = capacity_used; i < this->cap; i++)
			{
				copy[i].next = i + 1;
				copy[i].prev = i - 1;
			}
			this->firstEmpty = capacity_used;
			copy[capacity_used].prev = -1;
			copy[this->cap - 1].next = -1;
			delete[] this->nodes;
			this->nodes = copy;
		}
		current = this->firstEmpty;
		if (this->nodes[this->firstEmpty].next != -1)
		{
			this->firstEmpty = this->nodes[this->firstEmpty].next;
			this->nodes[this->firstEmpty].prev = -1;
		}
		else
		{
			this->firstEmpty = this->nodes[this->firstEmpty].next;
		}
		this->nodes[current].info = elem;
		this->nodes[current].frequency = 1;
		this->nodes[current].next = -1;
		this->nodes[current].prev = this->tail;
		this->nodes[this->tail].next = current;
		this->Size++;
		this->tail = current;
		return;
	}
}
// BC = T(1)
// WC = T(cap) when the capacity is increased and the dlla is resized
// TC = O(cap)


bool Bag::remove(TElem elem) {
	int current = this->head;
	//if empty ->false
	if (current == -1)
	{
		return false;
	}
	while (this->nodes[current].next != -1)
	{
		if (this->nodes[current].info == elem)
		{
			// > 1 frequency then just decrease
			if (this->nodes[current].frequency > 1)
			{
				this->nodes[current].frequency--;
				this->Size--;
				return true;
			}
			else
			{
				//case if head then we just adjust to the next node
				if (current == this->head)
				{
					int nextElem = this->nodes[current].next;
					this->nodes[nextElem].prev = -1;
					this->head = nextElem;
				}
				else
				{
					// then we adjust 2 nodes
					int nextElem = this->nodes[current].next;
					int prevElem = this->nodes[current].prev;
					this->nodes[prevElem].next = nextElem;
					this->nodes[nextElem].prev = prevElem;

				}
				// append at the start of the empty array
				if (this->firstEmpty != -1)
				{
					this->nodes[this->firstEmpty].prev = current;
				}
				this->nodes[current].next = this->firstEmpty;
				this->nodes[current].prev = -1;
				this->firstEmpty = current;
				this->Size--;
				return true;
			}
		}
		current = this->nodes[current].next;
	}
	// last element
	if (this->nodes[this->tail].info == elem)
	{
		if (this->nodes[this->tail].frequency > 1)
		{
			this->nodes[this->tail].frequency--;
			this->Size--;
			return true;
		}
		else
		{
			// if only one element in the array
			if (this->tail == this->head)
			{
				if (this->firstEmpty != -1)
				{
					this->nodes[this->firstEmpty].prev = this->head;
				}
				this->nodes[this->head].next = this->firstEmpty;
				this->nodes[this->head].prev = -1;
				this->firstEmpty = this->head;
				this->Size--;
				this->head = this->tail = -1;
				return true;
			}
			else
			{
				// otherwise we have a prev elem
				int prevElem = this->nodes[this->tail].prev;
				this->nodes[prevElem].next = -1;
				if (this->firstEmpty != -1)
				{
					this->nodes[this->firstEmpty].prev = this->tail;
				}
				this->nodes[this->tail].next = this->firstEmpty;
				this->nodes[this->tail].prev = -1;
				this->firstEmpty = this->tail;
				this->Size--;
				this->tail = prevElem;
				return true;
			}
		}
	}
	return false;
}

// BC = T(1)
// WC = T(n) - where n is the number of DLLANodes USED
// TC = O(n)


bool Bag::search(TElem elem) const {
	int current = this->head;
	if (current == -1)
	{
		return 0;
	}
	while (this->nodes[current].next != -1)
	{
		if (this->nodes[current].info == elem)
		{
			return true;
		}
		current = this->nodes[current].next;
	}
	if (this->nodes[current].info == elem)
	{
		return true;
	}
	return false;
}
// BC = T(1) -empty
// WC = T(n) - element not found, n number of DLLANodes that don't contain emptyPositions
// TC = O(n)

int Bag::nrOccurrences(TElem elem) const {
	int current = this->head;
	if (current == -1)
	{
		return 0;
	}
	while (this->nodes[current].next != -1)
	{
		if (this->nodes[current].info == elem)
		{
			return this->nodes[current].frequency;
		}
		current = this->nodes[current].next;
	}
	if (this->nodes[current].info == elem)
	{
		return this->nodes[current].frequency;
	}
	return 0;
}
// BC = T(1) -empty
// WC = T(n) - element not found, n number of DLLANodes that don't contain emptyPositions
// TC = O(n)


int Bag::size() const {
	return Size;
}
// BC = WC = TC = T(1)
vector<int> Bag::histogram() const
{
	int max_freq = 0;
	int current = this->head;
	vector<int> result;
	if (this->head == -1)
	{
		vector<int> vec;
		vec.push_back(0);
		return vec;
	}
	else
	{
		while (this->nodes[current].next != -1)
		{
			if (this->nodes[current].frequency > max_freq)
			{
				max_freq = this->nodes[current].frequency;
			}
			current = this->nodes[current].next;
		}
		if (this->nodes[current].frequency > max_freq)
		{
			max_freq = this->nodes[this->tail].frequency;
		}
		for (int i = 1; i <= max_freq + 1; i++)
		{
			result.push_back(0);
		}
		current = this->head;
		while (this->nodes[current].next != -1)
		{
			result[this->nodes[current].frequency]++;
			current = this->nodes[current].next;
		}
		result[this->nodes[this->tail].frequency]++;
	}
	return result;
}
// BC = T(1)
// WC = T(n) - n is the number of different elements
// TC = O(n)

bool Bag::isEmpty() const {
	return Size == 0;
}

// BC = WC = TC = T(1)

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
// Complexity of constructor of iterator



Bag::~Bag() {
	delete[] this->nodes;
}
// BC = WC = TC = T(1)

