#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

int SortedMap::hash_function(TKey k) const
{
	// hash function by division method
	if (k < 0)
	{
		//Case: Negative numbers
		return -(k % m);
	}
	return k % m;
}
//Complexity: WC = BC = TC = T(1)

void SortedMap::add_sort(TKey k, TValue v)
{
	//Create a new SortedNode
	SortedNode* node = new SortedNode;
	node->elem.first = k;
	node->elem.second = v;
	node->next = nullptr;
	node->prev = nullptr;
	if (this->head == nullptr)
	{
		//If there is no element in the double linked list, we initialize it
		this->head = this->tail = node;
	}
	else
	{
		//Take a "current" node and find where to insert the new element
		SortedNode* current = this->head;
		//Parse the list -> complexity+
		while (current != nullptr && this->sort_by(current->elem.first, node->elem.first))
		{
			current = current->next;
		}
		//Check if the element comes at the end of the list
		if (current == nullptr)
		{
			this->tail->next = node;
			node->prev = this->tail;
			this->tail = node;
		}
		//Check if the element comes at the start of the list
		else if (current == this->head)
		{
			current->prev = node;
			node->next = current;
			this->head = node;
		}
		//Otherwise it should come between two nodes
		else
		{
			current->prev->next = node;
			node->prev = current->prev;
			current->prev = node;
			node->next = current;
		}
	}
}
//BC = T(1) - if we add the element before the head
//WC = T(n) - if we add the element after the tail
//TC = O(n) - n is the number of elements inside the map

void SortedMap::delete_sort(TKey k)
{
	SortedNode* current = this->head;
	//Parse the list -> complexity+
	while (current != nullptr && current->elem.first != k)
	{
		current = current->next;
	}
	//Check if list is empty or if the key is not there
	if (current == nullptr)
	{
		return;
	}
	//Check if the element to be removed is the only one in the list
	if (this->head == this->tail)
	{
		delete this->head;
		this->head = this->tail = nullptr;
	}
	//Check if the element to be removed is the last one
	else if (this->tail == current)
	{
		this->tail->prev->next = nullptr;
		this->tail = this->tail->prev;
		delete current;
	}
	//Check if the element to be removed is the first one
	else if (this->head == current)
	{
		this->head->next->prev = nullptr;
		this->head = this->head->next;
		delete current;
	}
	//Otherwise we change the connections between the next and prev node of the to be deleted 
	else
	{
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
	}
}
//BC = T(1) - if the element to be removed is at the front
//WC = T(n) - if the element to be removed is not found
//TC = O(n) - n is number of elements in the map 

void SortedMap::resize_rehash()
{
	this->m = this->m * 2;
	Node** new_T = new Node * [this->m];
	//Initialize the new table with nullptr
	for (int i = 0; i < this->m; i++)
	{
		new_T[i] = nullptr;
	}
	//Rehash the elements from the map
	//Parse the old table -> complexity(m)
	for (int i = 0; i < this->m / 2; i++)
	{
		//If there are elements on the position from the original table
		if (this->T[i] != nullptr)
		{
			Node* currentNode = this->T[i];
			//Parse the linked list -> complexity(n) - n is the number of elements hashed to that position
			while (currentNode != nullptr)
			{
				int position = this->hash_function(currentNode->elem.first);
				//Add the element at the position if no element has been assigned to it
				if (new_T[position] == nullptr)
				{
					new_T[position] = currentNode;
					currentNode = currentNode->next;
					new_T[position]->next = nullptr;
				}
				else
				{
					Node* new_T_Node = new_T[position];
					//Parse the linked list from the new table -> complexity(k) - k is the number of elements hashed to
					//                                                          to that position
					while (new_T_Node->next != nullptr)
					{
						new_T_Node = new_T_Node->next;
					}
					new_T_Node->next = currentNode;
					currentNode = currentNode->next;
					(new_T_Node->next)->next = nullptr;
				}
			}
		}
	}
	delete[] this->T;
	this->T = new_T;
}
//BC = T(m) - if there is no colision in any of the table (?)
//WC = T(m * n * k) - if there is colision
//OC = O(m * n * k)

SortedMap::SortedMap(Relation r) {
	this->sort_by = r;
	m = 16;
	this->T = new Node * [this->m];
	//Initialize with nullptr so we don't keep the garbage values
	for (int i = 0; i < this->m; i++)
	{
		this->T[i] = nullptr;
	}
	//Keep size for better complexity
	this->nr_elem = 0;
	this->head = nullptr;
	this->tail = nullptr;
}
// BC = WC = TC = T(m) / m size of the array

