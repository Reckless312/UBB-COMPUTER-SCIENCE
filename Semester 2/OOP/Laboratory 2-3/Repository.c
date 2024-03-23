#include "Repository.h"
#include <stdlib.h>

Repository* createRepository(int capacity)
{
	/*
	* capacity: int
	* Creates a new repository
	* return Repository*
	*/
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (repo == NULL)
	{
		return NULL;
	}
	repo->capacity = capacity;
	repo->meds = (Medicine*)malloc(capacity * sizeof(Medicine));
	if (repo->meds == NULL)
	{
		return NULL;
	}
	return repo;
}

void destroyRepository(Repository* repo)
{
	/*
	* repo: Repository*
	* Destroys an allocated repository
	* return;
	*/
	if (repo == NULL)
	{
		return;
	}
	free(repo->meds);
	repo->meds = NULL;
	free(repo);
}

void resize_repository(Repository* repo)
{
	/*
	* repo: Repository*
	* Resizes repository based on the current capacity
	* return;
	*/
	if (repo == NULL)
	{
		return;
	}
	Medicine* temporary_meds = realloc(repo->meds, repo->capacity * sizeof(Medicine));
	if (temporary_meds == NULL)
	{
		return;
	}
	repo->meds = temporary_meds;
}

void addMedicine(Repository* repo, Medicine med)
{
	/*
	* repo: Repository*
	* med: Medicine
	* Adds a new medicine inside the repository
	* return;
	*/
	if (repo == NULL)
	{
		return;
	}
	if (repo->meds == NULL)
	{
		return;
	}
	Medicine* meds = get_Meds(repo);
	int capacity = get_capacity(repo);
	for (int i = 0; i < capacity; i++)
	{
		if (strcmp(get_name(meds[i]), med.name) == 0 && get_concentration(meds[i]) == med.concentration)
		{
			meds[i].quantity += med.quantity;
			return;
		}
	}
	meds[capacity - 1] = med;
	repo->capacity++;
	resize_repository(repo);
}

void deleteMedicine(Repository* repo, char name[], unsigned int concentration, int pos)
{
	/*
	* repo: Repository*
	* name: string
	* concentration: unsigned int
	* Deletes a medicines that have the same name and concentration
	* return;
	*/
	Medicine* meds = get_Meds(repo);
	int capacity = get_capacity(repo);
	moveMedicinetoEnd(meds, pos, capacity);
	repo->capacity--;
	resize_repository(repo);
}

void updateMedicine(Repository* repo, char name[], unsigned int concentration, char new_name[], unsigned int new_concentration, unsigned int new_price, unsigned int new_quantity, int pos)
{
	/*
	* repo: Repository*
	* name: string
	* concentration: unsigned int
	* new_name:string
	* new_concentration: unsigned int
	* new_price: unsigned int
	* new_quantity: unsigned int
	* Updates a medicines that contain the name and the concentration given with new values
	* return;
	*/
	Medicine* meds = get_Meds(repo);
	strcpy(meds[pos].name, new_name);
	meds[pos].concentration = new_concentration;
	meds[pos].price = new_price;
	meds[pos].quantity = new_quantity;
}

void moveMedicinetoEnd(Medicine meds[], int pos, int length)
{
	/*
	* meds: array of Medicine
	* pos: int
	* length: int
	* Moves the element at the position "pos" to the end
	* return;
	*/
	for (int i = pos; i < length - 1; i++)
	{
		Medicine aux = meds[i];
		meds[i] = meds[i + 1];
		meds[i + 1] = aux;
	}
}

int get_Medicine_Position(Repository* repo, char name[], unsigned int concentration)
{
	/*
	* repo: Repository*
	* name: string
	* concentration: unsigned int
	* Gets the position where the medicine name and concentration coincide with the ones givenn
	* return int
	*/
	Medicine* meds = get_Meds(repo);
	int capacity = get_capacity(repo);
	for (int i = 0; i < capacity - 1; i++)
	{
		if (strcmp(get_name(meds[i]), name) == 0 && get_concentration(meds[i]) == concentration)
		{
			return i;
		}
	}
	return -1;
}

Medicine* get_Meds(Repository* repo)
{
	/*
	* repo: Repository*
	* Returns the meds
	* return Medicine*
	*/
	return repo->meds;
}

int get_length(Repository* repo)
{
	/*
	* repo: Repository*
	* Returns the length
	* return int
	*/
	return repo->capacity;
}

int get_capacity(Repository* repo)
{
	/*
	* repo: Repository*
	* Returns the capacity
	* return int
	*/
	return repo->capacity;
}

void generate_10_medicines(Repository* repo)
{
	Medicine med_1 = createMedicine("Hydrocodone", 15, 21, 60);
	Medicine med_2 = createMedicine("Metformin", 21, 40, 32);
	Medicine med_3 = createMedicine("Losartan", 12, 14, 52);
	Medicine med_4 = createMedicine("Antibiotics", 72, 17, 12);
	Medicine med_5 = createMedicine("Albuterol", 25, 82, 142);
	Medicine med_6 = createMedicine("Antihistamines", 35, 96, 36);
	Medicine med_7 = createMedicine("Gabapentin", 34, 56, 71);
	Medicine med_8 = createMedicine("Omeprazole", 75, 72, 82);
	Medicine med_9 = createMedicine("Levothyroxine", 66, 20, 99);
	Medicine med_10 = createMedicine("Atorvastatin", 12, 5, 15);
	addMedicine(repo, med_1);
	addMedicine(repo, med_2);
	addMedicine(repo, med_3);
	addMedicine(repo, med_4);
	addMedicine(repo, med_5);
	addMedicine(repo, med_6);
	addMedicine(repo, med_7);
	addMedicine(repo, med_8);
	addMedicine(repo, med_9);
	addMedicine(repo, med_10);
}