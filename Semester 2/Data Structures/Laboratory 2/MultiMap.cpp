#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	this->head = nullptr;
	this->tail = nullptr;
	this->number_of_elements = 0;
}

// BC = WC = TC = T(1)


void MultiMap::add(TKey c, TValue v) {
	KeyNode* current = this->head;
	while (current)
	{
		if (current->key == c)
		{
			break;
		}
		current = current->Next;
	}
	if (current == nullptr)
	{
		ValueNode* NewValueNode = new ValueNode{ v, nullptr, nullptr };
		KeyNode* NewKeyNode = new KeyNode{ c, NewValueNode,nullptr, nullptr };
		if (this->head == nullptr)
		{
			this->head = this->tail = NewKeyNode;
			NewKeyNode->Head = NewKeyNode->Tail = NewValueNode;
		}
		else
		{
			this->tail->Next = NewKeyNode;
			NewKeyNode->Prev = this->tail;
			this->tail = NewKeyNode;
		}
		NewKeyNode->Head = NewKeyNode->Tail = NewValueNode;
	}
	else
	{
		ValueNode* NewValue = new ValueNode{ v, nullptr, nullptr };
		if (current->Head == nullptr)
		{
			current->Head = current->Tail = NewValue;
		}
		else
		{
			current->Tail->Next = NewValue;
			NewValue->Prev = current->Tail;
			current->Tail = NewValue;
		}
	}
	this->number_of_elements++;
}
// BC = T(1) - Key is found | Part of the head
// WC = T(k) - Where k is the number of keys, when the key is the last one or there is no key with that value
// TC = O(k)

bool MultiMap::remove(TKey c, TValue v) {
	KeyNode* current = this->head;
	while (current) 
	{
		if (current->key == c) 
		{
			break;
		}
		current = current->Next;
	}
	if (current == nullptr)
	{
		return false;
	}
	ValueNode* current_value = current->Head;
	while (current_value) 
	{
		if (current_value->value == v) 
		{
			if (current_value == current->Head) 
			{
				current->Head = current_value->Next;
				if (current->Head != nullptr) 
				{
					current->Head->Prev = nullptr;
				}
				else 
				{
					current->Tail = nullptr;
				}
			}
			else if (current_value == current->Tail)
			{
				current->Tail = current_value->Prev;
				current_value->Prev->Next = nullptr;
			}
			else 
			{
				current_value->Prev->Next = current_value->Next;
				current_value->Next->Prev = current_value->Prev;
			}
			delete current_value;
			this->number_of_elements--;
			return true;
		}
		current_value = current_value->Next;
	}
	return false;
}
// BC = T(1) - Element found on the first key, first value
// WC = T(k + v) - k - number of keys, v - number of values for one key | removing the last element or no element is found
// TC = O(k + v)


vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> Values;
	KeyNode* current_key = this->head;
	while (current_key)
	{
		if (current_key->key == c)
		{
			break;
		}
		current_key = current_key->Next;
	}
	if (current_key == nullptr)
	{
		return Values;
	}
	ValueNode* current_value = current_key->Head;
	while (current_value)
	{
		Values.push_back(current_value->value);
		current_value = current_value->Next;
	}
	return Values;
}
// BC = T(min(k, v)) - k is number of keys, v is number of values for that key, depends on if the number of total keys is smaller than
// the possible case of finding the key in the first position but it has assigned many values
// WC = T(k + v) - maximum between number of keys and the number of values for that key
// OC = O(k + v)


int MultiMap::size() const {
	return this->number_of_elements;
}
//WC = BC = OC = T(1)


bool MultiMap::isEmpty() const {
	return this->number_of_elements == 0;
}
//WC = BC = OC = T(1)

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

//WC = BC = OC = T(1) - complexity of the constructor
int MultiMap::trimValues(int maxSize)
{
	KeyNode* CurrentKey = this->head;
	if (CurrentKey == nullptr)
	{
		return 0;
	}
	int total_removed = 0, position;
	while (CurrentKey)
	{
		position = 0;
		ValueNode* CurrentValue = CurrentKey->Head;
		while (CurrentValue)
		{	
			if (position >= maxSize)
			{
				ValueNode* SavePrevious = CurrentValue->Prev;
				this->remove(CurrentKey->key, CurrentValue->value);
				total_removed++;
				CurrentValue = SavePrevious;
			}
			position++;
			CurrentValue = CurrentValue->Next;
		}
		CurrentKey = CurrentKey->Next;
	}
	return total_removed;
}
// BC = T(1) - Map is empty
// WC = T(V) - number of total values for simplicity
// TC = O(V) 

MultiMap::~MultiMap() {
	if (size() < 1)
	{
		return;
	}
	while (this->tail)
	{
		while (this->tail->Tail)
		{
			ValueNode* del_value = this->tail->Tail;
			this->tail->Tail = this->tail->Tail->Prev;
			delete del_value;
		}
		KeyNode* del_key = this->tail;
		this->tail = this->tail->Prev;
		delete del_key;
	}
	// BC = T(1) - empty
	// WC = T(V) - where V is the total amount of values in the map
	// OC = O(V)
}

