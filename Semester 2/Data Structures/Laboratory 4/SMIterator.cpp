#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;


SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->currentNode = this->map.head;
}
//BC = WC = TC = T(1)

void SMIterator::first(){
	this->currentNode = this->map.head;
}
//BC = WC = TC = T(1)

void SMIterator::next(){
	if (!valid())
	{
		throw std::exception("");
	}
	this->currentNode = this->currentNode->next;
}
//BC = WC = TC = T(1)

bool SMIterator::valid() const{
	return this->currentNode != nullptr;
}
//BC = WC = TC = T(1)

TElem SMIterator::getCurrent() const{
	if (!valid())
	{
		throw std::exception("");
	}
	return this->currentNode->elem;
}
//BC = WC = TC = T(1)



