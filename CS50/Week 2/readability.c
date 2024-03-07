#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string text = get_string("Text: ");
    int number_of_letters = 0, number_of_words = 0, number_of_sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            number_of_letters++;
        }
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            number_of_sentences++;
        }
    }
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) && (text[i + 1] == ' ' || text[i + 1] == '.' || text[i + 1] == '!' ||
                                 text[i + 1] == '?' || text[i + 1] == ','))
        {
            number_of_words++;
        }
    }
    double L = number_of_letters * 100.0 / number_of_words;
    double S = number_of_sentences * 100.0 / number_of_words;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}
