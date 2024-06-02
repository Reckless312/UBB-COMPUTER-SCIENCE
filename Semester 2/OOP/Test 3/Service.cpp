#include "Service.h"

void Service::Call_Read()
{
	this->repo.Read();
}

vector<Document> Service::Get_Doc()
{
	return this->repo.storage;
}

void Service::Sort()
{
	for (int i = 0, n = this->repo.storage.size(); i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (this->repo.storage[i].GetName() > this->repo.storage[j].GetName())
			{
				swap(this->repo.storage[i], this->repo.storage[j]);
			}
		}
	}
}
