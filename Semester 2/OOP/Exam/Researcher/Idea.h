#pragma once

#include <string>

using namespace std;

class Idea
{
private:
	string title, description, status, creator;
	int duration;
public:
	Idea(string title, string description, string status, string creator, int duration) { this->title = title, this->description = description, this->status = status, this->creator = creator, this->duration = duration; }
	string getTitle() { return this->title; }
	string getStatus() { return this->status; }
	string getcreator() { return this->creator; }
	int getDuration() { return this->duration; }
	string getDescription() { return this->description; }
	void setStatus() { this->status = "accepted"; }
	string setDescription(string description) { this->description = description; }
};