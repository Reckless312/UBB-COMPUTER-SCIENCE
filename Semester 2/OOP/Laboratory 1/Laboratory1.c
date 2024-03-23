#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void UI(void);
void print_commands(void);
void read_vector(int length, int vector[]);
int find_exponent(int n, int p);
void find_subsequence(int length, int vector[]);
int common_greater_divizor(int a, int b);

int main(void)
{
	UI();
	return 0;
}

void UI(void)
{
	/*
	* Menu
	*/
	int length = -1;
	int* vector = NULL;
	bool vector_initialized = false;
	while (true)
	{
		printf("Option 1: Read a vector\n");
		printf("Option 2: Problem set a)\n");
		printf("Option 3: Problem set b)\n");
		printf("Option 0: Exit the program\n");
		int answer;
		printf("Your option: ");
		scanf_s("%i", &answer);
		if (answer == 1)
		{
			printf("Length is: ");
			scanf_s("%i", &length);
			if (length <= 0)
			{
				continue;
			}
			vector = malloc(length * sizeof(int));
			read_vector(length, vector);
			vector_initialized = true;
		}
		else if (answer == 2)
		{
			int n, p;
			printf("Select the values for n: ");
			scanf_s("%i", &n);
			printf("Select the values for p: ");
			scanf_s("%i", &p);
			int exponent = find_exponent(n, p);
			printf("%i\n", exponent);
		}
		else if (answer == 3)
		{
			if (vector_initialized == true)
			{
				find_subsequence(length, vector);
			}
		}
		else if (answer == 0)
		{
			break;
		}
		else
		{
			printf("INVALID COMMAND!\n\n");
		}
	}
	if (vector_initialized == true)
	{
		free(vector);
	}
}

void print_commands(void)
{
	/*
	* Menu Commands
	*/
	printf("Option 1: Read a vector\n");
	printf("Option 2: Problem set a)\n");
	printf("Option 3: Problem set b)\n");
	printf("Option 0: Exit the program\n");
}

void read_vector(int length, int vector[])
{
	/*
	* length: int
	* vector: vector
	* Reads a vector of size "length" from the console
	* return: None
	*/
	for (int i = 0; i < length; i++)
	{
		scanf_s("%i", &vector[i]);
	}
}

int find_exponent(int n, int p)
{
	/*
	* n: int
	* p: int
	* Finds the exponent of a prime number p from the decomposition in prime factors of a given number n
	* return: int
	*/
	int exponent = 0;
	while (n % p == 0)
	{
		exponent += 1;
		n /= p;
	}
	return exponent;
}

void find_subsequence(int length, int vector[])
{
	/*
	* length: int
	* vector: vector
	* Finds the longest contiguous subsequence such that any two consecutive elements are relatively prime and prints their position
	* return: none
	*/
	int longetivity, max_longetivity, index;
	longetivity = max_longetivity = 0;
	index = -1;
	for (int i = 0; i < length - 1; i++)
	{
		if (common_greater_divizor(vector[i], vector[i + 1]) == 1)
		{
			longetivity++;
		}
		else
		{
			if (max_longetivity < longetivity)
			{
				max_longetivity = longetivity;
				longetivity = 0;
				index = i;
			}
		}
	}
	if (max_longetivity < longetivity)
	{
		max_longetivity = longetivity;
		index = length - 1;
	}
	for (int i = 0; i <= max_longetivity; i++)
	{
		printf("Element: %i | Position: %i\n", vector[index], index);
		index--;
	}
}

int common_greater_divizor(int a, int b)
{
	/*
	* a: int
	* b: int
	* Finds the greatest common divizor
	* return: int
	*/
	if (b == 0)
	{
		return a;
	}
	return common_greater_divizor(b, a % b);
}