TValue SortedMap::add(TKey k, TValue v) {
	//Check for resize and rehash
	if ((this->nr_elem / 1.0) / this->m >= 0.7)
	{
		this->resize_rehash();
	}
	int position = this->hash_function(k);
	Node* currentNode = this->T[position];
	//Check if no element has been hashed to that position
	if (currentNode == nullptr)
	{
		Node* newNode = new Node;
		newNode->elem.first = k;
		newNode->elem.second = v;
		newNode->next = nullptr;
		this->T[position] = newNode;
		this->nr_elem++;
		//Delete the element from the sorted list if found (because it might change a value / no double keys) and add 
		//                                                 the new one
		this->delete_sort(k);
		this->add_sort(k, v);
		return NULL_TVALUE;
	}
	//Parse the list ->complexity+
	while (currentNode->next != nullptr)
	{
		//Check for key
		if (currentNode->elem.first == k)
		{
			TValue old = currentNode->elem.second;
			currentNode->elem.second = v;
			//Edit sorted list
			this->delete_sort(k);
			this->add_sort(k, v);
			return old;
		}
		currentNode = currentNode->next;
	}
	//Check the tail if it contains the key
	if (currentNode->elem.first == k)
	{
		TValue old = currentNode->elem.second;
		currentNode->elem.second = v;
		//Edit sorted list
		this->delete_sort(k);
		this->add_sort(k, v);
		return old;
	}
	//Otherwise we connect the new element with the tail 
	Node* newNode = new Node;
	newNode->elem.first = k;
	newNode->elem.second = v;
	newNode->next = nullptr;
	currentNode->next = newNode;
	this->nr_elem++;
	//Edit sorted list
	this->delete_sort(k);
	this->add_sort(k, v);
	return NULL_TVALUE;
}
//Other function -> resize&rehash, add_sort, delete_sort
//BC = T(1) -> no element has been hashed to the position / is found on the first position and keeping the BC
//             from the other mandatory function calls (add_sort, delete_sort) and no resize and rehash needed
//WC = T(p + T(add_sort) + T(delete_sort) + T(resize_rehash)) - p is the number of hashed elements to a position
//OC = O(p + T(add_sort) + T(delete_sort) + T(resize_rehash))

TValue SortedMap::search(TKey k) const {
	int position = this->hash_function(k);
	Node* currentNode = this->T[position];
	//Parse the list -> complexity+
	while (currentNode != nullptr && currentNode->elem.first != k)
	{
		currentNode = currentNode->next;
	}
	//Check if we found the elem
	if (currentNode != nullptr)
	{
		return currentNode->elem.second;
	}
	return NULL_TVALUE;
}
// BC = T(1) - element is found at the start
// WC = T(n) - element not found, n is the number of hashed elements
// TC = O(n)

TValue SortedMap::remove(TKey k) {
	int position = this->hash_function(k);
	//Check for hashed elements
	if (this->T[position] == nullptr)
	{
		return NULL_TVALUE;
	}
	Node* FindToBeDeletedNode = this->T[position];
	Node* NodeBeforeToBeDeleted = this->T[position];
	//Parse the list -> complexity+
	//Find if the elem is inside list
	while (FindToBeDeletedNode != nullptr && FindToBeDeletedNode->elem.first != k)
	{
		NodeBeforeToBeDeleted = FindToBeDeletedNode;
		FindToBeDeletedNode = FindToBeDeletedNode->next;
	}
	//Check if not found
	if (FindToBeDeletedNode == nullptr)
	{
		return NULL_TVALUE;
	}
	//Find the node before the one to be deleted
	TValue val = FindToBeDeletedNode->elem.second;
	//If they are both the same from the start ( first element )
	if (NodeBeforeToBeDeleted == FindToBeDeletedNode)
	{
		//Check if no other elements are hashed
		if (FindToBeDeletedNode->next == nullptr)
		{
			this->T[position] = nullptr;
		}
		else
		{
			this->T[position] = FindToBeDeletedNode->next;
		}
	}
	else
	{
		//Check if the elem is the tail
		if (FindToBeDeletedNode->next == nullptr)
		{
			NodeBeforeToBeDeleted->next = nullptr;
		}
		else
		{
			//Otherwise connect with the one after the elem to be deleted
			NodeBeforeToBeDeleted->next = FindToBeDeletedNode->next;
		}
	}
	delete FindToBeDeletedNode;
	this->nr_elem--;
	//Edit sort list
	this->delete_sort(k);
	return val;
}

//BC = T(1) - element is the head of the hashed list and BC from the function(delete_sort)
//WC = T(n) - element is the last one in the hashed list + WC from the function(delete_sort)
//TC = O(n) + Complexity(delete_sort) 

int SortedMap::size() const {
	return nr_elem;
}
//BC = WC = TC = T(1)

bool SortedMap::isEmpty() const {
	return nr_elem == 0;
}
//BC = WC = TC = T(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
int SortedMap::addIfNotPresent(SortedMap& sm)
{
	SortedNode* current = sm.head;
	int added_pairs = 0;
	while (current != nullptr)
	{
		if (this->search(current->elem.first) == NULL_TVALUE)
		{
			this->add(current->elem.first, current->elem.second);
			added_pairs++;
		}
		current = current->next;
	}
	return added_pairs;
}
//BC = WC = TC = T(1)

SortedMap::~SortedMap() {
	for (int i = 0; i < m; i++)
	{
		if (this->T[i] != nullptr)
		{
			Node* currentNode = this->T[i];
			Node* del = currentNode;
			while (currentNode != nullptr)
			{
				currentNode = currentNode->next;
				delete del;
				del = currentNode;
			}
		}
	}
	SortedNode* current = this->tail;
	while (current != nullptr)
	{
		SortedNode* del = current;
		current = current->prev;
		delete del;
	}
}
//BC = T(m) - empty map
//WC = T(m * n)
//OC = O(m * n)
