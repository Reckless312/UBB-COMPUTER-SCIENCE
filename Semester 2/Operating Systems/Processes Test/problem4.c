#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Provide arguments!\n");
		exit(3);
	}
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);
	int f = fork();
	if (f < 0)
	{
		perror("Error on fork!\n");
		exit(1);
	}
	else if (f == 0)
	{
		if(execvp(argv[1], argv + 1) == -1)
		{
			perror("Error on exec");
			exit(2);
		}
	}
	else
	{
		wait(0);
		gettimeofday(&tv2, NULL);
		 printf("Total time = %f seconds\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
	}
	return 0;
}
