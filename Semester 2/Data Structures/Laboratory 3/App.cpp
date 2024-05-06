#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main() {

	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();
	//Tests take around 2 min
	cout << "All test over" << endl;
	cout << "Extra test\n";
	Bag bag;
	bag.add(1);
	bag.add(2);
	bag.add(2);
	bag.add(3);
	bag.add(3);
	bag.add(3);
	vector<int> result;
	result = bag.histogram();
	assert(result[1] == 1);
	assert(result[2] == 1);
	assert(result[3] == 1);
	cout << "Test extra finished\n";
}