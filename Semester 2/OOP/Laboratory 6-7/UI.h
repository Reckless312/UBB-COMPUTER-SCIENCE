#pragma once

#include "Account.h"

#include <windows.h>

class UI
{
private:
	Administrator admin;
	User user;

	void Start_Admin();
	void Start_User(int& file_choice);
	void ChooseFile(int& choice);

	void ReadDog(std::string& breed, std::string& name, int& age, std::string& photograph);
	void ReadUpdateDog(std::string& name, int& age, std::string& photograph);
	void ReadFilter(std::string& requested_breed, int& requested_age);

public:
	void Start();
};