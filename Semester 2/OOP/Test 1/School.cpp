#include "School.h"

School::School()
{
	this->name = "";
	this->location.latitude = 0;
	this->location.longitude = 0;
	this->current_date.day = "";
	this->current_date.month = "";
	this->current_date.year = "";
	this->visited = false;
}

School::School(string name, address addr, date dat, bool visited)
{
	this->name = name;
	this->location.latitude = addr.latitude;
	this->location.longitude = addr.longitude;
	this->current_date.day = dat.day;
	this->current_date.month = dat.month;
	this->current_date.year = dat.year;
	this->visited = visited;
}

bool School::operator==(School other)
{
	if (this->name != other.name)
	{
		return false;
	}
	if (this->location.latitude != other.location.latitude)
	{
		return false;
	}
	if (this->location.longitude != other.location.longitude)
	{
		return false;
	}
	return true;
}

string School::GetName(void)
{
	return this->name;
}

address School::GetAddress(void)
{
	return this->location;
}

date School::GetCurrentDate(void)
{
	return this->current_date;
}

bool School::GetVisited(void)
{
	return this->visited;
}

void School::SetName(string name)
{
	this->name = name;
}

void School::SetAddress(address adr)
{
	this->location = adr;
}

void School::SetVisited()
{
	this->visited = true;
}

string School::__str__(void)
{
	if (this->visited == true)
	{
		return this->name + " | " + to_string(this->location.longitude) + ", " + to_string(this->location.latitude) + " | " + this->current_date.year +"." + this->current_date.month+"." + this->current_date.day + " | true";
	}
	else
	{
		return this->name + " | " + to_string(this->location.longitude) + ", " + to_string(this->location.latitude) + " | " + this->current_date.year + "." + this->current_date.month + "." + this->current_date.day + " | false";
	}
	
}
