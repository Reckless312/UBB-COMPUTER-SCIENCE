#pragma once
#include <exception>
#include <algorithm>
#include <iostream>

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
	int nrLine;
	int nrCol;
	int* Line;
	int* Cols;
	int Capacity;
	int Size;
	TElem* Value;

	TElem GetValue(int i, int j);
	TElem GetPosition(int i, int j);
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	int numberOfNonZeroElems(int line)const;

};
