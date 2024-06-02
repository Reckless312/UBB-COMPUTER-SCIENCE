#pragma once

#include "Repo.h"

class Service
{
public:
	Repo repo;
	void Call_Read();
	vector<Document> Get_Doc();
	void Sort();
};