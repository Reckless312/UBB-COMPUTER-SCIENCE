#pragma once

#include "AdoptionCenter.h"
#include "Validator.h"

/// <summary>
/// Father class Account
/// Meant for verifying errors from the user and doing operations on data
/// </summary>
class Account
{
protected:
	ServiceValidator valid;
	Repository* shelter;

public:
	std::vector<Dog> GetCopy();
	void ChangeRepo(Repository* repo);
};

/// <summary>
/// Subclass of Account
/// In charge of the shelter
/// </summary>
class Administrator : public Account
{
public:
	Administrator(Repository* repo);
	void Add(std::string breed, std::string name, int age, std::string photograph);
	void Delete(std::string breed, std::string name, int age, std::string photograph);
	void Update(std::string breed, std::string name, int age, std::string photograph, std::string new_name, int new_age, std::string new_photograph);

	void ReadFromFile();
};

/// <summary>
/// Subclass of Account
/// Visitor of the shelter
/// </summary>
class User : public Account
{
public:
	User(Repository* repo);
	void Add(Dog Pet);
	std::vector<Dog> Adopt(std::vector<Dog>DogsInShelter, std::string requested_breed = "", std::string requested_age = "9999");
	void WriteInFile();
	void Open();
};