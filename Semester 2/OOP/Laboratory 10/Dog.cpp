#include "Dog.h"

/// <summary>
/// Constructor for a dog
/// </summary>
/// <param name="breed"></param> Assigned breed
/// <param name="name"></param> Assigned name
/// <param name="age"></param> Assigned age
/// <param name="photograph"></param> Assigned link / photograph
Dog::Dog(const std::string& _breed, const std::string& _name, const int& _age, const std::string& photograph): breed(_breed), name(_name), age(_age), photograph(photograph)
{
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
