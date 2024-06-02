#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	this->capacity = 1;
	this->capacity_used = 0;
	this->nodes = new BSTNode[this->capacity];
	this->Size = 0;
	this->relation = r;
	this->firstEmpty = 0;
	this->root = -1;
}
//Complexity : T(1) -> All cases

void SortedBag::add(TComp e) {
	//Case if no elements are in the bag
	if (this->root == -1)
	{
		this->root = this->firstEmpty;
		this->nodes[this->root].frequency = 1;
		this->nodes[this->root].info = e;
		this->nodes[this->root].right = -1;
		this->nodes[this->root].left = -1;
		this->nodes[this->root].parent = -1;
		this->firstEmpty = this->nodes[this->firstEmpty].right;
		this->Size++;
		this->capacity_used++;
		return;
	}

	int currentNode = this->root;
	int parentNode = -1;
	while (currentNode != -1)
	{
		parentNode = currentNode;
		if (this->nodes[currentNode].info == e)
		{
			//Case if the element is already in the bag
			this->nodes[currentNode].frequency++;
			this->Size++;
			return;
		}
		else if (this->relation(this->nodes[currentNode].info, e))
		{
			//If the relation is met, we go in to the right part
			currentNode = this->nodes[currentNode].right;
		}
		else
		{
			currentNode = this->nodes[currentNode].left;
		}
	}
	//Case of resize
	if (this->capacity == this->capacity_used)
	{
		this->capacity *= 2;
		BSTNode* NewNodes = new BSTNode[this->capacity];
		for (int i = 0; i < this->capacity / 2; i++)
		{
			NewNodes[i] = this->nodes[i];
		}
		for (int i = this->capacity / 2; i < this->capacity; i++)
		{
			NewNodes[i].right = i + 1;
		}
		this->firstEmpty = this->capacity / 2;
		NewNodes[this->capacity - 1].right = -1;
		delete[] this->nodes;
		this->nodes = NewNodes;
	}
	//Assign the connection from the parent
	if (this->relation(this->nodes[parentNode].info, e))
	{
		this->nodes[parentNode].right = this->firstEmpty;
	}
	else
	{
		this->nodes[parentNode].left = this->firstEmpty;
	}
	//Make connection from the new node
	int position = this->firstEmpty;
	this->firstEmpty = this->nodes[this->firstEmpty].right;
	this->nodes[position].frequency = 1;
	this->nodes[position].info = e;
	this->nodes[position].right = -1;
	this->nodes[position].left = -1;
	this->nodes[position].parent = parentNode;
	this->Size++;
	this->capacity_used++;
	return;
}
//Complexity -> T(1) - Best case if the element is the root
//           -> T(h + complexity of resize) - maximum if the resize happen, which would be a complexity of T(cap)
//                                          otherwise h - means the height of the tree
//              O(worst_case) - total complexity


