#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Please provide only one argument!\n");
		return 1;
	}
	for(int i = 0, n = strlen(argv[1]); i < n; i++)
	{
		if(!isdigit(argv[1][i]))
		{
			printf("Argument must be a number!\n");
			return 2;
		}
	}
	int n = atoi(argv[1]);
	for(int i = 0; i < n; i++)
	{
		int f = fork();
		if(f < 0)
		{
			perror("Error on fork");
		}
		else if(f == 0)
		{
                	printf("Child process: %d | Parent of child: %d\n",getpid(), getppid());
			exit(0);	
		}
		else
		{
			printf("Parent process: %d | Child process: %d\n", getpid(), f);
		}
	}
	for(int i = 0; i < n; i++)
	{
		wait(0);
	}
	return 0;
}
