#include "UI.h"
#include <stdio.h>
#include <stdbool.h>

void start_ui(UI ui)
{
	printf("Welcome to the application!\n");
	while (true)
	{
		unsigned int main_command;
		print_main_menu();
		read_value(&main_command, "command");
		if (main_command == 1)
		{
			unsigned int set_a_command, value_error;
			char name[50], concentration[50], price[50], quantity[50];
			print_set_a();
			read_value(&set_a_command, "set");
			if (set_a_command == 1)
			{
				read_string(name, "name");
				read_string(concentration, "concentration");
				read_string(price, "price");
				read_string(quantity, "quantity");
				value_error = addToRepo(ui.serv, name, concentration, price, quantity);
				if (value_error == 1)
				{
					printf("Operation cannot be done! Invalid paramaters!\n");
				}
			}
			else if (set_a_command == 2)
			{
				read_string(name, "name to find");
				read_string(concentration, "concentration to find");
				value_error = deleteInRepo(ui.serv, name, concentration);
				if (value_error == 1)
				{
					printf("Operation cannot be done! Invalid paramaters!\n");
				}
			}
			else if (set_a_command == 3)
			{
				char new_name[50], new_concentration[50], new_price[50], new_quantity[50];
				read_string(name, "name to be updated");
				read_string(concentration, "concentration to be updated");
				read_string(new_name, "new name");
				read_string(new_concentration, "new concentration");
				read_string(new_price, "new price");
				read_string(new_quantity, "new quantity");
				value_error = updateToRepo(ui.serv, name, concentration, new_name, new_concentration, new_price, new_quantity);
				if (value_error == 1)
				{
					printf("Operation cannot be done! Invalid paramaters!\n");
				}
			}
			else if (set_a_command == 0)
			{
				continue;
			}
			else
			{
				printf("Invalid command! Going back to the main menu...\n");
			}
		}
		else if (main_command == 2)
		{
			char string[50];
			read_string(string, "substring");
			Repository* temp_repo = DisplaySortedByGivenString(ui.serv, string);
			print_all_medicine(temp_repo->meds, temp_repo->capacity);
			destroyRepository(temp_repo);
		}
		else if (main_command == 3)
		{
			unsigned int value_error;
			char quantity[50];
			read_string(quantity, "quantity");
			value_error = check_number(quantity);
			if (value_error == 1)
			{
				printf("Operation cannot be done! Invalid paramaters!\n");
			}
			else
			{
				Repository* temporary_repo = LessThanQuantity(ui.serv, atoi(quantity));
				print_all_medicine(get_Meds(temporary_repo), get_capacity(temporary_repo));
				destroyRepository(temporary_repo);
			}
		}
		else if (main_command == 4)
		{
			unsigned int set_d_command;
			print_set_d();
			read_value(&set_d_command, "operation");
			if (set_d_command == 1)
			{
				Undo(ui.serv);
			}
			else if (set_d_command == 2)
			{
				Redo(ui.serv);
			}
			else if (set_d_command == 0)
			{
				continue;
			}
			else
			{
				printf("Invalid command! Going back to the main menu...\n");
			}
		}
		else if (main_command == 0)
		{
			break;
		}
		else
		{
			printf("Invalid command!\n");
		}
		printf("\n");
	}
}

UI createUI(Service serv)
{
	UI ui;
	ui.serv = serv;
	return ui;
}

void print_set_a(void)
{
	printf("Add a new medicine | 1\n");
	printf("Delete a medicine | 2\n");
	printf("Update a medicine | 3\n");
	printf("Go back | 0\n");
}

void print_main_menu(void)
{
	printf("Set A | 1\n");
	printf("Set B | 2\n");
	printf("Set C | 3\n");
	printf("Set D | 4\n");
	printf("Exit | 0\n");
}

void read_string(char string[], char message[])
{
	printf("Insert %s: ", message);
	fgets(string, 100, stdin);
	string[strlen(string) - 1] = '\0';
}

void read_value(unsigned int* value, char message[])
{
	printf("Insert %s: ", message);
	scanf("%i", value);
	while (getchar() != '\n');
}

void print_all_medicine(Medicine* meds, unsigned int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		print_medicine(meds[i]);
	}
}

void print_set_d(void)
{
	printf("Undo last operation | 1\n");
	printf("Redo last undone - operation | 2\n");
	printf("Go back | 0\n");
}