// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <cs50.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 2048;

// Hash table
node *table[N];

unsigned int nrelem = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int key = hash(word);
    node* current = table[key];
    while(current != NULL)
    {
        if(strcasecmp(word, current->word) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int sum = 0;
    for(int i = 0, n = strlen(word); i < n; i++)
    {
        sum = (int)tolower(word[i]);
    }
    return sum % N;
}

bool initialize_node(node** current, char* word)
{
    *current = malloc(sizeof(node));
    if(*current == NULL)
    {
        return false;
    }
    strcpy((*current)->word, word);
    (*current)->next = NULL;
    return true;
}

void assign_node(node* current, unsigned int key)
{
    if(table[key] == NULL)
    {
        table[key] = current;
        return;
    }
    current->next = table[key];
    table[key] = current;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE* f = fopen(dictionary, "r");
    if(f == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    char c;
    int index = 0;
    while(fread(&c, sizeof(char), 1, f))
    {
        if(c != '\n')
        {
            word[index++] = c;
        }
        else
        {
            word[index] = '\0';
            nrelem++;
            unsigned int key = hash(word);
            node* new_node = NULL;
            if((initialize_node(&new_node, word)) == false)
            {
                return false;
            }
            assign_node(new_node, key);
            index = 0;
        }
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return nrelem;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++)
    {
        if(table[i] != NULL)
        {
            node* current = table[i];
            node* prev = NULL;
            while(current != NULL)
            {
                prev = current;
                current = current->next;
                free(prev);
            }
        }
    }
    return true;
}
