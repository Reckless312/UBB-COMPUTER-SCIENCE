#pragma once
#include "Service.h"
typedef struct
{
	Service serv;
}UI;
UI createUI(Service serv);
void print_set_a(void);
void print_main_menu(void);
void start_ui(UI ui);
void read_value(unsigned int* value, char message[]);
void read_string(char string[], char message[]);
void print_all_medicine(Medicine* meds, unsigned int length);
void print_set_d(void);