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

Administrator::Administrator(Repository* repo)
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
	std::unique_ptr<Action> action = std::make_unique<ActionAdd>(this->shelter, breed, name, age, photograph);
	this->undo_storage.push_back(std::move(action));
	this->shelter->Write();
	this->redo_storage.clear();
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
	std::unique_ptr<Action> action = std::make_unique<ActionRemove>(this->shelter, breed, name, age, photograph);
	this->undo_storage.push_back(std::move(action));
	this->shelter->Write();
	this->redo_storage.clear();
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
	std::unique_ptr<Action> action = std::make_unique<ActionUpdate>(this->shelter, breed, name, age, photograph, new_name, new_age, new_photograph);
	this->undo_storage.push_back(std::move(action));
	this->shelter->Write();
	this->redo_storage.clear();
}

void Administrator::Undo()
{
	if (this->undo_storage.size() == 0)
	{
		throw ServiceException("No undo available!\n");
	}
	std::unique_ptr<Action> last = std::move(this->undo_storage.back());
	this->undo_storage.pop_back();
	last->executeUndo();
	this->redo_storage.push_back(std::move(last));
	this->shelter->Write();
}

void Administrator::Redo()
{
	if (this->redo_storage.size() == 0)
	{
		throw ServiceException("No redo available!\n");
	}
	std::unique_ptr<Action> last = std::move(this->redo_storage.back());
	this->redo_storage.pop_back();
	last->executeRedo();
	this->undo_storage.push_back(std::move(last));
	this->shelter->Write();
}

/// <summary>
/// Allows for the data to be read
/// </summary>
void Administrator::ReadFromFile()
{
	this->shelter->Read();
}

User::User(Repository* repo)
{
	this->shelter = repo;
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
std::vector<Dog> User::Adopt(std::vector<Dog>DogsInShelter, std::string requested_breed, std::string requested_age)
{
	int age = 9999;
	this->valid.CorrectAge(requested_age);
	if (requested_age != "")
	{
		age = std::stoi(requested_age);
	}
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
		if ((Pet.GetBreed() == requested_breed || requested_breed == "") && Pet.GetAge() < age)
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

void User::Open()
{
	this->shelter->Open();
}
