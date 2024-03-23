#include "Domain.h"
#include <string.h>

Medicine createMedicine(char name[], unsigned int concentration, unsigned int quantity, unsigned int price)
{
	/*
	* name: string
	* concentration: unsigned int
	* quantity: unsigned int
	* price: unsigned int
	* Creates a medicine
	* return Medicine
	*/
	Medicine med;
	strcpy(med.name, name);
	med.concentration = concentration;
	med.quantity = quantity;
	med.price = price;
	return med;
}

char* get_name(Medicine med)
{
	/*
	* med: Medicine
	* Gets the name of the medicine
	* return string
	*/
	return med.name;
}

unsigned int get_concentration(Medicine med)
{
	/*
	* med: Medicine
	* Gets the concentration of the medicine
	* return unsigned int
	*/
	return med.concentration;
}

unsigned int get_quantity(Medicine med)
{
	/*
	* med: Medicine
	* Gets the quantity of the medicine
	* return unsigned int
	*/
	return med.quantity;
}

unsigned int get_price(Medicine med)
{
	/*
	* med: Medicine
	* Gets the price of the medicine
	* return unsigned int
	*/
	return med.price;
}

void print_medicine(Medicine med)
{
	/*
	* med: Medicine
	* Provides a format for the type Medicine and prints it on the screen
	* return;
	*/
	printf("Name: %s | Concentration: %i | Price: %i | Quantity: %i\n", med.name, med.concentration, med.price, med.quantity);
}