#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct
{
	int* vec;
	int* position;
	pthread_mutex_t* mutex;
	pthread_cond_t* cond;
	int N;
}data;

void* f(void* arg)
{	
	data d = *((data*) arg);
	pthread_mutex_lock(d.mutex);
	if(*(d.position) % 2 != 0) pthread_cond_wait(d.cond, d.mutex);
	while(*(d.position) < d.N)
	{
		int x = rand() % 1000;
		if(x % 2 != 0)
		{
			x--;
		}
		if(*(d.position) < d.N)
		{
			d.vec[*(d.position)] = x;
			*(d.position) = *(d.position) + 1;
		}
		pthread_cond_signal(d.cond);
		if(*(d.position) % 2 != 0) pthread_cond_wait(d.cond, d.mutex);	
	}	
	pthread_cond_signal(d.cond);
	pthread_mutex_unlock(d.mutex);
	return NULL;
}

void* f2(void* arg)
{
        data d = *((data*) arg);
        pthread_mutex_lock(d.mutex);
        if(*(d.position) % 2 == 0) pthread_cond_wait(d.cond, d.mutex);
        while(*(d.position) < d.N)
        {
                int x = rand() % 1000;
                if(x % 2 == 0)
                {
                        x--;
                }
                if(*(d.position) < d.N)
                {
                        d.vec[*(d.position)] = x;
                        *(d.position) = *(d.position) + 1;
                }
                pthread_cond_signal(d.cond);
                if(*(d.position) % 2 == 0) pthread_cond_wait(d.cond, d.mutex);
        }
        pthread_cond_signal(d.cond);
        pthread_mutex_unlock(d.mutex);
        return NULL;
}

int main(int argc, char** argv)
{
	int N;
	scanf("%d", &N);
	pthread_mutex_t* mutex = malloc(sizeof(pthread_mutex_t));
	int* vec = malloc(sizeof(int) * N);
	data* d = malloc(sizeof(data));
	int* position = malloc(sizeof(int));
	pthread_cond_t* cond = malloc(sizeof(pthread_cond_t));
	if(pthread_mutex_init(mutex, NULL) != 0)
	{
		perror("Error on creating mutex");
		exit(1);
	}
	if(pthread_cond_init(cond, NULL) != 0)
	{
		perror("Error on barrier");
		exit(5);
	}
	srand(getpid());
	pthread_t* th = malloc(sizeof(pthread_t) * 2);
	*(position) = 0;
	d->position = position;
	d->N = N;
	d->vec = vec;
	d->mutex = mutex;
	d->cond = cond;
	if(pthread_create(&th[0], NULL, f, d) != 0)
	{
		perror("Error on creating thread");
		exit(3);
	}	
	if(pthread_create(&th[1], NULL, f2, d) != 0)
	{
		perror("Error on creating thread");
		exit(4);
	}
	for(int i = 0; i < 2; i++)
	{
		pthread_join(th[i], NULL);
	}
	for(int i = 0; i < N; i++)
	{
		printf("%d ", vec[i]);
	}
	printf("\n");
	if(pthread_mutex_destroy(mutex) != 0)
	{
		perror("Error destroying mutex");
		exit(2);
	}
	free(vec);
	free(mutex);
	free(d);
	free(th);
	free(position);
	free(cond);
	return 0;
}
