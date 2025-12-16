#ifndef LL1_H
#define LL1_H

#include <stdbool.h>

#define MAX_NON_TERMINALS 2
#define MAX_TERMINALS 256
#define EPSILON_INDEX 255
#define PRODUCTION_SIZE 50

typedef struct {
    char production[PRODUCTION_SIZE];
    int index;
}LL1;

extern char nonTerminals[MAX_NON_TERMINALS];

extern bool FIRST[MAX_NON_TERMINALS][MAX_TERMINALS];
extern bool FOLLOW[MAX_NON_TERMINALS];
extern LL1 ParseTable[MAX_NON_TERMINALS][MAX_TERMINALS];

void FillFirst();
void FillFollow();
void FillParsingTable();
void PrintParsingTable();
int* ParseWord(char* word);

#endif