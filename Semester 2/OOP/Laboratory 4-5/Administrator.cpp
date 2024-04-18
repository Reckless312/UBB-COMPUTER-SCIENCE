#include "Administrator.h"

bool Administrator::OnlyLetters(string str)
{
	/*
	* Check if the input is contains only letters
	*/
	for (char letter : str)
	{
		if (!isalpha(letter) && letter != ' ')
		{
			return false;
		}
	}
	return true;
}

void Administrator::CheckParameters(string breed, string name, int age)
{
	/*
	* Checks if the parameters are correct, otherwise throws exception
	*/
	if (OnlyLetters(breed) == false)
	{
		throw exception("Not a valid breed!\n");
	}
	if (OnlyLetters(name) == false)
	{
		throw exception("Not a valid name!\n");
	}
	if (age < 0)
	{
		throw exception("Not a valid age!\n");
	}
}

void Administrator::CheckExistance(TElem Dog)
{
	/*
	* Checks if the same dog already exists
	*/
	for (int i = 0, length = this->Repository.GetSize(); i < length; i++)
	{
		if (this->Repository[i] == Dog)
		{
			throw exception("Dog already exists!\n");
		}
	}
	return;
}

void Administrator::AddDog(string breed, string name, int age, Link photograph)
{
	/*
	* Adds a dog in the repository
	*/
	CheckParameters(breed, name, age);
	TElem Dog(breed, name, age, photograph);
	CheckExistance(Dog);
	this->Repository.Add(Dog);
}

void Administrator::DeleteDog(string breed, string name, int age, Link photograph)
{
	/*
	* Deletes a dog from the repository
	*/
	CheckParameters(breed, name, age);
	TElem Dog(breed, name, age, photograph);
	this->Repository.Delete(Dog);
}

void Administrator::UpdateDog(string breed, string name, int age, Link photograph, string new_name, int new_age, Link new_photograph)
{
	/*
	* Updates a dog from the repository
	*/
	CheckParameters(breed, name, age);
	CheckParameters(breed, new_name, new_age);
	TElem Dog(breed, name, age, photograph);
	this->Repository.Update(Dog, new_name, new_age, new_photograph);
}

tuple <Dog*, int> Administrator::GetCopyDogs(void)
{
	/*
	* Get a copy of the dogs in the repository
	* Memory must be freed after use
	*/
	int size = this->Repository.GetSize();
	if (size == 0)
	{
		throw exception("Shelter is empty!\n");
	}
	Dog* DogsInShelter = new Dog[size];
	for (int i = 0; i < size; i++)
	{
		DogsInShelter[i] = this->Repository[i];
	}
	return make_pair(DogsInShelter, size);
}

void Administrator::GenerateEntities(void)
{
	/*
	* Generating 10 dogs
	*/
	string breed_1 = "Golden Retriever", breed_2 = "Siberian Husky", breed_3 = "Labrador Retriever", breed_4 = "German Shepherd", breed_5 = "Samoyed", breed_6 = "Austalian Shepherd", breed_7 = "Poodle", breed_8 = "Saluki", breed_9 = "Irish Setter", breed_10 = "Cane Corso";
	string name_1 = "Charlie", name_2 = "Luna", name_3 = "Max", name_4 = "Daisy", name_5 = "Cooper", name_6 = "Lucy", name_7 = "Milo", name_8 = "Lily", name_9 = "Buddy", name_10 = "Bella";
	int age_1 = 5, age_2 = 3, age_3 = 6, age_4 = 6, age_5 = 9, age_6 = 2, age_7 = 0, age_8 = 1, age_9 = 4, age_10 = 3;
	Link photograph_1 = "https://unsplash.com/s/photos/golden-retriever", photograph_2 = "https://unsplash.com/s/photos/siberian-husky", photograph_3 = "https://unsplash.com/s/photos/labrador-retriever", photograph_4 = "https://unsplash.com/s/photos/german-shepherd", photograph_5 = "https://unsplash.com/s/photos/samoyed";
	Link photograph_6 = "https://unsplash.com/s/photos/australian-shepherd", photograph_7 = "https://unsplash.com/s/photos/poodle", photograph_8 = "https://unsplash.com/s/photos/saluki", photograph_9 = "https://unsplash.com/s/photos/irish-setter", photograph_10 = "https://unsplash.com/s/photos/cane-corso";
	TElem Dog_1(breed_1, name_1, age_1, photograph_1);
	TElem Dog_2(breed_2, name_2, age_2, photograph_2);
	TElem Dog_3(breed_3, name_3, age_3, photograph_3);
	TElem Dog_4(breed_4, name_4, age_4, photograph_4);
	TElem Dog_5(breed_5, name_5, age_5, photograph_5);
	TElem Dog_6(breed_6, name_6, age_6, photograph_6);
	TElem Dog_7(breed_7, name_7, age_7, photograph_7);
	TElem Dog_8(breed_8, name_8, age_8, photograph_8);
	TElem Dog_9(breed_9, name_9, age_9, photograph_9);
	TElem Dog_10(breed_10, name_10, age_10, photograph_10);
	this->Repository.Add(Dog_1);
	this->Repository.Add(Dog_2);
	this->Repository.Add(Dog_3);
	this->Repository.Add(Dog_4);
	this->Repository.Add(Dog_5);
	this->Repository.Add(Dog_6);
	this->Repository.Add(Dog_7);
	this->Repository.Add(Dog_8);
	this->Repository.Add(Dog_9);
	this->Repository.Add(Dog_10);
}
