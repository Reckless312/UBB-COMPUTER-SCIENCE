#pragma once

#include <string>
#include <iostream>

/// <summary>
/// Representation of a "Dog"
/// </summary>
class Dog
{
private:
	std::string breed;
	std::string name;
	int age;
	std::string photograph;

public:
	Dog();
	Dog(std::string breed, std::string name, int age, std::string photograph);

	bool operator==(const Dog& other) const;
	std::string toString();

	std::string GetBreed();
	std::string GetName();
	int GetAge();
	std::string GetPhotograph();

	void SetBreed(std::string breed);
	void SetName(std::string name);
	void SetAge(int age);
	void SetPhotograph(std::string photograph);

	friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
	friend std::istream& operator>>(std::istream& is, Dog& dog);
};