#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
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
	srandom(getpid());
	int num = 1;
	while(num != 0)
	{
		if(read(a2b, &num, sizeof(int)) == -1)
                {
                        perror("Error on read");
                        exit(8);
                }
                if(num == 10)
                {
                        printf("Process B won!\n");
                        num = 0;
                        if(write(b2a, &num, sizeof(int)) == -1)
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
                        printf("Process B got the number: %d\n", num);
                        num = (random() % 10) + 1;
                        if(write(b2a, &num, sizeof(int)) == -1)
                        {
                                perror("Error on write");
                                exit(10);
                        }
                }
	}
	close(a2b);
	close(b2a);
}
