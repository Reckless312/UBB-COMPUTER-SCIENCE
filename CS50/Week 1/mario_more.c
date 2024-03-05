#include <cs50.h>
#include <stdio.h>

void print_spaces(int height, int amount);
void print_blocks(int amount);

int main(void)
{
    int height;
    do
    {
        height = get_int("What height do you request? ");
    }
    while(height < 1 || height > 8);
    for (int row = 0; row < height; row++)
    {
        print_spaces(height, row);
        print_blocks(row);
        print_spaces(height, height - 3);
        print_blocks(row);
        printf("\n");
    }
}

void print_spaces(int height, int amount)
{
    for(int space = 0; space < height - amount - 1; space++)
        {
            printf(" ");
        }
}

void print_blocks(int amount)
{
    for(int blocks = 0; blocks < amount + 1; blocks++)
        {
            printf("#");
        }
}
