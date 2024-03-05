#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int change;
    do
    {
        change = get_int("Change owed: ");
    }
    while(change <= 0);
    int coins[4] = {25, 10, 5, 1};
    int total_coins = 0;
    for (int coin = 0; coin < 4; coin++)
    {
        while(change >= coins[coin])
        {
            change = change - coins[coin];
            total_coins++;
        }
    }
    printf("%i\n", total_coins);
}
