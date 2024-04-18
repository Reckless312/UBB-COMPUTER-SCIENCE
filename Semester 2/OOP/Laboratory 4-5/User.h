#pragma once

#include "Administrator.h"

class User
{
private:
	DynamicVector<TElem> Adoption_list;
public:
	tuple <Dog*, int> GetAdoptedDogs(void);
	tuple <Dog*, int> FilterDogs(tuple <Dog*, int> PossibleDogs, string required_breed = "none", int required_age = 10000);
	tuple <Dog*, int> FilterNotAdopted(tuple <Dog*, int> Dogs);
	void AddDog(Dog dog);
};