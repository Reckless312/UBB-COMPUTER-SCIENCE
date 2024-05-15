#pragma once

#include <exception>
#include <string>

/// <summary>
/// Custom exception class for Repository
/// </summary>
class RepositoryException :public std::exception
{
private:
	std::string message;

public:
	RepositoryException(std::string message);
	virtual const char* what() const noexcept override;
};

/// <summary>
/// Custom exception class for Service
/// </summary>
class ServiceException :public std::exception
{
private:
	std::string message;

public:
	ServiceException(std::string message);
	virtual const char* what() const noexcept override;
};
