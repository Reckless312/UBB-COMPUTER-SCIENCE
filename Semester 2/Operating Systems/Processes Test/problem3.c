#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
int f;
void child_handler(int signum)
{
	printf("Child process is exiting...\n");
	exit(0);
}

void parent_handler(int signum)
{
	printf("Parent process is exiting...\n");
	kill(f, SIGUSR1);
	wait(0);
	exit(0);
}

void zombie_handler(int signum)
{
	printf("Waiting for child to exit...\n");
	wait(0);
}

int main()
{
	f = fork();
	if(f < 0)
	{
		perror("Error on fork\n");
		exit(1);
	}
	else if (f == 0)
	{
		signal(SIGUSR1, child_handler);
		while(1)
		{
			printf("Child process is still running...\n");
			sleep(2);
		}
	}
	else
	{
		signal(SIGUSR1, parent_handler);
		signal(SIGCHLD, zombie_handler);
		while(1)
		{
			printf("Parent process is still running...\n");
			sleep(2);
		}
	}
	return 0;
}
