#pragma once

#include "Dog.h"
#include "Exceptions.h"

#include <vector>
#include <string>

/// <summary>
/// Validator class for service
/// </summary>
class ServiceValidator
{
public:
	bool OnlyLetters(std::string str);
	void CheckParameters(std::string breed, std::string name, int age);
	void NotEmpty(std::vector<Dog> repo);
};