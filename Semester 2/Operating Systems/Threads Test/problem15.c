#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef struct{
	int id;
	char*s;
	int* number;
	int* letters;
	int* specials;
	pthread_mutex_t *mutexes;
}data;

void *fun(void *arg)
{
	data d = *((data*) arg);
	int letters, digits, specials;
	letters = digits = specials = 0;
	for(int i = 0, n = strlen(d.s); i < n; i++)
	{
		if(isdigit(d.s[i]))
		{
			digits++;
		}
		else if(isalpha(d.s[i]))
		{
			letters++;
		}
		else
		{
			specials++;
		}

	}
	if(digits > 0)
	{
		pthread_mutex_lock(&d.mutexes[0]);
		*(d.number) += digits;
		pthread_mutex_unlock(&d.mutexes[0]);
	}	
	if(letters > 0)
	{
		pthread_mutex_lock(&d.mutexes[1]);
		*(d.letters) += letters; 
		pthread_mutex_unlock(&d.mutexes[1]);
	}
	if(specials > 0)
        {
                pthread_mutex_lock(&d.mutexes[2]);
                *(d.specials) += specials;
                pthread_mutex_unlock(&d.mutexes[2]);
        }
	return NULL;
}

int main(int argc, char** argv)
{
	int size = argc - 1;
	int *letters = malloc(sizeof(int));
	int *digits = malloc(sizeof(int));
	int *specials = malloc(sizeof(int));
	pthread_t* th = malloc(sizeof(pthread_t) * size);
       	data *args = malloc(sizeof(data) * size);	
	pthread_mutex_t *mutexes = malloc(sizeof(pthread_mutex_t) * 3);
	for(int i = 0; i < 3; i++)
	{
		if(pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			perror("Error on mutexes");
			exit(1);
		}
	}
	*letters = 0;
	*digits = 0;
	*specials = 0;
	for(int i = 0; i < size; i++)
	{
		args[i].id = i;
		args[i].s = argv[i + 1];
		args[i].letters = letters;
		args[i].number = digits;
		args[i].specials = specials;
		args[i].mutexes = mutexes;
		if(pthread_create(&th[i], NULL, fun,(void *) &args[i]) != 0)
		{
			perror("Error on thread");
		}
	}
	for(int i = 0; i < size; i++)
	{
        	pthread_join(th[i], NULL);
	}
	printf("Total letters: %d, total numbers: %d, total specials: %d\n", *letters, *digits, *specials);
	for(int i = 0; i < 3; i++)
	{
		pthread_mutex_destroy(&mutexes[i]);
	}
	free(mutexes);
	free(letters);
	free(digits);
	free(specials);
	free(th);
	free(args);
	return 0;
}
