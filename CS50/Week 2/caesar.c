#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int k = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isalpha(plaintext[i]))
        {
            int new_letter;
            if (isupper(plaintext[i]))
            {
                new_letter = (plaintext[i] - 'A' + k) % 26;
                plaintext[i] = alphabet[new_letter];
            }
            else
            {
                new_letter = (plaintext[i] - 'a' + k) % 26;
                plaintext[i] = tolower(alphabet[new_letter]);
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}
