#include "DynamicVector.h"

template <class T> void DynamicVector<T>::Resize()
{
	/*
	* Resizes vector if full
	*/
	this->capacity *= 2;
	T* new_elements = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
	{
		new_elements[i] = this->elements[i];
	}
	delete[] this->elements;
	this->elements = new_elements;
}

template <class T> int DynamicVector<T>::FindInVector(T Element)
{
	/*
	* Gets the position of the dog in the vector, otherwise returns the size
	*/
	int position = 0;
	while (position < size)
	{
		if (this->elements[position] == Element)
		{
			break;
		}
		position++;
	}
	if (position == size)
	{
		throw exception("No such dog exists!\n");
	}
	return position;
}

template <class T> DynamicVector<T>::DynamicVector()
{
	/*
	* Builds a vector
	*/
	this->capacity = 1;
	this->size = 0;
	elements = new T[this->capacity];
}

template <class T> DynamicVector<T>::~DynamicVector()
{
	/*
	* Deconstructs the vector
	*/
	delete[] this->elements;
}

template <class T> void DynamicVector<T>::Add(T Element)
{
	/*
	* Adds an element inside
	*/
	if (this->capacity == this->size)
	{
		Resize();
	}
	this->elements[this->size] = Element;
	this->size++;
}

template <class T> int DynamicVector<T>::GetSize(void)
{
	/*
	* Returns the current size
	*/
	return this->size;
}

template <class T> void DynamicVector<T>::Delete(T Element)
{
	/*
	* Deletes an element
	*/
	int position = FindInVector(Element);
	for (int i = position; i < this->size - 1; i++)
	{
		swap(this->elements[i], this->elements[i + 1]);
	}
	this->size -= 1;
}

template <class T> void DynamicVector<T>::Update(T Element, string new_name, int new_age, Link new_photograph)
{
	/*
	* Updates an element
	*/
	int position = FindInVector(Element);
	this->elements[position].SetName(new_name);
	this->elements[position].SetAge(new_age);
	this->elements[position].SetPhotograph(new_photograph);
}

template<class T>
T DynamicVector<T>::operator[](int position)
{
	return this->elements[position];
}

template class DynamicVector<Dog>;