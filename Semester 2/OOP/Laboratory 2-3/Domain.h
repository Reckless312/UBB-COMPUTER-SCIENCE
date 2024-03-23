#pragma once
typedef struct
{
	char name[50];
	unsigned int concentration;
	unsigned int quantity;
	unsigned int price;
} Medicine;

Medicine createMedicine(char name[], unsigned int concentration, unsigned int quantity, unsigned int price);
char* get_name(Medicine med);
unsigned int get_concentration(Medicine med);
unsigned int get_quantity(Medicine med);
unsigned int get_price(Medicine med);
void print_medicine(Medicine med);
