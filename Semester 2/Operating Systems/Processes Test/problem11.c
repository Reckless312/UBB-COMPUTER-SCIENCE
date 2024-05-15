#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	//Make pipes
	int a2b[2], b2a[2];
	if(pipe(a2b) == -1)
	{
		perror("Error on pipe");
		exit(3);
	}
	if(pipe(b2a) == -1)
	{
		perror("Error on pipe");
		exit(4);
	}
	//Open Process A
	int f = fork();
	if(f == -1)
	{
		perror("Error on fork");
		exit(1);
	}
	else if(f == 0)
	{
	//Process A
	//Close not used ends
		close(a2b[0]);
		close(b2a[1]);
	//Generate number n
		srandom(getpid());
		int n = (random() % 148) + 51;
		if(n % 2 == 1)
		{
			n++;
		}
		if(write(a2b[1], &n, sizeof(int)) == -1)
		{
			perror("Error on write");
			exit(4);
		}
		while(1)
		{
			if(read(b2a[0], &n, sizeof(int)) == -1)
			{
				perror("Error on read");
				exit(5);
			}
			if(n < 5)
			{
				printf("N is now: %d in process A\n", n);
				printf("Process A is exiting...\n");
				break;
			}
			else
			{
				printf("N is now: %d in process A\n", n);
				if(n % 2 == 1)
				{
					n++;
				}
				if(write(a2b[1], &n, sizeof(int)) == -1)
				{
					perror("Error on write");
					exit(5);
				}
			}
		}
		close(a2b[1]);
		close(b2a[0]);
		return 0;
	}
	//Open Process B
	int g = fork();
	if(g == -1)
	{
		perror("Error on fork");
		exit(2);
	}
	else if(g == 0)
	{
	//Process B
		close(a2b[1]);
                close(b2a[0]);
        //Generate number n
               	int n;
                while(1)
                {
                        if(read(a2b[0], &n, sizeof(int)) == -1)
                        {
                                perror("Error on read");
                                exit(7);
                        }
                        printf("N is now: %d in process B\n", n);
			n /= 2;
			if(write(b2a[1], &n, sizeof(int)) == -1)
			{
				perror("Error on write");
				exit(8);
			}
			if(n < 5)
			{
				printf("Process B is exiting...\n");
				break;
			}
                }
		close(a2b[0]);
		close(b2a[1]);
		return 0;
	}		
	//Parent
	//Close not used ends
	close(a2b[0]);
	close(a2b[1]);
	close(b2a[0]);
	close(b2a[1]);
	//Wait
	wait(0);
	wait(0);
}
