#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char** argv)
{
	if(mkfifo("./a2b", 0600) == -1)
	{
		perror("Error on fifo");
		exit(1);
	}
	if(mkfifo("./b2a", 0600) == -1)
	{
		perror("Error on fifo");
		exit(3);
	}
	int a2b = open("./a2b", O_WRONLY);
	if(a2b == -1)
	{
		perror("Error on open");
		exit(5);
	}
	int b2a = open("./b2a", O_RDONLY);
	if(b2a == -1)
	{
		perror("Error on open");
		exit(6);
	}
	if(write(a2b, &argc, sizeof(int)) == -1)
	{
		perror("Error on write");
		exit(7);
	}
	for(int i = 1; i < argc; i++)
	{
		int length = strlen(argv[i]);
		if(write(a2b, &length, sizeof(int)) == -1)
		{
			perror("Error on write");
			exit(8);
		}		
		if(write(a2b, argv[i], sizeof(char) * (length + 1)) == -1)
		{
			perror("Error on write");
			exit(9);
		}
		if(read(b2a, argv[i], sizeof(char) * (length + 1)) == -1)
		{
			perror("Error on read");
			exit(10);
		}
	}
	for(int i = 1; i < argc;i++)
	{
		printf("%s ", argv[i]);
	}
	if(argc != 1)
	{
		printf("\n");
	}
	close(a2b);
	close(b2a);
	if(unlink("./a2b") == -1)
	{
		perror("Error on unlinking");
		exit(2);
	}
	if(unlink("./b2a") == -1)
	{
		perror("Error on unlinking");
		exit(4);
	}
}
