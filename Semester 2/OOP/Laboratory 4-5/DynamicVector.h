#pragma once
#include "Dog.h"
#include <exception>
#include <tuple>

typedef Dog TElem;

template <class T>

class DynamicVector
{
private:
	int size;
	int capacity;
	T* elements;

	void Resize();
	int FindInVector(T Element);
public:
	DynamicVector();
	~DynamicVector();
	void Add(T Element);
	int GetSize(void);
	void Delete(T Element);
	void Update(T Element, string new_name, int new_age, Link new_photograph);
	T operator[](int position);
};

