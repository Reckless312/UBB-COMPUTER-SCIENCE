#pragma once
#include "Domain.h"

typedef struct
{
	Medicine* meds;
	int capacity;
}Repository;

Repository* createRepository(int capacity);
void destroyRepository(Repository* repo);
void resize_repository(Repository* repo);
void addMedicine(Repository* repo, Medicine med);
void deleteMedicine(Repository* repo, char name[], unsigned int concentration, int pos);
void updateMedicine(Repository* repo, char name[], unsigned int concentration, char new_name[], unsigned int new_concentration, unsigned int new_price, unsigned int new_quantity, int pos);
int get_Medicine_Position(Repository* repo, char name[], unsigned int concentration);
void moveMedicinetoEnd(Medicine meds[], int pos, int length);
Medicine* get_Meds(Repository* repo);
int get_length(Repository* repo);
int get_capacity(Repository* repo);
void generate_10_medicines(Repository* repo);