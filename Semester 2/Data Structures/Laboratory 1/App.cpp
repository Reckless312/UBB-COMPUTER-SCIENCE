
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {


	testAll();
	testAllExtended();
	cout << "Test End" << endl;
	system("pause");
	/*Matrix m(4, 4);
	m.modify(1, 2, 5);
	m.modify(1, 3, 0);
	m.modify(0, 3, 1);
	m.modify(2, 3, 1);
	cout << "Line 0: " << m.numberOfNonZeroElems(0) <<endl;
	cout << "Line 1: " << m.numberOfNonZeroElems(1) <<endl;
	cout << "Line 2: " << m.numberOfNonZeroElems(2) <<endl;
	cout << "Line 3: " << m.numberOfNonZeroElems(3) <<endl;
	try
	{
		m.numberOfNonZeroElems(4);
	}
	catch (const std::exception&)
	{
		cout << "Erorr caught!\n";
	}
	try
	{
		m.numberOfNonZeroElems(-1);
	}
	catch (const std::exception&)
	{
		cout << "Error caught!\n";
	}*/
	
}