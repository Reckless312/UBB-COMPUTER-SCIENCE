#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void play(int fd[][2], int index)
{
	int reading_index = index % 2;
	int writing_index = (index + 1) % 2;
	for(int i = 0; i < 2; i++)
	{
		if(i == reading_index)
		{
			close(fd[i][1]);
		}
		else if(i == writing_index)
		{
			close(fd[i][0]);
		}
		else
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
	}
	int num = 1;
	srandom(getpid());
	if(index == 0)
	{
		num = (random() % 10) + 1;
		if(write(fd[writing_index][1], &num, sizeof(int)) == -1)
		{
			perror("Error on write");
			exit(4);
		}
	}
	while(num != 0)
	{
		if(read(fd[reading_index][0], &num, sizeof(int)) == -1)
		{
			perror("Error on read");
			exit(5);
		}
		if(num == 10)
		{
			num = 0;
			if(write(fd[writing_index][1], &num, sizeof(int)) == -1)
			{
				perror("Error on write");
				exit(6);
			}
			printf("Game has ended!\n");
			break;
		}
		else if(num == 0)
		{
			break;
		}
		else
		{
			printf("Process: %d got the number: %d\n", getpid(), num);
			num = (random() % 10) + 1;
			if(write(fd[writing_index][1], &num, sizeof(int)) == -1)
			{
				perror("Error on write");
				exit(7);
			}
		}
	}
	close(fd[writing_index][1]);
	close(fd[reading_index][0]);
}

int main()
{
	int fd[2][2];
	for(int i = 0; i < 2; i++)
	{
		if(pipe(fd[i]) == -1)
		{
			perror("Error on pipe");
			exit(3);
		}
	}
	int f = fork();
	if (f < 0)
	{
		perror("Error on fork");
		exit(1);
	}
	else if(f == 0)
	{
		play(fd, 0);
		return 0;
	}
	int g = fork();
	if (g < 0)
	{
		perror("Erron on fork");
		exit(2);
	}
	else if(g == 0)
	{
		play(fd, 1);
		return 0;
	}
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
	wait(0);
	wait(0);
	return 0;
}
