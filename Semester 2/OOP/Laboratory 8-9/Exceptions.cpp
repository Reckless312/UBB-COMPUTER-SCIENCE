#include "Exceptions.h"

/// <summary>
/// Constructor for the custom exception
/// </summary>
/// <param name="message"></param> Specifications of the error
RepositoryException::RepositoryException(std::string message)
{
	this->message = message;
}

/// <summary>
/// Allows the exception to be read
/// </summary>
/// <returns></returns>
const char* RepositoryException::what() const noexcept
{
	return this->message.c_str();
}

/// <summary>
/// Constructor for the custom exception
/// </summary>
/// <param name="message"></param> Specifications of the error
ServiceException::ServiceException(std::string message)
{
	this->message = message;
}

/// <summary>
/// Allows the exception to be read
/// </summary>
/// <returns></returns>
const char* ServiceException::what() const noexcept
{
	return this->message.c_str();
}
