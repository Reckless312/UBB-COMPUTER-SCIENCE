#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_score(string word);

int POINTS[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string player_one_word = get_string("Player 1: ");
    string player_two_word = get_string("Player 2: ");
    int player_one_score = 0, player_two_score = 0;
    player_one_score = calculate_score(player_one_word);
    player_two_score = calculate_score(player_two_word);
    if (player_one_score > player_two_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player_two_score > player_one_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int calculate_score(string word)
{
    int final_score = 0;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        if (isalpha(word[i]))
        {
            final_score = final_score + POINTS[toupper(word[i]) - 'A'];
        }
    }
    return final_score;
}
