#pragma once

#include "Administrator.h"
#include "User.h"
#include <windows.h>

class UI
{
private:
	Administrator Administrator;
	User User_of_App;
	void Admin(void);
	void User(void);
	void ReadDog(string& breed, string& name, int& age, string& photograph);
	void ReadUpdateDog(string& new_name, int& new_age, string& new_photograph);
	void ReadFilter(string& breed, int& age);
	void main_commands_admin();
	void main_commands_start();
	void main_commands_user();
	void exit_mode_message();
public:
	void Start(void);
};
