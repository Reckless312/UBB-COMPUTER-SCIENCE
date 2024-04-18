#pragma once

#include "Administrator.h"
#include "User.h"

class Tests {
private:
	Administrator admin;
	User user_of_app;
public:
	void TestAddCorrectElement(void);
	void TestAddCorrectResize(void);
	void TestAddAlreadyAdded(void);
	void TestAddWithIncorrectParameters(void);
	void TestDeleteElement(void);
	void TestDeleteNotFoundElement(void);
	void TestUpdateElement(void);
	void TestUpdateNotFoundElement(void);
	void TestGenerateElements(void);
	void TestPrintElements(void);
	void TestNoElements(void);
	void TestChangeBreed(void);
	void TestCheckComparisonOperator(void);
	void TestFilterEmptyAdoptionList(void);
	void TestAdopt5Dogs(void);
	void TestFilterDogs(void);
	void TestFilterAlreadyAdopted(void);
	void TestAll(void);
};