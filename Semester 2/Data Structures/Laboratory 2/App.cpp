#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"

using namespace std;


int main() {


	testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");
	MultiMap map;
	map.add(1, 2);
	map.add(1, 3);
	map.add(1, 4);
	map.add(2, 3);
	map.add(2, 4);
	cout << "Total removed: " << map.trimValues(1) << endl;
	map.add(1, 6);
	cout << "Removed after add: " << map.trimValues(1);
}