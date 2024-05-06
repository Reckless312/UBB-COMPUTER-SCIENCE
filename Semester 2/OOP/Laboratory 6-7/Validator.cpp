#include "Validator.h"

/// <summary>
/// Checks if the given string contains a number or not
/// </summary>
/// <param name="str"></param>
/// <returns></returns>
bool ServiceValidator::OnlyLetters(std::string str)
{
	for (char letter : str)
	{
		if (!isalpha(letter) && letter != ' ')
		{
			return false;
		}
	}
	return true;
}

/// <summary>
/// Checks if the parameter are correct
/// </summary>
/// <param name="breed"></param>
/// <param name="name"></param>
/// <param name="age"></param>
void ServiceValidator::CheckParameters(std::string breed, std::string name, int age)
{
	if (OnlyLetters(breed) == false)
	{
		throw ServiceException("Not a valid breed!\n");
	}
	if (OnlyLetters(name) == false)
	{
		throw ServiceException("Not a valid name!\n");
	}
	if (age < 0)
	{
		throw ServiceException("Not a valid age!\n");
	}
}

/// <summary>
/// Checks if a given repository is empty or not
/// If empty throws an error
/// </summary>
/// <param name="repo"></param>
void ServiceValidator::NotEmpty(std::vector<Dog> repo)
{
	if (repo.size() == 0)
	{
		throw ServiceException("Shelter is empty!\n");
	}
}
