#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
	char* num;
	int* vec;
	pthread_mutex_t *mutexes;
}data;

void* f(void * arg)
{
	data d = *((data*) arg);
       	int num = atoi(d.num);
	while(num)
	{
		pthread_mutex_lock(&d.mutexes[num%10]);
		d.vec[num%10]++;
		pthread_mutex_unlock(&d.mutexes[num%10]);
		num/=10;
	}	
	return NULL;
}

int main(int argc, char** argv)
{
	int size = argc - 1;
	if(size == 0)
	{
		printf("Provide at least one argument!\n");
		exit(1);
	}	
	data* d = malloc(sizeof(data) * size);
	pthread_mutex_t *mutexes = malloc(sizeof(pthread_mutex_t) * 10);
	int* vec = malloc(sizeof(int) * 10);
	pthread_t *th  = malloc(sizeof(pthread_t) * size);
	for(int i = 0; i < 10; i++)
	{
		vec[i] = 0;
	}
	for(int i = 0; i < 10; i++)
	{
		if(pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			perror("Error on mutex");
			exit(2);
		}
	}
	for(int i = 0; i < size; i++)
	{
		d[i].num = argv[i + 1];
		d[i].mutexes = mutexes;
		d[i].vec = vec;
		if(pthread_create(&th[i], NULL, f, &d[i]) != 0)
		{
			perror("Error on create");
			exit(3);
		}	
	}
	for(int i = 0; i < size; i++)
	{
		pthread_join(th[i], NULL);
	}
	for(int i = 0; i < 10; i++)
	{
		printf("For digit %d, the frequency is %d\n",i, vec[i]);
	}
	for(int i = 0; i < 10; i++)
	{
		pthread_mutex_destroy(&mutexes[i]);
	}
	free(vec);
	free(d);
	free(mutexes);
	free(th);
	return 0;
}
