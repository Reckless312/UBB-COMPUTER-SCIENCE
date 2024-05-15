#include "Action.h"

ActionAdd::ActionAdd(Repository* repo, std::string breed, std::string name, int age, std::string photograph)
{
	this->repo = repo;
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
}

void ActionAdd::executeUndo()
{
	this->repo->Delete(breed, name, age, photograph);
}

void ActionAdd::executeRedo()
{
	this->repo->Add(breed, name, age, photograph);
}

ActionRemove::ActionRemove(Repository* repo, std::string breed, std::string name, int age, std::string photograph)
{
	this->repo = repo;
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;

}

void ActionRemove::executeUndo()
{
	this->repo->Add(breed, name, age, photograph);
}

void ActionRemove::executeRedo()
{
	this->repo->Delete(breed, name, age, photograph);
}

ActionUpdate::ActionUpdate(Repository* repo, std::string breed, std::string name, int age, std::string photograph, std::string new_name, int new_age, std::string new_photograph)
{
	this->repo = repo;
	this->breed = breed;
	this->name = name;
	this->age = age;
	this->photograph = photograph;
	this->new_age = new_age;
	this->new_name = new_name;
	this->new_photograph = new_photograph;
}

void ActionUpdate::executeUndo()
{
	this->repo->Update(this->breed, this->new_name, this->new_age, this->new_photograph, this->name, this->age, this->photograph);
}

void ActionUpdate::executeRedo()
{
	this->repo->Update(this->breed, this->name, this->age, this->photograph, this->new_name, this->new_age, this->new_photograph);
}
