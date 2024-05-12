#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Please provide just one argument!\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	for(int i = 0; i < n; i++)
	{
		int f = fork();
		if (f < 0)
		{
			perror("Error on fork!\n");
			exit(2);
		}
		else if (f == 0)
		{
			printf("Child process: %d, Parent process: %d\n", getpid(), getppid());
		}
		else
		{
			wait(0);
			exit(0);
		}
	}
	return 0;
}
