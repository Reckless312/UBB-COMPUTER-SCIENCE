#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int boltz(int num)
{
	if(num % 7 == 0)
	{
		return 1;
	}
	while(num)
	{
		if(num % 10 == 7)
		{
			return 1;
		}
		num /= 10;
	}
	return 0;
}

void play(int fd[][2], int index, int N)
{
	int reading_index = index % N;
	int writing_index = (index + 1) % N;
	for(int i = 0; i < N; i++)
	{
		if(i == reading_index)
		{
			close(fd[i][1]);
		}
		else if (i == writing_index)
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
	if (index == 0)
	{
		if(write(fd[writing_index][1], &num, sizeof(int)) == -1)
		{
			perror("Error on write");
			exit(4);
		}
	}
	while(num >= 1)
	{
		if(read(fd[reading_index][0], &num, sizeof(int)) == -1)
		{
			printf("it's me: %d\n", getpid());
			perror("Error on read");
			exit(5);
		}
		if(num == 0)
		{
			if(write(fd[writing_index][1], &num, sizeof(int)) == -1)
			{
				perror("Error on write");
				exit(6);
			}
			break;
		}
		else
		{
			num++;
			if(boltz(num) == 1)
			{
				int success = random() % 5;
				if(success == 0)
				{
					num = 0;
					printf("Succes!\n");
				}
				else
				{
					printf("Boltz!\n");
				}
			}	
			else
			{
				printf("Process: %d got the number: %d\n", getpid(), num);
			}
			if(write(fd[writing_index][1], &num, sizeof(int)) == -1)
			{
				perror("Error on write");
				exit(7);
			}
		}
	}
	wait(0);
	close(fd[writing_index][1]);
	close(fd[reading_index][0]);
}

void create_processes(int fd[][2], int index, int N)
{
	if(index + 1 < N)
	{
		int f = fork();
		if(f < 0)
		{
			perror("Error on fork ");
			exit(3);
		}
		else if(f == 0)
		{
			create_processes(fd, index + 1, N);
			return;
		}
	}
	play(fd, index, N);
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Please provide just one argument!\n");
		exit(1);
	}
	int N = atoi(argv[1]);
	int fd[N][2];
	for(int i = 0; i < N; i++)
	{
		if(pipe(fd[i]) == -1)
		{
			perror("Error on pipe ");
			exit(2);
		}
	}
	create_processes(fd, 0, N);
}


