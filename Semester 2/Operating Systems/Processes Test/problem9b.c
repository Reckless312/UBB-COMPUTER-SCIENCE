#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv)
{
        int a2b = open("./a2b", O_RDONLY);
        if(a2b == -1)
        {
                perror("Error on open");
                exit(1);
        }
        int b2a = open("./b2a", O_WRONLY);
        if(b2a == -1)
        {
                perror("Error on open");
                exit(2);
        }
	int N;
	if(read(a2b, &N, sizeof(int)) == -1)
	{
		perror("Error on read");
		exit(3);
	}
	N--;
	char** arg = (char**) malloc(N * sizeof(char*));
	if(arg == NULL)
	{
		printf("Error on malloc\n");
		exit(4);
	}
	int length;
	for(int i = 0; i < N; i++)
	{
		if(read(a2b, &length, sizeof(int)) == -1)
		{
			perror("Error on read");
			exit(5);
		}		
		arg[i] = (char *) malloc((length + 1) * sizeof(char));
		if(arg[i] == NULL)
		{
			printf("Error on malloc\n");
			exit(6);
		}
		if(read(a2b, arg[i], sizeof(char) * (length + 1)) == -1)
		{
			perror("Error on read");
			exit(7);
		}
		for(int j = 0; j < length; j++)
		{
			arg[i][j] = tolower(arg[i][j]);
		}
		if(write(b2a, arg[i], sizeof(char) * (length + 1)) == -1)
		{
			perror("Error on write");
			exit(8);
		}
	}
	for(int i = 0; i < N; i++)
	{
		free(arg[i]);
	}
	free(arg);
	close(a2b);
	close(b2a);
}	
