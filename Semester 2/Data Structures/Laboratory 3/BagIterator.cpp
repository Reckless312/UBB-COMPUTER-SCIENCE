#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->CurrentValue = this->bag.head;
	if (this->CurrentValue != -1)
	{
		this->CurrentFrequency = this->bag.nodes[this->CurrentValue].frequency;
	}
	else
	{
		this->CurrentFrequency = 0;
	}
}
// BC = WC = TC = T(1)

void BagIterator::first() {
	this->CurrentValue = this->bag.head;
	if (this->CurrentValue != -1)
	{
		this->CurrentFrequency = this->bag.nodes[this->CurrentValue].frequency;
	}
	else
	{
		this->CurrentFrequency = 0;
	}
}
// BC = WC = TC = T(1)


void BagIterator::next() {
	if (!valid()) {
		throw std::exception();
	}
	if (this->CurrentFrequency == 1)
	{
		this->CurrentValue = this->bag.nodes[this->CurrentValue].next;
		if (this->CurrentValue != -1)
		{
			this->CurrentFrequency = this->bag.nodes[this->CurrentValue].frequency;
		}
	}
	else
	{
		this->CurrentFrequency--;
	}
	
}
// BC = WC = TC = T(1)


bool BagIterator::valid() const {
	return this->CurrentValue != -1;
}
// BC = WC = TC = T(1)



TElem BagIterator::getCurrent() const
{
	if (!valid()) {
		throw std::exception();
	}
	return this->bag.nodes[CurrentValue].info;
}
// BC = WC = TC = T(1)
