#include "History.h"
#include <stdlib.h>
#include <string.h>

History* createHistory()
{
	/*
	* Creates a history
	* return History*
	*/
	History* history = (History*)malloc(sizeof(History));
	if (history == NULL)
	{
		return NULL;
	}
	history->redo = createRepository(1);
	history->undo = createRepository(1);
	if (history->redo == NULL || history->undo == NULL)
	{
		return NULL;
	}
	history->capacity_redo = history->capacity_undo = 1;
	return history;
}

void destroyHistory(History* history)
{
	/*
	* history: History*
	* Destroys an allocated history
	* return;
	*/
	if (history == NULL)
	{
		return;
	}
	for (int i = 0; i < history->capacity_undo - 1; i++)
	{
		free(history->undo[i].meds);
	}
	for (int i = 0; i < history->capacity_redo - 1; i++)
	{
		free(history->redo[i].meds);
	}
	free(history->undo);
	free(history->redo);
	history->undo = NULL;
	history->redo = NULL;
	free(history);
}

void resize_history(History* history, char string[])
{
	/*
	* history: History*
	* string: string
	* Resizes the repositories inside history given their capacity and the given string
	* return;
	*/
	if (history == NULL)
	{
		return;
	}
	if (history->undo == NULL || history->redo == NULL)
	{
		return;
	}
	if (strcmp(string, "undo") == 0)
	{
		Repository* temporary_repository = realloc(history->undo, history->capacity_undo * sizeof(Repository));
		history->undo = temporary_repository;
	}
	else if (strcmp(string, "redo") == 0)
	{
		Repository* temporary_repository = realloc(history->redo, history->capacity_redo * sizeof(Repository));
		history->redo = temporary_repository;
	}
}

void push(History* history, Repository repo, char string[])
{
	/*
	* history: History*
	* repo: Repository*
	* string: string
	* Pushes a repository in the history
	* return;
	*/
	if (history == NULL)
	{
		return;
	}
	if (history->redo == NULL)
	{
		return;
	}
	if (history->undo == NULL)
	{
		return;
	}
	if (strcmp(string, "undo") == 0)
	{
		Repository* undo = get_Repos_Undo(history);
		Repository* temp_repo = createRepository(1);
		int capacity = history->capacity_undo;
		int length = repo.capacity;
		temp_repo->capacity = repo.capacity;
		resize_repository(temp_repo);
		for (int i = 0; i < length; i++)
		{
			temp_repo->meds[i] = repo.meds[i];
		}
		undo[capacity - 1] = *temp_repo;
		history->capacity_undo++;
		resize_history(history, "undo");
		free(temp_repo);
	}
	else if (strcmp(string, "redo") == 0)
	{
		Repository* redo = get_Repos_Redo(history);
		Repository* temp_repo = createRepository(1);
		int capacity = history->capacity_redo;
		int length = repo.capacity;
		temp_repo->capacity = repo.capacity;
		resize_repository(temp_repo);
		for (int i = 0; i < length; i++)
		{
			temp_repo->meds[i] = repo.meds[i];
		}
		redo[capacity - 1] = *temp_repo;
		history->capacity_redo++;
		resize_history(history, "redo");
		free(temp_repo);
	}
}

Repository pop(History* history, char string[])
{
	/*
	* history: History*
	* string: string
	* Pops an element out of the history and returns it
	* return Repository
	*/
	if (history == NULL)
	{
		return;
	}
	if (history->undo == NULL)
	{
		return;
	}
	if (history->redo == NULL)
	{
		return;
	}
	if (strcmp(string, "undo") == 0)
	{
		history->capacity_undo -= 1;
		return history->undo[history->capacity_undo - 1];
	}
	else if (strcmp(string, "redo") == 0)
	{
		history->capacity_redo -= 1;
		return history->redo[history->capacity_redo - 1];
	}
}

Repository* get_Repos_Undo(History* history)
{
	/*
	* history: History
	* Gets the pointer to the undos
	* return: Repository*
	*/
	return history->undo;
}

Repository* get_Repos_Redo(History* history)
{
	/*
	* history: History
	* Gets the pointer to the redos
	* return: Repository*
	*/
	return history->redo;
}