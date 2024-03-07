#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Not a good key!\n");
            return 1;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        int appeared = 0;
        for (int j = 0; j < 26; j++)
        {
            if (alphabet[i] == toupper(argv[1][j]))
            {
                appeared++;
            }
        }
        if (appeared != 1)
        {
            printf("Not a good key!\n");
            return 1;
        }
    }
    string plaintext = get_string("plaintext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]) && isalpha(plaintext[i]))
        {
            plaintext[i] = toupper(argv[1][plaintext[i] - 'A']);
        }
        else if (islower(plaintext[i]) && isalpha(plaintext[i]))
        {
            plaintext[i] = tolower(argv[1][plaintext[i] - 'a']);
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}
