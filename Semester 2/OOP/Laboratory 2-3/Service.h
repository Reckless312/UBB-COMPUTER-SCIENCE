#pragma once
#include "History.h"
typedef struct
{
	Repository* repo;
	History* history;
}Service;

Service createService(Repository* repo, History* history);
int updateToRepo(Service serv, char name[], char concentration[], char new_name[], char new_concentration[], char new_price[], char new_quantity[]);
int deleteInRepo(Service serv, char name[], char concentration[]);
int addToRepo(Service serv, char name[], char concentration[], char price[], char quantity[]);
Repository* FindByString(Service serv, char string[]);
void SortByName(Service serv, Medicine* meds, int length);
Repository* LessThanQuantity(Service serv, unsigned int quantity);
Repository* DisplaySortedByGivenString(Service serv, char string[]);
void Undo(Service serv);
void Redo(Service serv);
int check_string(char string[]);
int check_number(char number[]);