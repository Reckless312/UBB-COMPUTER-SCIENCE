#include "UI.h"

void UI::Admin(void)
{
	string breed, name, photograph, new_name, new_photograph;
	int admin_command, age, new_age, exit_flag = 0;
	while (true)
	{
		this->main_commands_admin();
		cin >> admin_command;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input!\n";
			continue;
		}
		switch (admin_command)
		{
		case 1:
			try
			{
				ReadDog(breed, name, age, photograph);
				this->Administrator.AddDog(breed, name, age, photograph);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 2:
			try
			{
				ReadDog(breed, name, age, photograph);
				this->Administrator.DeleteDog(breed, name, age, photograph);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 3:
			try
			{
				ReadDog(breed, name, age, photograph);
				ReadUpdateDog(new_name, new_age, new_photograph);
				this->Administrator.UpdateDog(breed, name, age, photograph, new_name, new_age, new_photograph);
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 4:
			try
			{
				tuple<Dog*, int> DogsInShelter = this->Administrator.GetCopyDogs();
				Dog* Dogs = get<0>(DogsInShelter);
				int size = get<1>(DogsInShelter);
				for (int i = 0; i < size; i++)
				{
					cout << Dogs[i].__String__() << endl;
				}
				delete[] Dogs;
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 0:
			exit_flag = 1;
			break;
		default:
			cout << "Invalid command!\n";
			break;
		}
		if (exit_flag == 1)
		{
			break;
		}
		cout << endl;
	}
	return;
}

void UI::User(void)
{
	tuple<Dog*, int> DogsInShelter = this->Administrator.GetCopyDogs();
	tuple<Dog*, int> FilteredDogs;
	int user_command, desired_age, position, size, exit_flag = 0;
	string filter_command, desired_breed, browser_command, answer;
	Dog CurrentDog;
	Link url;
	while (true)
	{
		this->main_commands_user();
		cin >> user_command;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input!\n";
			continue;
		}
		switch (user_command)
		{
		case 1:
			try
			{
				this->ReadFilter(desired_breed, desired_age);
				if (desired_breed == "")
				{
					FilteredDogs = this->User_of_App.FilterDogs(DogsInShelter);
				}
				else
				{
					FilteredDogs = this->User_of_App.FilterDogs(DogsInShelter, desired_breed, desired_age);
				}
			}
			catch (const std::exception& e)
			{
				cout << e.what();
				continue;
			}
			position = 0;
			while (true)
			{
				try
				{
					FilteredDogs = this->User_of_App.FilterNotAdopted(FilteredDogs);
				}
				catch (const std::exception& e)
				{
					cout << e.what();
					break;
				}
				Dog* Fil_Dogs = get<0>(FilteredDogs);
				size = get<1>(FilteredDogs);
				if (position > size - 1)
				{
					position = 0;
				}
				CurrentDog = Fil_Dogs[position];
				cout << CurrentDog.__String__() << endl;
				url = CurrentDog.GetPhotograph();
				browser_command = "start " + url;
				system(browser_command.c_str());
				cout << "Do you want to adopt this dog ? -> yes | no | exit\n";
				cin >> answer;
				if (answer == "yes")
				{
					this->User_of_App.AddDog(CurrentDog);
					cout << "Dog adopted!\n";
					position--;
				}
				else if (answer == "no")
				{
					cout << "Showing next dog...\n";
				}
				else if (answer == "exit")
				{
					cout << "Closing adoption mode...\n";
					break;
				}
				else
				{
					cout << "Invalid command!\n";
					cout << "Showing next dog!\n";
				}
				position++;
			}
			delete[] get<0>(FilteredDogs);
			break;
		case 2:
			try
			{
				tuple <Dog*, int> DogsInAdoptionList = this->User_of_App.GetAdoptedDogs();
				Dog* Dogs = get<0>(DogsInAdoptionList);
				for (int i = 0, size = get<1>(DogsInAdoptionList); i < size; i++)
				{
					cout << Dogs[i].__String__() << endl;
				}
				delete[] Dogs;
			}
			catch (const std::exception& e)
			{
				cout << e.what();
			}
			break;
		case 0:
			exit_flag = 1;
			break;
		default:
			cout << "Invalid input!\n";
			break;
		}
		if (exit_flag == 1)
		{
			break;
		}
	}
	delete[] get<0>(DogsInShelter);
}

void UI::ReadDog(string& breed, string& name, int& age, string& photograph)
{
	cout << "Insert breed: ";
	getline(cin >> ws, breed);
	cout << "Insert name: ";
	cin >> name;
	cout << "Insert age: ";
	cin >> age;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		throw exception("Age must be an integer!\n");
	}
	cout << "Insert photograph-link: ";
	cin >> photograph;
}

void UI::ReadUpdateDog(string& new_name, int& new_age, string& new_photograph)
{
	cout << "Insert new name: ";
	cin >> new_name;
	cout << "Insert new age: ";
	cin >> new_age;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		throw exception("Age must be an integer!\n");
	}
	cout << "Insert new photograph-link: ";
	cin >> new_photograph;
}

void UI::ReadFilter(string& breed, int& age)
{
	cout << "Insert breed: ";
	cin.ignore();
	getline(cin, breed);
	if (breed == "")
	{
		return;
	}
	cout << "Insert age: ";
	cin >> age;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore();
		throw exception("Age must be an integer!\n");
	}
}

void UI::main_commands_admin()
{
	cout << "Select desired operations:\n";
	cout << "Add a dog to the adoption center | 1\n";
	cout << "Remove a dog from the adoption center | 2\n";
	cout << "Update a dog's name, age and link to the photograph | 3\n";
	cout << "See the dogs in the center | 4\n";
	cout << "Exit admin mode | 0\n";
}

void UI::main_commands_start()
{
	cout << "Welcome to the adoption center!\n";
	cout << "Select application mode:\n";
	cout << "1.Administator | 2.User | 0.Exit\n";
}

void UI::main_commands_user()
{
	cout << "Select option: \n";
	cout << "Adoption mode | 1\n";
	cout << "See the dogs you adopted | 2\n";
	cout << "Exit | 0\n";
}

void UI::exit_mode_message()
{
	cout << "Choose new mode\n";
	cout << "1.Administator | 2.User | 0.Exit\n";
}

void UI::Start(void)
{
	this->Administrator.GenerateEntities();
	this->main_commands_start();
	int main_command, exit_flag = 0;
	while (true)
	{
		cin >> main_command;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input!\n";
			continue;
		}
		switch (main_command)
		{
		case 1:
			Admin();
			cout << "Exiting admin mode...\n";
			this->exit_mode_message();
			break;
		case 2:
			User();
			cout << "Exiting user mode...\n";
			this->exit_mode_message();
			break;
		case 0:
			exit_flag = 1;
			break;
		default:
			cout << "Wrong command!\n";
			cout << "1.Administator | 2.User | 0.Exit\n";
			break;
		}
		if (exit_flag == 1)
		{
			break;
		}
	}
}

