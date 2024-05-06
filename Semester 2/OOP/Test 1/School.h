#pragma once
#include <string>
#include <algorithm>

using namespace std;

struct address {
	double longitude;
	double latitude;
};

struct date {
	string year;
	string month;
	string day;
};

class School
{
private:
	string name;
	address location;
	date current_date;
	bool visited;
public:
	School();
	School(string name, address addr, date dat, bool visited);
	bool operator==(School other);
	string GetName(void);
	address GetAddress(void);
	date GetCurrentDate(void);
	bool GetVisited(void);
	void SetName(string name);
	void SetAddress(address adr);
	void SetVisited();
	string __str__(void);
};

class SchoolNameComparison
{
public:
	bool operator()(School& s1, School& s2)
	{
		if (s1.GetName() < s2.GetName())
		{
			return true;
		}
		return false;
	}
};