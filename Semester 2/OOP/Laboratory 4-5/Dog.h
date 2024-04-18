#pragma once

#include <string>

using namespace std;
typedef string Link;

class Dog
{
private:
	string breed;
	string name;
	int age;
	Link photograph;
public:
	Dog();
	Dog(string breed, string name, int age, Link photograph);
	bool operator==(Dog& other);
	string GetBreed(void);
	string GetName(void);
	int GetAge(void);
	Link GetPhotograph(void);
	void SetBreed(string breed);
	void SetName(string name);
	void SetAge(int age);
	void SetPhotograph(Link photograph);
	string __String__(void);
};
