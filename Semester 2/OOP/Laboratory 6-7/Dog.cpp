#include "Dog.h"

/// <summary>
/// Default constructor for a dog
/// </summary>
Dog::Dog()
{
	this->breed = "";
	this->age = 0;
	this->name = "";
	this->photograph = "";
}


/// <summary>
/// Constructor for a god
/// </summary>
/// <param name="breed"></param> Assigned breed
/// <param name="name"></param> Assigned name
/// <param name="age"></param> Assigned age
/// <param name="photograph"></param> Assigned link / photograph
Dog::Dog(std::string breed, std::string name, int age, std::string photograph)
{
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
}


/// <summary>
/// Operator "=="
/// A dog is the same as "another" one if all of it's attributes are the same
/// </summary>
/// <param name="other"></param> -> Dog to check with
/// <returns></returns>
bool Dog::operator==(const Dog& other) const
{
	if (this->breed == other.breed && this->name == other.name &&
		this->age == other.age && this->photograph == other.photograph)
	{
		return true;
	}
	return false;
}


/// <summary>
/// Readable format for a dog
/// </summary>
/// <returns></returns>
std::string Dog::toString()
{
	return std::string("Dog: ") + this->name + std::string(" | Breed: ") + this->breed + std::string(" | Age: ") + std::to_string(this->age) + std::string(" | Photograph: ") + std::string("\033[4m") + this->photograph + std::string("\033[0m");
}

/// <summary>
/// Gets the breed of a dog
/// </summary>
/// <returns></returns>
std::string Dog::GetBreed()
{
	return this->breed;
}

/// <summary>
/// Gets the name of a dog
/// </summary>
/// <returns></returns>
std::string Dog::GetName()
{
	return this->name;
}

/// <summary>
/// Gets the age of a dog
/// </summary>
/// <returns></returns>
int Dog::GetAge()
{
	return this->age;
}


/// <summary>
/// Gets the link of the photograph
/// </summary>
/// <returns></returns>
std::string Dog::GetPhotograph()
{
	return this->photograph;
}


/// <summary>
/// Sets the breed of a dog
/// </summary>
/// <param name="breed"></param> New breed
void Dog::SetBreed(std::string breed)
{
	this->breed = breed;
}

/// <summary>
/// Sets the name of a dog
/// </summary>
/// <param name="name"></param> New name
void Dog::SetName(std::string name)
{
	this->name = name;
}

/// <summary>
/// Sets the age of a dog
/// </summary>
/// <param name="age"></param> New age
void Dog::SetAge(int age)
{
	this->age = age;
}

/// <summary>
/// Sets the link of a dog
/// </summary>
/// <param name="photograph"></param> New link
void Dog::SetPhotograph(std::string photograph)
{
	this->photograph = photograph;
}

/// <summary>
/// Overload "<<" operator
/// </summary>
/// <param name="os"></param>
/// <param name="dog"></param> Wanted dog to write
/// <returns></returns>
std::ostream& operator<<(std::ostream& os, const Dog& dog)
{
	return os << dog.breed << " " << dog.name << " " << dog.age << " " << dog.photograph;
}

/// <summary>
/// Overload ">>" operator
/// </summary>
/// <param name="is"></param>
/// <param name="dog"></param> Wanted dog to read
/// <returns></returns>
std::istream& operator>>(std::istream& is, Dog& dog)
{
	return is >> dog.breed >> dog.name >> dog.age >> dog.photograph;
}
