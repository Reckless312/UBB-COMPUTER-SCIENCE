#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
	if(mkfifo("./a2b", 0600) == -1)
	{
		perror("Error on fifo");
		exit(1);
	}
	if(mkfifo("./b2a", 0600) == -1)
	{
		perror("Error on fifo");
		exit(2);
	}
	int a2b = open("./a2b", O_WRONLY);
	if(a2b == -1)
	{
		perror("Error on open");
		exit(3);
	}
	int b2a = open("./b2a", O_RDONLY);
	if(b2a == -1)
	{
		perror("Error on open");
		exit(4);
	}
	srandom(getpid());
	int num = (random() %10) + 1;
	if(write(a2b, &num, sizeof(int)) == -1)
	{
		perror("Error on write");
		exit(7);
	}
	while(num != 0)
	{
		if(read(b2a, &num, sizeof(int)) == -1)
		{
			perror("Error on read");
			exit(8);
		}
		if(num == 10)
		{
			printf("Process A won!\n");
			num = 0;
			if(write(a2b, &num, sizeof(int)) == -1)
			{
				perror("Error on write");
				exit(9);
			}
			break;
		}
		else if(num == 0)
		{
			break;
		}
		else
		{
			printf("Process A got the number: %d\n", num);
			num = (random() % 10) + 1;
			if(write(a2b, &num, sizeof(int)) == -1)
			{
				perror("Error on write");
				exit(10);
			}
		}
	}
	close(a2b);
	close(b2a);
	if(unlink("./a2b") == -1)
	{
		perror("Error on deleting");
		exit(5);
	}
	if(unlink("./b2a") == -1)
	{
		perror("Error on deleting");
		exit(6);
	}
}
