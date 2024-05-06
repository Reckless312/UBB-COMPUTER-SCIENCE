#include "UI.h"

void UI::Start()
{
	int command, exit_flag = 0, choice;
	this->ChooseFile(choice);
	while (true)
	{
		std::cout << "Select mode:\n";
		std::cout << "1.Admin mode\n";
		std::cout << "2.User mode\n";
		std::cout << "0.Exit\n";
		std::cin >> command;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Only numbers!\n";
			continue;
		}
		switch (command)
		{
		case 1:
		{
			this->Start_Admin();
			std::cout << "Exiting admin mode...\n\n";
			break;
		}
		case 2:
		{
			this->Start_User(choice);
			std::cout << "Exiting user mode...\n\n";
			break;
		}
		case 0:
			exit_flag = 1;
			break;
		default:
			break;
		}
		if (exit_flag == 1)
		{
			break;
		}
	}
}

void UI::Start_Admin()
{
	std::string breed, name, photograph, new_name, new_photograph;
	int command, age, new_age, exit_flag = 0;
	while (true)
	{
		std::cout << "Select operation:\n";
		std::cout << "1.Add a dog\n";
		std::cout << "2.Remove a dog\n";
		std::cout << "3.Update a dog\n";
		std::cout << "4.See the shelter\n";
		std::cout << "0.Exit\n";
		std::cin >> command;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Only numbers!\n";
			continue;
		}
		switch (command)
		{
		case 1:
		{
			try
			{
				this->ReadDog(breed, name, age, photograph);
				this->admin.Add(breed, name, age, photograph);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
			}
			break;
		}
		case 2:
			try
			{
				this->ReadDog(breed, name, age, photograph);
				this->admin.Delete(breed, name, age, photograph);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
			}
			break;
		case 3:
			try
			{
				this->ReadDog(breed, name, age, photograph);
				this->ReadUpdateDog(new_name, new_age, new_photograph);
				this->admin.Update(breed, name, age, photograph, new_name, new_age, new_photograph);
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
			}
			break;
		case 4:
			try
			{
				for (Dog Pet : this->admin.GetCopy())
				{
					std::cout << Pet.toString() << std::endl;
				}
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
			}
			break;
		case 0:
			exit_flag = 1;
			break;
		default:
			std::cout << "Invalid!\n";
			break;
		}
		if (exit_flag == 1)
		{
			break;
		}
		std::cout << std::endl;
	}
}

void UI::Start_User(int& file_choice)
{
	int command, requested_age, exit_flag = 0;
	std::string requested_breed, choice, link_start;
	std::vector<Dog> DogsFiltered;
	while (true)
	{
		std::cout << "Select mode:\n";
		std::cout << "1.Adoption mode\n";
		std::cout << "2.See dogs adopted\n";
		std::cout << "0.Exit\n";
		std::cin >> command;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Only numbers!\n";
			continue;
		}
		switch (command)
		{
		case 1:
			try
			{
				this->ReadFilter(requested_breed, requested_age);
				int position = 0;
				while (true)
				{
					DogsFiltered = this->user.Adopt(this->admin.GetCopy(), requested_breed, requested_age);
					if (position > DogsFiltered.size() - 1)
					{
						position = 0;
					}
					std::cout << DogsFiltered[position].toString() << std::endl;
					link_start = "start " + DogsFiltered[position].GetPhotograph();
					system(link_start.c_str());
					std::cout << "Do you want to adopt the dog?\n";
					std::cout << "Yes\n";
					std::cout << "No\n";
					std::cout << "Exit\n";
					std::cin >> choice;
					if (choice == "yes")
					{
						this->user.Add(DogsFiltered[position]);
						std::cout << "Adopted!\n";
						position--;
					}
					else if (choice == "no")
					{
						std::cout << "Next dog...\n";
					}
					else if (choice == "exit")
					{
						std::cout << "Exiting...\n";
						break;
					}
					else
					{
						std::cout << "Invalid!\n";
						std::cout << "Showing next dog!\n";
					}
					position++;
				}
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
			}
			this->user.WriteInFile();
			break;
		case 2:
			try
			{
				switch (file_choice)
				{
				case 1:
				{
					for (Dog Pet : this->user.GetCopy())
					{
						std::cout << Pet.toString() << std::endl;
					}
					break;
				}
				case 2:
				{
					std::string notepad_command = "C:\\Users\\ionut\\Desktop\\asm_tools\\npp\\notepad++ C:\\Users\\ionut\\source\\repos\\cs-ubbcluj-ro\\oop-a6-7-Reckless312\\AdoptAPet\\CSVRepository.csv";
					system(notepad_command.c_str());
					break;
				}
				case 3:
				{
					std::wstring html_path = L"C:\\Users\\ionut\\source\\repos\\cs-ubbcluj-ro\\oop-a6-7-Reckless312\\AdoptAPet\\HTMLRepository.html";
					ShellExecute(NULL, L"open", html_path.c_str(), NULL, NULL, SW_SHOWNORMAL);
					break;
				}
				default:
					break;
				}
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
			}
			break;
		case 0:
			exit_flag = 1;
			break;
		default:
			std::cout << "Invalid!\n";
			break;
		}
		if (exit_flag == 1)
		{
			break;
		}
	}
}

void UI::ChooseFile(int& choice)
{
	std::cout << "Select file format: \n";
	std::cout << "1.Text File\n";
	std::cout << "2.CSV File\n";
	std::cout << "3.HTML File\n";
	do
	{
		std::cin >> choice;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Only numbers!\n";
		}
	} while (choice < 1 || choice > 3);
	switch (choice)
	{
	case 1:
	{
		TextFileRepository* repo = new TextFileRepository("TextFileAdoption.txt");
		this->user.ChangeRepo(repo);
		break;
	}
	case 2:
	{
		CSVRepository* repo = new CSVRepository;
		this->user.ChangeRepo(repo);
		break;
	}
	case 3:
	{
		HTMLRepository* repo = new HTMLRepository;
		this->user.ChangeRepo(repo);
		break;
	}
	default:
		break;
	}
	TextFileRepository* shelter = new TextFileRepository("TextFile.txt");
	this->admin.ChangeRepo(shelter);
	this->admin.ReadFromFile();
}

void UI::ReadDog(std::string& breed, std::string& name, int& age, std::string& photograph)
{
	std::cout << "Breed: ";
	std::getline(std::cin >> std::ws, breed);
	std::cout << "Name: ";
	std::cin >> name;
	std::cout << "Age: ";
	std::cin >> age;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		throw std::exception("Not a number!\n");
	}
	std::cout << "Photograph-link: ";
	std::cin >> photograph;
}

void UI::ReadUpdateDog(std::string& name, int& age, std::string& photograph)
{
	std::cout << "New name: ";
	std::cin >> name;
	std::cout << "New age: ";
	std::cin >> age;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		throw std::exception("Not a number!\n");
	}
	std::cout << "New Photograph-link: ";
	std::cin >> photograph;
}

void UI::ReadFilter(std::string& requested_breed, int& requested_age)
{
	std::cout << "Breed: ";
	std::cin.ignore();
	std::getline(std::cin, requested_breed);
	if (requested_breed == "")
	{
		requested_age = 9999;
		return;
	}
	std::cout << "Age: ";
	std::cin >> requested_age;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore();
		throw std::exception("Not a number!\n");
	}
}
