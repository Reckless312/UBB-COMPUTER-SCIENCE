#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
int n, max;
int *numbers;
pthread_t * tids;
pthread_barrier_t barrier;

void* add(void * arg)
{
	int idx = *(int*) arg;
	pthread_barrier_wait(&barrier);
	int l, r;
	int i, j;
	if(idx < max / 2)
	{
		l = 2 * idx;
		r = l + 1;
		pthread_join(tids[l], NULL);
		pthread_join(tids[r], NULL);
	}
	j = max;
	while(j > idx && j > 1){ j /= 2;}
	i = j;
	l = 0;
	r = 0;
	while(i < idx)
	{
		i++;
		l += max/j;
	}
	r = l + max/ j/ 2;
	numbers[l] += numbers[r];
	return NULL;
}
int main(int argc, char**argv)
{
	if(argc != 2)
	{
		printf("Provide only one argument!\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	if(n < 1)
	{
		printf("Provide a strictly positive number\n");
		exit(2);
	}
	max = 1;
	while(max < n)
	{
		max*=2;
	}
	numbers = malloc(max* sizeof(int));
	int i;
	for(i = 0; i < max; i++)
	{
		if(i < n)
		{
			printf("a[%d]=", i);
			scanf("%d", &numbers[i]);
		}
		else
		{
			numbers[i] = 0;
		}
	}
	if(max == 1)
	{
		printf("%d\n", numbers[0]);
		free(numbers);
		return 0;
	}
	pthread_barrier_init(&barrier, NULL, max - 1);
	tids = malloc(sizeof(pthread_t) * max);
	int *ids = malloc(max * sizeof(int));
	for(i = 0; i < max; i++)
	{
		ids[i] = i;
	}
	for(i = 1; i< max; i++)
	{
		if(0 > pthread_create(&tids[i], NULL, add, (void*)(&ids[i])))
		{
			perror("Error on starting thread");
			exit(2);
		}
	}
	if(0 > pthread_join(tids[1], NULL))
	{
		perror("Error encountered while waiting fro thread to terminate");
	}
	printf("%d\n", numbers[0]);
	pthread_barrier_destroy(&barrier);
	free(numbers);
	free(tids);
	free(ids);
	return 0;
}
