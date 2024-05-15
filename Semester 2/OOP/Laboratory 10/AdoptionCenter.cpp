#include "AdoptionCenter.h"

/// <summary>
/// Adds a dog in the shelter
/// Throws exception if the dog is already in the shelter
/// </summary>
/// <param name="breed"></param> Breed of the dog
/// <param name="name"></param> Name of the dog
/// <param name="age"></param> Age of the dog
/// <param name="photograph"></param> Link of the photograph
void Repository::Add(std::string breed, std::string name, int age, std::string photograph)
{
	Dog Pet(breed, name, age, photograph);
	if (find(Pet) != this->repo.end())
	{
		throw RepositoryException("This dog is already in the shelter!\n");
	}
	this->repo.push_back(Pet);
}

/// <summary>
/// Removes a dog from the shelter
/// Throws exception if dog is not in the shelter
/// </summary>
/// <param name="breed"></param> Breed of dog
/// <param name="name"></param> Name of dog
/// <param name="age"></param> Age of dog
/// <param name="photograph"></param> Link of the photograph
void Repository::Delete(std::string breed, std::string name, int age, std::string photograph)
{
	Dog Pet(breed, name, age, photograph);
	auto iterator = find(Pet);
	if (iterator == this->repo.end())
	{
		throw RepositoryException("This dog is not in the shelter!\n");
	}
	this->repo.erase(iterator);
}

/// <summary>
/// Updates the information of a dog in the shelter
/// Throws exception if dog is not in the shelter
/// </summary>
/// <param name="previous_breed"></param> Breed of dog
/// <param name="previous_name"></param> Name of dog
/// <param name="previous_age"></param> Age of dog
/// <param name="previous_photograph"></param> Link of the photograph
/// <param name="new_name"></param> New name of the dog
/// <param name="new_age"></param> New age of the dog
/// <param name="new_photograph"></param> New link for the photograph
void Repository::Update(std::string previous_breed, std::string previous_name, int previous_age, std::string previous_photograph, std::string new_name, int new_age, std::string new_photograph)
{
	Dog Pet(previous_breed, previous_name, previous_age, previous_photograph);
	auto iterator = find(Pet);
	if (iterator == this->repo.end())
	{
		throw RepositoryException("This dog is not in the shelter!\n");
	}
	iterator->SetName(new_name);
	iterator->SetAge(new_age);
	iterator->SetPhotograph(new_photograph);
}

/// <summary>
/// Makes a copy of the data and returns it
/// </summary>
/// <returns></returns>
std::vector<Dog> Repository::MakeCopy()
{
	std::vector<Dog> RepoCopy;
	std::copy(this->repo.begin(), this->repo.end(), std::back_inserter(RepoCopy));
	return RepoCopy;
}

/// <summary>
/// Constructor for the text-file-repository
/// </summary>
TextFileRepository::TextFileRepository(std::string file_name)
{
	this->file_name = file_name;
}

/// <summary>
/// Reads the data from the textfile
/// </summary>
void TextFileRepository::Read()
{
	Dog Pet;
	std::string line;
	std::ifstream file(this->file_name);
	std::string breed;
	if (file.is_open() == false)
	{
		throw RepositoryException("File didn't open!\n");
	}
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			continue;
		}
		std::stringstream input(line);
		input >> Pet;
		breed = Pet.GetBreed();
		std::replace(breed.begin(), breed.end(), '_', ' ');
		Pet.SetBreed(breed);
		this->repo.push_back(Pet);
	}
	file.close();
}

/// <summary>
/// Writes the data from the center into a text file
/// </summary>
void TextFileRepository::Write()
{
	std::ofstream file(this->file_name);
	std::string breed;
	for (Dog Pet : this->repo)
	{
		breed = Pet.GetBreed();
		std::replace(breed.begin(), breed.end(), ' ', '_');
		Pet.SetBreed(breed);
		file << Pet << std::endl;
	}
	file.close();
}

void TextFileRepository::Open()
{
	std::string notepad_command = "C:\\Users\\ionut\\Desktop\\asm_tools\\npp\\notepad++ C:\\Users\\ionut\\source\\repos\\cs-ubbcluj-ro\\oop-a8-9-Reckless312\\QTAdoptAPet\\TextFileAdoption.txt";
	system(notepad_command.c_str());
}

/// <summary>
/// Default constructor for the CSV file repository
/// </summary>
CSVRepository::CSVRepository(std::string file_name)
{
	this->file_name = file_name;
}

/// <summary>
/// Empty override function
/// </summary>
void CSVRepository::Read()
{

}

/// <summary>
/// Writes the data from the shelter in csv file
/// </summary>
void CSVRepository::Write()
{
	std::ofstream file(this->file_name);
	std::string breed;
	for (Dog Pet : this->repo)
	{
		breed = Pet.GetBreed();
		std::replace(breed.begin(), breed.end(), ' ', '_');
		Pet.SetBreed(breed);
		file << Pet.GetBreed() << "," << Pet.GetName() << "," << Pet.GetAge() << "," << Pet.GetPhotograph() << std::endl;
	}
	file.close();
}

void CSVRepository::Open()
{
	std::string notepad_command = "C:\\Users\\ionut\\Desktop\\asm_tools\\npp\\notepad++ C:\\Users\\ionut\\source\\repos\\cs-ubbcluj-ro\\oop-a8-9-Reckless312\\QTAdoptAPet\\CSVRepository.csv";
	system(notepad_command.c_str());
}

/// <summary>
/// Default constructor for the html repository
/// </summary>
HTMLRepository::HTMLRepository(std::string file_name)
{
	this->file_name = file_name;
}

/// <summary>
/// Empty override function
/// </summary>
void HTMLRepository::Read()
{

}

/// <summary>
/// Writes the data from the center into a html
/// </summary>
void HTMLRepository::Write()
{
	std::ofstream file(this->file_name);
	file << "<!DOCTYPE html>" << std::endl;
	file << "<html>" << std::endl;
	file << "<head>" << std::endl;
	file << "<title>Adoption Shelter</title>" << std::endl;
	file << "</head>" << std::endl;
	file << "<body>" << std::endl;
	file << "<table border = \"1\">" << std::endl;
	for (Dog Pet : this->repo)
	{
		file << "<tr>" << std::endl;
		file << "<td>" << Pet.GetBreed() << "</td>" << std::endl;
		file << "<td>" << Pet.GetName() << "</td>" << std::endl;
		file << "<td>" << Pet.GetAge() << "</td>" << std::endl;
		file << "<td><a href = \"" << Pet.GetPhotograph() << "\">Link</a></td>" << std::endl;
		file << "</tr>" << std::endl;
	}
	file << "</table>" << std::endl;
	file << "</body>" << std::endl;
	file << "</html>" << std::endl;
	file.close();
}

void HTMLRepository::Open()
{
	std::wstring html_path = L"C:\\Users\\ionut\\source\\repos\\cs-ubbcluj-ro\\oop-a8-9-Reckless312\\QTAdoptAPet\\HTMLRepository.html";
	ShellExecute(NULL, L"open", html_path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
