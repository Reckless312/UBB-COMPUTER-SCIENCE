#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Provide just one argument!\n");
		exit(1);
	}
	int N = atoi(argv[1]);
	int fd[2][2];
	int num[N];
	for(int i = 0; i < 2; i++)
	{
		if(pipe(fd[i]) == -1)
		{
			perror("Error on pipe");
			exit(2);
		}
	}
	int f = fork();
	if (f < 0)
	{
		perror("Error on fork");
		exit(3);
	}
	else if (f == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		int got[N];
		if(read(fd[0][0], got, sizeof(got)) == -1)
		{
			perror("Error on read");
			exit(4);
		}
		double average_cal = 0;
		for(int i = 0; i < N; i++)
		{
			printf("Number: %d\n", got[i]);
			average_cal = average_cal + got[i];
		}
		average_cal = (average_cal / 1.0) / (double) N;
		printf("Average inside process: %f\n", average_cal);
		if(write(fd[1][1], &average_cal, sizeof(double)) == -1)
		{
			perror("Error on write");
			exit(5);
		}
		close(fd[0][0]);
		close(fd[1][1]);
		return 0;
	}
	close(fd[1][1]);
	close(fd[0][0]);
	for(int i = 0; i < N; i++)
	{
		num[i] = random() % 1000;
	}
	if(write(fd[0][1], num, sizeof(num)) == -1)
	{
		perror("Error on write");
		exit(3);
	}
	double average;
	if(read(fd[1][0], &average, sizeof(double)) == -1)
	{
		perror("Error on read");
		exit(6);
	}
	wait(0);
	printf("Average: %f\n", average);
}
