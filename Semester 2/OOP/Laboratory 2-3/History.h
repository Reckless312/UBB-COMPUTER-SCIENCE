#pragma once
#include "Repository.h"
typedef struct
{
	Repository* undo;
	Repository* redo;
	int capacity_undo;
	int capacity_redo;
}History;

History* createHistory();
void destroyHistory(History* history);
void resize_history(History* history, char string[]);
void push(History* history, Repository repo, char string[]);
Repository pop(History* history, char string[]);
Repository* get_Repos_Undo(History* history);
Repository* get_Repos_Redo(History* history);