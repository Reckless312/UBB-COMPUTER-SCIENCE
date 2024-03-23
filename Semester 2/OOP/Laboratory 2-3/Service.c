#include "Service.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

Service createService(Repository* repo, History* history)
{
	/*
	* repo: Repository
	* history: History
	* Creates a Service
	* return Service
	*/
	Service serv;
	serv.repo = repo;
	serv.history = history;
	return serv;
}

int addToRepo(Service serv, char name[], char concentration[], char price[], char quantity[])
{
	/*
	* serv: Service
	* name: string
	* concentration: string
	* price: string
	* quantity: string
	* Prepares to add a medicine to repo
	* return int;
	*/
	if (check_string(name) == 1)
	{
		return 1;
	}
	if (check_number(concentration) == 1)
	{
		return 1;
	}
	if (check_number(price) == 1)
	{
		return 1;
	}
	if (check_number(quantity) == 1)
	{
		return 1;
	}
	Medicine med = createMedicine(name, atoi(concentration), atoi(quantity), atoi(price));
	push(serv.history, *serv.repo, "undo");
	addMedicine(serv.repo, med);
	return 0;
}

int check_string(char string[])
{
	/*
	* string: string
	* Checks if the given string contain only letters
	* return int
	*/
	for (int i = 0, length = strlen(string); i < length; i++)
	{
		if (!isalpha(string[i]))
		{
			return 1;
		}
	}
	return 0;
}

int check_number(char number[])
{
	/*
	* number: string
	* Checks if the given string contain only digits
	*/
	for (int i = 0, length = strlen(number); i < length; i++)
	{
		if (!isdigit(number[i]))
		{
			return 1;
		}
	}
	return 0;
}

int updateToRepo(Service serv, char name[], char concentration[], char new_name[], char new_concentration[], char new_price[], char new_quantity[])
{
	/*
	* serv: Service
	* name: string
	* concentration: string
	* new_name: string
	* new_concentration: string
	* new_price: string
	* new_quantity: string
	* Prepares to update an entity in repo
	* return int;
	*/
	if (check_string(name) == 1)
	{
		return 1;
	}
	if (check_number(concentration) == 1)
	{
		return 1;
	}
	if (check_string(new_name) == 1)
	{
		return 1;
	}
	if (check_number(new_concentration) == 1)
	{
		return 1;
	}
	if (check_number(new_price) == 1)
	{
		return 1;
	}
	if (check_number(new_quantity) == 1)
	{
		return 1;
	}
	int pos = get_Medicine_Position(serv.repo, name, atoi(concentration));
	if (pos == -1)
	{
		printf("Element not found!\n");
		return 0;
	}
	push(serv.history, *serv.repo, "undo");
	updateMedicine(serv.repo, name, atoi(concentration), new_name, atoi(new_concentration), atoi(new_price), atoi(new_quantity), pos);
	return 0;
}

int deleteInRepo(Service serv, char name[], char concentration[])
{
	/*
	* serv: Service
	* name: string
	* concentration: string
	* Prepares to delete an entity inside repo
	* return int;
	*/
	if (check_string(name) == 1)
	{
		return 1;
	}
	if (check_number(concentration) == 1)
	{
		return 1;
	}
	int pos = get_Medicine_Position(serv.repo, name, atoi(concentration));
	if (pos == -1)
	{
		printf("Element not found!\n");
		return 0;
	}
	push(serv.history, *serv.repo, "undo");
	deleteMedicine(serv.repo, name, atoi(concentration), pos);
	return 0;
}

Repository* DisplaySortedByGivenString(Service serv, char string[])
{
	/*
	* serv: Service
	* string: string
	* Sorts the entities and sorts them by "string"
	* return: array
	*/
	unsigned int length;
	Repository* temporary_repo = FindByString(serv, string);
	Medicine* meds = get_Meds(temporary_repo);
	length = get_capacity(temporary_repo);
	SortByName(serv, meds, length);
	return temporary_repo;
}

Repository* FindByString(Service serv, char string[])
{
	/*
	* serv: Service
	* string: string
	* Finds all the entities that have as a substring the string "string"
	* return: array
	*/
	Repository* temporary_repo = createRepository(1);
	Medicine* meds = get_Meds(serv.repo);
	for (int i = 0, length = get_length(serv.repo); i < length - 1; i++)
	{
		if (strstr(&meds[i], string) != NULL)
		{
			addMedicine(temporary_repo, meds[i]);
		}
	}
	return temporary_repo;
}

void Undo(Service serv)
{
	/*
	* serv: Service
	* Undo the last operation
	* return;
	*/
	if (serv.history->capacity_undo == 1)
	{
		printf("No more undos!");
		return;
	}
	push(serv.history, *serv.repo, "redo");
	Repository temporary_repository = pop(serv.history, "undo");
	serv.repo->capacity = temporary_repository.capacity;
	resize_repository(serv.repo);
	for (int i = 0, length = serv.repo->capacity; i < length; i++)
	{
		serv.repo->meds[i] = temporary_repository.meds[i];
	}
	free(temporary_repository.meds);
	resize_history(serv.history, "undo");
}

void Redo(Service serv)
{
	/*
	* serv: Service
	* Redo the last undo
	* return;
	*/
	if (serv.history->capacity_redo == 1)
	{
		printf("No more redos!\n");
		return;
	}
	push(serv.history, *serv.repo, "undo");
	Repository temporary_repository = pop(serv.history, "redo");
	serv.repo->capacity = temporary_repository.capacity;
	resize_repository(serv.repo);
	for (int i = 0, length = serv.repo->capacity; i < length - 1; i++)
	{
		serv.repo->meds[i] = temporary_repository.meds[i];
	}
	free(temporary_repository.meds);
	resize_history(serv.history, "redo\n");
}

void SortByName(Service serv, Medicine* meds, int length)
{
	/*
	* serv: Service
	* meds: array of Medicine
	* length: int
	* Sorts the array alphabetically
	* return;
	*/
	for (int i = 0; i < length - 2; i++)
	{
		for (int j = i + 1; j < length - 1; j++)
		{
			if (strcmp(meds[i].name, meds[j].name) > 0)
			{
				Medicine aux = meds[i];
				meds[i] = meds[j];
				meds[j] = aux;
			}
		}
	}
}

Repository* LessThanQuantity(Service serv, unsigned int quantity)
{
	/*
	* serv: Service
	* quantity: unsigned int
	* Find all the entities with the quantity less than the given one
	* return: array
	*/
	Repository* temporary_repo = createRepository(1);
	Medicine* meds = get_Meds(serv.repo);
	for (int i = 0, length = get_length(serv.repo); i < length - 1; i++)
	{
		if (get_quantity(meds[i]) < quantity)
		{
			addMedicine(temporary_repo, meds[i]);
		}
	}
	return temporary_repo;
}