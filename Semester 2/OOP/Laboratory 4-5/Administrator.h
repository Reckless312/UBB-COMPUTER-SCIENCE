#pragma once

#include "DynamicVector.h"
#include <cctype>
#include <iostream>

class Administrator
{
private:

	DynamicVector <TElem> Repository;
	bool OnlyLetters(string str);
	void CheckParameters(string breed, string name, int age);
	void CheckExistance(TElem Dog);
public:
	void AddDog(string breed, string name, int age, Link photograph);
	void DeleteDog(string breed, string name, int age, Link photograph);
	void UpdateDog(string breed, string name, int age, Link photograph, string new_name, int new_age, Link new_photograph);
	tuple<Dog*, int> GetCopyDogs(void);
	void GenerateEntities(void);
};