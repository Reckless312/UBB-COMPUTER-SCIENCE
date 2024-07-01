#pragma once

#include <string>
#include <vector>
using namespace std;


class Idea
{
private:
	string description, status, creator;
	int act;

public:
	Idea(string des, string stat, string creator, int act) { this->description = des, this->status = stat, this->creator = creator, this->act = act; }

	string getDescription()  const { return this->description; }
	string getStatus()  const { return this->status; }
	string getCreator()  const { return this->creator; }
	int getAct()  const { return this->act; }
	void setApproved() { this->status = "accepted"; }

private:
	vector<string> tokenize(string str, char delimitator);

	friend std::istream& operator>>(istream& is, Idea& idea);
	friend std::ostream& operator<<(ostream& os, const Idea& idea);
};