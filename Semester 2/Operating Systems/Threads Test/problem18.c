#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
	char* string;
}data;

void* f(void* arg)
{
	data d = *((data *) arg);
	for(int i = 0, n = strlen(d.string); i < n; i++)
	{
		if(isalpha(d.string[i]) && islower(d.string[i]))
		{
			d.string[i] = toupper(d.string[i]);
		}
	}
	printf("%s\n", d.string);
	return NULL;
}

int main(int argc, char** argv)
{
	int size = argc - 1;
	pthread_t* th = malloc(sizeof(pthread_t) * size);
	data* d = malloc(sizeof(data) * size);
	for(int i = 0; i < size; i++)
	{
		d[i].string = argv[i + 1];
		pthread_create(&th[i], NULL, f, &d[i]); 
	}
	for(int i = 0; i < size; i++)
	{
		pthread_join(th[i], NULL);
	}
	free(th);
	free(d);
}
