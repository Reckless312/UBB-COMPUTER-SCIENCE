#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("What height do you request? ");
    }
    while(height <= 0);
    for (int i = 0; i < height; i++)
    {
        for(int space = 0; space < height - i - 1; space++)
        {
            printf(" ");
        }
        for(int block = 0; block < i + 1; block++)
        {
            printf("#");
        }
        printf("\n");
    }
}
