#pragma once
#include "AdoptionCenter.h"

class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;
};

class ActionAdd : public Action
{
private:
	std::string breed;
	std::string name;
	int age;
	std::string photograph;
	Repository* repo;
public:
	ActionAdd(Repository* repo, std::string breed, std::string name, int age, std::string photograph);
	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove : public Action
{
private:
	std::string breed;
	std::string name;
	int age;
	std::string photograph;
	Repository* repo;
public:
	ActionRemove(Repository* repo, std::string breed, std::string name, int age, std::string photograph);
	void executeUndo() override;
	void executeRedo() override;
};

class ActionUpdate : public Action
{
private:
	std::string breed;
	std::string name;
	int age;
	std::string photograph;
	std::string new_name;
	int new_age;
	std::string new_photograph;
	Repository* repo;
public:
	ActionUpdate(Repository* repo, std::string breed, std::string name, int age, std::string photograph, std::string new_name, int new_age, std::string new_photograph);
	void executeUndo() override;
	void executeRedo() override;
};