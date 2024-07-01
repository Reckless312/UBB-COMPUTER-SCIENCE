#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
	int id;
	int checkpoint;
	int m;
	pthread_mutex_t* mutex;
	pthread_barrier_t* barrier;
}data;

void* race(void* arg)
{
	data d = *((data *) arg);
	pthread_barrier_wait(d.barrier);
	while(d.checkpoint < d.m)
	{
		pthread_mutex_lock(d.mutex);
		d.checkpoint++;
		printf("Thread: %d has arrived at checkpoint: %d\n",d.id, d.checkpoint);
		pthread_mutex_unlock(d.mutex);
		int n = rand() % 100000;
		usleep(n + 100000);
	}
	return NULL;
}

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("Please provide exactly 2 arguments!\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	if(n == 0 || m == 0)
	{
		printf("Please provide numbers strictly bigger than 0\n");
		exit(2);
	}
	pthread_t* th = malloc(sizeof(pthread_t) * n);
	pthread_barrier_t* barrier = malloc(sizeof(pthread_barrier_t));
	pthread_mutex_t* mutex = malloc(sizeof(pthread_mutex_t) * m);
	data* d = malloc(sizeof(data) * n);
	for(int i = 0; i < m; i++)
	{
		pthread_mutex_init(&mutex[i], NULL);
	}
	pthread_barrier_init(barrier, NULL, n);
	srand(getpid());
	for(int i = 0; i < n; i++)
	{
		d[i].id = i;
		d[i].checkpoint = 0;
		d[i].m = m;
		d[i].mutex = mutex;
		d[i].barrier = barrier;
		pthread_create(&th[i], NULL, race, &d[i]);  
	}
	for(int i = 0; i < n; i++)
	{
		pthread_join(th[i], NULL);
	}
	pthread_barrier_destroy(barrier);
	free(th);
	free(barrier);
	free(mutex);
	free(d);
	return 0;
}