bool SortedBag::remove(TComp e) {
	int currentNode = this->root;
	while (currentNode != -1 && this->nodes[currentNode].info != e)
	{
		if (this->relation(this->nodes[currentNode].info, e))
		{
			currentNode = this->nodes[currentNode].right;
		}
		else
		{
			currentNode = this->nodes[currentNode].left;
		}
	}

	if (currentNode == -1)
	{
		//Case not found
		return false;
	}

	if (this->nodes[currentNode].frequency > 1)
	{
		//Case multiple frequency
		this->nodes[currentNode].frequency--;
		this->Size--;
		return true;
	}
	
	if (this->nodes[currentNode].left == -1 && this->nodes[currentNode].right == -1)
	{
		//Case of leaf
		if (currentNode == this->root)
		{
			this->root = -1;
		}
		else
		{
			int parent = this->nodes[currentNode].parent;
			if (this->nodes[parent].left == currentNode)
			{
				this->nodes[parent].left = -1;
			}
			else
			{
				this->nodes[parent].right = -1;
			}
		}
	}
	else if (this->nodes[currentNode].left != -1 && this->nodes[currentNode].right == -1)
	{
		//Case of one connection
		if (currentNode == this->root)
		{
			int left = this->nodes[currentNode].left;
			this->nodes[left].parent = -1;
			this->root = left;
		}
		else
		{
			int parent = this->nodes[currentNode].parent;
			int left = this->nodes[currentNode].left;
			this->nodes[left].parent = parent;
			if (this->nodes[parent].left == currentNode)
			{
				this->nodes[parent].left = left;
			}
			else
			{
				this->nodes[parent].right = left;
			}
		}
	}
	else if (this->nodes[currentNode].left == -1 && this->nodes[currentNode].right != -1)
	{
		//Case of one connection but to the other side
		if (currentNode == this->root)
		{
			int right = this->nodes[currentNode].right;
			this->nodes[right].parent = -1;
			this->root = right;
		}
		else
		{
			int parent = this->nodes[currentNode].parent;
			int right = this->nodes[currentNode].right;
			this->nodes[right].parent = parent;
			if (this->nodes[parent].left == currentNode)
			{
				this->nodes[parent].left = right;
			}
			else
			{
				this->nodes[parent].right = right;
			}
		}
	}
	else
	{
		//Case of two connections
		//Find the maximum - minimum of the subtree from the node on
		int max_left = this->nodes[currentNode].left;
		while (this->nodes[max_left].right != -1)
		{
			max_left = this->nodes[max_left].right;
		}
		int left = this->nodes[currentNode].left;
		int right = this->nodes[currentNode].right;
		int parent = this->nodes[currentNode].parent;
		int parent_max_left = this->nodes[max_left].parent;
		//Connect
		this->nodes[max_left].right = right;
		this->nodes[right].parent = max_left;
		this->nodes[max_left].parent = parent;
		this->nodes[parent_max_left].right = this->nodes[max_left].left;
		//Check if the max also has some connection
		if (this->nodes[max_left].left != -1)
		{
			this->nodes[this->nodes[max_left].left].parent = parent_max_left;
		}
		//Check if the max is the children to the left of the to be deleted node
		if (left == max_left)
		{
			this->nodes[max_left].left = -1;
		}
		else
		{
			this->nodes[max_left].left = left;
			this->nodes[left].parent = max_left;
		}
		if (currentNode == this->root)
		{
			this->root = max_left;
		}
		else
		{
			if (this->nodes[parent].left == currentNode)
			{
				this->nodes[parent].left = max_left;
			}
			else
			{
				this->nodes[parent].right = max_left;
			}
		}
	}
	//Assign as empty
	this->nodes[currentNode].right = firstEmpty;
	this->firstEmpty = currentNode;
	this->Size--;
	this->capacity_used--;
	return true;
}
//Complexity -> T(1) - Best case if the node to be deleted is the root / start
//           -> T(h) - Worst case if the node is not found
//           -> O(h) - total complexity


bool SortedBag::search(TComp elem) const {
	int currentNode = this->root;
	while (currentNode != -1)
	{
		if (this->nodes[currentNode].info == elem)
		{
			return true;
		}
		else if (this->relation(this->nodes[currentNode].info, elem))
		{
			currentNode = this->nodes[currentNode].right;
		}
		else
		{
			currentNode = this->nodes[currentNode].left;
		}
	}
	return false;
}
//Complexity -> T(1) - Best case if the node to be searched is the root / start
//           -> T(h) - Worst case if the node is not found
//           -> O(h) - total complexity


int SortedBag::nrOccurrences(TComp elem) const {
	int currentNode = this->root;
	while (currentNode != -1)
	{
		if (this->nodes[currentNode].info == elem)
		{
			return this->nodes[currentNode].frequency;
		}
		else if (this->relation(this->nodes[currentNode].info, elem))
		{
			currentNode = this->nodes[currentNode].right;
		}
		else
		{
			currentNode = this->nodes[currentNode].left;
		}
	}
	return 0;
}
//Complexity -> T(1) - Best case if the node to be found is the root / start
//           -> T(h) - Worst case if the node is not found
//           -> O(h) - total complexity



int SortedBag::size() const {
	return this->Size;
}
//Complexity -> T(1) - all cases


bool SortedBag::isEmpty() const {
	return this->Size == 0;
}
int SortedBag::elementsWithMinimumFrequency() const
{
	SortedBagIterator it(*this);
	int nr = 0;
	if (!it.valid())
	{
		return 0;
	}
	TElem current, prev;
	prev = it.getCurrent();
	int freq = 0;
	int min_freq = -1;
	while (it.valid())
	{
		current = it.getCurrent();
		it.next();
		if (current == prev)
		{
			freq++;
		}
		else
		{
			if (min_freq == -1)
			{
				min_freq = freq;
				nr = 1;
			}
			else if (min_freq > freq)
			{
				min_freq = freq;
				nr = 1;
			}
			else if (min_freq == freq)
			{
				nr++;
			}
			freq = 1;
		}
		prev = current;
	}
	if (min_freq > freq)
	{
		min_freq = freq;
		nr = 1;
	}
	else if (min_freq == freq)
	{
		nr++;
	}
	return nr;
}
//Complexity -> T(1) - all cases


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
//Complexity of the constructor of the iterator


SortedBag::~SortedBag() {
	delete[] this->nodes;
}
//Complexity -> T(1) - all cases
