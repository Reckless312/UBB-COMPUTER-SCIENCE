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
	Dog() {}
	Dog(const std::string& _breed, const std::string& _name, const int& _age, const std::string& photograph);

	bool operator==(const Dog& other) const;
	std::string toString();

	std::string GetBreed() const { return breed; }
	std::string GetName() const { return name; }
	int GetAge() const { return age; }
	std::string GetPhotograph() const { return photograph; }

	void SetBreed(std::string breed) { this->breed = breed; }
	void SetName(std::string name) { this->name = name; }
	void SetAge(int age) { this->age = age; }
	void SetPhotograph(std::string photograph) { this->photograph = photograph; }

	friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
	friend std::istream& operator>>(std::istream& is, Dog& dog);
};