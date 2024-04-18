#include "User.h"

tuple <Dog*, int> User::GetAdoptedDogs(void)
{
	/*
	* Shows all the dogs in the adoption list
	*/
	int size = this->Adoption_list.GetSize();
	if (size == 0)
	{
		throw exception("Adoption list is empty!\n");
	}
	Dog* CopyOfDogs = new Dog[size];
	for (int i = 0; i < size; i++)
	{
		CopyOfDogs[i] = this->Adoption_list[i];
	}
	return make_pair(CopyOfDogs, size);
}

tuple<Dog*, int> User::FilterDogs(tuple<Dog*, int> PossibleDogs, string required_breed, int required_age)
{
	/*
	* Filters the dog in the shelter by the desired breed and age
	*/
	int number_of_dogs = get<1>(PossibleDogs), size = 0;
	if (number_of_dogs == 0)
	{
		throw exception("No dogs in the shelter");
	}
	Dog* MatchedDogs = new Dog[number_of_dogs];
	Dog* Dogs = get<0>(PossibleDogs);
	for (int i = 0; i < number_of_dogs; i++)
	{
		Dog CurrentDog = Dogs[i];
		if ((CurrentDog.GetBreed() == required_breed || required_breed == "none") && CurrentDog.GetAge() < required_age)
		{
			MatchedDogs[size++] = CurrentDog;
		}
	}
	if (size == 0)
	{
		delete[] MatchedDogs;
		throw exception("No dogs meet the criteria!\n");
	}
	return make_pair(MatchedDogs, size);
}

tuple <Dog*, int> User::FilterNotAdopted(tuple<Dog*, int> Dogs)
{
	/*
	* Filters the dog so that they don't appear already in the adoption list
	*/
	tuple <Dog*, int> AdoptionList;
	int size = get<1>(Dogs), new_size = 0, size_of_adoption_list;
	bool found;
	try
	{
		AdoptionList = this->GetAdoptedDogs();
	}
	catch (const std::exception&)
	{
		return Dogs;
	}
	size_of_adoption_list = get<1>(AdoptionList);
	Dog* FilteredDogs = get<0>(Dogs);
	Dog* AdoptedDogs = get<0>(AdoptionList);
	for (int i = 0; i < size; i++)
	{
		found = false;
		for (int j = 0; j < size_of_adoption_list; j++)
		{
			if (FilteredDogs[i] == AdoptedDogs[j])
			{
				found = true;
			}
		}
		if (found == false)
		{
			FilteredDogs[new_size++] = FilteredDogs[i];
		}
	}
	delete[] get<0>(AdoptionList);
 	if (new_size == 0)
	{
		throw exception("No more dogs available!\n");
	}
	return make_pair(FilteredDogs, new_size);
}

void User::AddDog(Dog dog)
{
	/*
	* Adds a dog in the adoption list
	*/
	this->Adoption_list.Add(dog);
}
