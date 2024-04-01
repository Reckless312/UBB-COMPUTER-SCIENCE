#include "Matrix.h"
#include <exception>
#include <stdlib.h>
using namespace std;


TElem Matrix::GetValue(int i, int j)
{
	for (int k = this->Line[i], length = this->Line[i + 1]; k < length; k++)
	{
		if (this->Cols[k] == j)
		{
			return this->Value[k];
		}
	}
	return NULL_TELEM;
}
// Helping function | Complexity: BC = WC = TC = Teta(k) | where k is the length of the segment from [A,B) | the columns of a specific line

TElem Matrix::GetPosition(int i, int j)
{
	for (int k = this->Line[i], length = this->Line[i + 1]; k < length; k++)
	{
		if (this->Cols[k] == j)
		{
			return k;
		}
	}
	return NULL_TELEM;
}
// Helping function | Complexity: BC = WC = TC = Teta(k) | where k is the length of the segment from [A,B) | the columns of a specific line

Matrix::Matrix(int nrLines, int nrCols) {

	if (nrLines <= 0)
	{
		throw exception();
	}
	if (nrCols <= 0)
	{
		throw exception();
	}
	this->nrLine = nrLines;
	this->nrCol = nrCols;
	this->Line = new int[this->nrLine + 1];
	for (int i = 0, length = this->nrLine; i <= length; i++)
	{
		this->Line[i] = 0;
	}
	this->Cols = new int[1];
	this->Capacity = 1;
	this->Size = 0;
	this->Value = new TElem[1];
}
// Complexity: BC = WC = TC = Teta(nrLine) for initialization;

int Matrix::nrLines() const {
	return this->nrLine;
}
// Complexity: BC = WC = TC = Teta(1)


int Matrix::nrColumns() const {
	return this->nrCol;
}
// Complexity: BC = WC = TC = Teta(1)


TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= this->nrLine)
	{
		throw exception();
	}
	if (j < 0 || j >= this->nrCol)
	{
		throw exception();
	}
	int begin_line = this->Line[i], finish_line = this->Line[i + 1];
	if (begin_line == finish_line)
	{
		return NULL_TELEM;
	}
	for (int k = begin_line; k < finish_line; k++)
	{
		if (this->Cols[k] == j)
		{
			return this->Value[k];
		}
	}
	return NULL_TELEM;
}
// Complexity BC = WC = TC = Teta(k), where k is the length of the segment [A, B), a segment which represents where
// the column number begins and ends in the Cols array (of a specific row) 

TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= this->nrLine)
	{
		throw exception();
	}
	if (j < 0 || j >= this->nrCol)
	{
		throw exception();
	}
	if (GetValue(i, j) == NULL_TELEM && e == NULL_TELEM)
	{
		return NULL_TELEM;
	}
	if (GetValue(i, j) != NULL_TELEM && e != NULL_TELEM)
	{
		TElem previous_value = GetValue(i, j);
		this->Value[GetPosition(i, j)] = e;
		return previous_value;
	}
	if (GetValue(i, j) == NULL_TELEM && e != NULL_TELEM)
	{
		if (this->Capacity == this->Size)
		{
			this->Capacity*= 2;
			int* NewCols = new int[this->Capacity];
			for (int k = 0; k < this->Size; k++)
			{
				NewCols[k] = this->Cols[k];
			}
			delete[] this->Cols;
			this->Cols = NewCols;
			int* NewValues = new TElem[this->Capacity];
			for (int k = 0; k < this->Size; k++)
			{
				NewValues[k] = this->Value[k];
			}
			delete[] this->Value;
			this->Value = NewValues;
		}
		if (this->Size == 0)
		{
			this->Cols[0] = j;
			this->Size++;
			for (int k = i + 1; k <= this->nrLine; k++)
			{
				this->Line[k]++;
			}
			this->Value[0] = e;
			return NULL_TELEM;
		}
		else
		{
			int position = this->Line[i];
			bool was_last = false;
			for (int k = this->Line[i], length = this->Line[i + 1]; k < length; k++)
			{
				if (this->Cols[k] > j)
				{
					position = k;
					break;
				}
				if (k == length - 1)
				{
					was_last = true;
				}
			}
			if (was_last == true)
			{
				position = this->Line[i + 1];
			}
			for (int k = this->Size; k > position; k--)
			{
				swap(this->Cols[k], this->Cols[k - 1]);
				swap(this->Value[k], this->Value[k - 1]);
			}
			this->Cols[position] = j;
			this->Size++;
			for (int k = i + 1; k <= this->nrLine; k++)
			{
				this->Line[k]++;
			}
			this->Value[position] = e;
			return NULL_TELEM;
		}
	}
	if (GetValue(i, j) != NULL_TELEM && e == NULL_TELEM)
	{
		TElem PreviousValue = GetValue(i, j);
		int position = this->Line[i];
		for (int k = this->Line[i], length = this->Line[i + 1]; k < length; k++)
		{
			if (this->Cols[k] == j)
			{
				position = k;
				break;
			}
		}
		for (int k = position; k < this->Size - 1; k++)
		{
			swap(this->Cols[k], this->Cols[k + 1]);
			swap(this->Value[k], this->Value[k + 1]);
		}
		this->Size--;
		for (int k = i + 1; k <= this->nrLine; k++)
		{
			this->Line[k]--;
		}
		return PreviousValue;
	}
}
// BC = Teta(1) | Returns the NULL_TELEM
// WC = Teta(Colsize + NrLine + k) The maximum of these values, where Colsize is the current amount of elements in
// the Cols array, k is the segment like in the previous function, NrLine is the total amound of lines of the matrix
// TC = O(Colsize + Nrline + k)
int Matrix::numberOfNonZeroElems(int line) const
{
	if (nrLines() - 1 < line || line < 0)
	{
		throw exception();
	}
	int number_of_elems = 0;
	for (int i = this->Line[line], length = this->Line[line + 1]; i < length; i++)
	{
		number_of_elems++;
	}
	return number_of_elems;
}
// BC = WC = TC = Teta(k), where k is the length of the segment from [A,B) | the columns of a specific line


