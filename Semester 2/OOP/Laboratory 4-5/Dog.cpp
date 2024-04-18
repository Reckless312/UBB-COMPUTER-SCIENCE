#include "Dog.h"

Dog::Dog()
{
	/*
	* Default constructor for Dog Class
	*/
	this->breed = "";
	this->age = 0;
	this->name = "";
	this->photograph = "";
}

Dog::Dog(string breed, string name, int age, Link photograph)
{
	/*
	* Initializes the components / constructor
	*/
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
}

bool Dog::operator==(Dog& other)
{
	/*
	* Over-rides the "==" operator so that a dog is the same when all of the components are equal
	*/
	if (this->breed != other.breed)
	{
		return false;
	}
	if (this->name != other.name)
	{
		return false;
	}
	if (this->age != other.age)
	{
		return false;
	}
	if (this->photograph != other.photograph)
	{
		return false;
	}
	return true;
}

string Dog::GetBreed(void)
{
	/*
	* Returns the breed;
	*/
	return this->breed;
}

string Dog::GetName(void)
{
	/*
	* Returns the name;
	*/
	return this->name;
}

int Dog::GetAge(void)
{
	/*
	* Returns the age;
	*/
	return this->age;
}

Link Dog::GetPhotograph(void)
{
	/*
	* Returns the photograph-link;
	*/
	return this->photograph;
}

void Dog::SetBreed(string breed)
{
	/*
	* Sets a new value for the breed
	*/
	this->breed = breed;
}

void Dog::SetName(string name)
{
	/*
	* Sets a new value for the name
	*/
	this->name = name;
}

void Dog::SetAge(int age)
{
	/*
	* Sets a new value for the age
	*/
	this->age = age;
}

void Dog::SetPhotograph(Link photograph)
{
	/*
	* Sets a new value for the photograph-link
	*/
	this->photograph = photograph;
}

string Dog::__String__(void)
{
	/*
	* Provides a printing method for a dog
	*/
	return string("Breed: ") + GetBreed() + string(" | Name: ") + GetName() + string(" | Age: ") + to_string(GetAge()) + string(" | Photograph Link: ") + string("\033[4m") + GetPhotograph() + string("\033[0m");
}
