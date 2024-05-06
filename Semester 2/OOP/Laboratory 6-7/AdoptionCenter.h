#pragma once

#include "Dog.h"
#include "Exceptions.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

/// <summary>
/// Father class Repository
/// Meant for storing animals in the center
/// </summary>
class Repository
{
private:
	auto find(Dog Pet);

protected:
	std::vector<Dog> repo;

public:
	void Add(std::string breed, std::string name, int age, std::string photograph);
	void Delete(std::string breed, std::string name, int age, std::string photograph);
	void Update(std::string previous_breed, std::string previous_name, int previous_age,
		std::string previous_photograph, std::string new_name, int new_age, std::string new_photograph);

	int Size();
	std::vector<Dog> MakeCopy();

	virtual void Read() = 0;
	virtual void Write() = 0;
};

/// <summary>
/// Subclass of Repository
/// Meant for working with text file recordings of shelter
/// </summary>
class TextFileRepository : public Repository
{
private:
	std::string file_name;

public:
	TextFileRepository(std::string file_name);
	void Read() override;
	void Write() override;
};

/// <summary>
/// Subclass of Repository
/// Meant for working with csv recordings of shelter
/// </summary>
class CSVRepository : public Repository
{
private:
	std::string file_name;

public:
	CSVRepository();
	void Read() override;
	void Write() override;
};

/// <summary>
/// Subclass of Repository
/// Meant for working with html recordings of shelter
/// </summary>
class HTMLRepository : public Repository
{
private:
	std::string file_name;

public:
	HTMLRepository();
	void Read() override;
	void Write() override;
};