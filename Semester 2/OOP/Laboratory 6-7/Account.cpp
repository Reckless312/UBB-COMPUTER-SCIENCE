#include "Account.h"

/// <summary>
/// Gets the repo as a copy
/// Throws exception if no animal in the shelter
/// </summary>
/// <returns></returns>
std::vector<Dog> Account::GetCopy()
{
	std::vector<Dog>Copy = this->shelter->MakeCopy();
	this->valid.NotEmpty(Copy);
	return Copy;
}

/// <summary>
/// Changes the format of the repository
/// </summary>
/// <param name="repo"></param>
void Account::ChangeRepo(Repository* repo)
{
	this->shelter = repo;
}

/// <summary>
/// Checks if the parameters are okay and proceeds to call Add to shelter
/// </summary>
/// <param name="breed"></param>
/// <param name="name"></param>
/// <param name="age"></param>
/// <param name="photograph"></param>
void Administrator::Add(std::string breed, std::string name, int age, std::string photograph)
{
	this->valid.CheckParameters(breed, name, age);
	this->shelter->Add(breed, name, age, photograph);
}

/// <summary>
/// Checks if the parameters are okay and proceeds to call Delete to shelter
/// </summary>
/// <param name="breed"></param>
/// <param name="name"></param>
/// <param name="age"></param>
/// <param name="photograph"></param>
void Administrator::Delete(std::string breed, std::string name, int age, std::string photograph)
{
	this->valid.CheckParameters(breed, name, age);
	this->shelter->Delete(breed, name, age, photograph);
}

/// <summary>
/// Checks if the parameters are okay and proceeds to call Update to shelter
/// </summary>
/// <param name="breed"></param>
/// <param name="name"></param>
/// <param name="age"></param>
/// <param name="photograph"></param>
void Administrator::Update(std::string breed, std::string name, int age, std::string photograph, std::string new_name, int new_age, std::string new_photograph)
{
	this->valid.CheckParameters(breed, name, age);
	this->valid.CheckParameters(breed, new_name, new_age);
	this->shelter->Update(breed, name, age, photograph, new_name, new_age, new_photograph);
}

/// <summary>
/// Allows for the data to be read
/// </summary>
void Administrator::ReadFromFile()
{
	this->shelter->Read();
}

/// <summary>
/// Adds a dog in the adoption list
/// </summary>
/// <param name="Pet"></param>
void User::Add(Dog Pet)
{
	this->shelter->Add(Pet.GetBreed(), Pet.GetName(), Pet.GetAge(), Pet.GetPhotograph());
}

/// <summary>
/// Present the available adoption list
/// </summary>
/// <param name="DogsInShelter"></param> The dogs in the shelter
/// <param name="requested_breed"></param> optional
/// <param name="requested_age"></param> optional
/// <returns></returns>
std::vector<Dog> User::Adopt(std::vector<Dog>DogsInShelter, std::string requested_breed, int requested_age)
{
	std::vector<Dog> DogsNotAdopted, DogsFiltered, DogsAdopted;
	try
	{
		DogsAdopted = this->GetCopy();
	}
	catch (const ServiceException&)
	{
		
	}
	this->valid.NotEmpty(DogsInShelter);
	for (Dog Pet : DogsInShelter)
	{
		if (std::find(DogsAdopted.begin(), DogsAdopted.end(), Pet) == DogsAdopted.end())
		{
			DogsNotAdopted.push_back(Pet);
		}
	}
	for (Dog Pet : DogsNotAdopted)
	{
		if ((Pet.GetBreed() == requested_breed || requested_breed == "") && Pet.GetAge() < requested_age)
		{
			DogsFiltered.push_back(Pet);
		}
	}
	if (DogsFiltered.size() == 0)
	{
		throw ServiceException("No dogs have been found!\n");
	}
	return DogsFiltered;
}

/// <summary>
/// Allows to write the adoption list in a file
/// </summary>
void User::WriteInFile()
{
	this->shelter->Write();
}
