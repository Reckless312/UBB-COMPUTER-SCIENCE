#include "LL1.h"
#include "production.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char nonTerminals[MAX_NON_TERMINALS] = {'S', 'A'};
bool FIRST[MAX_NON_TERMINALS][MAX_TERMINALS] = {false};
bool FOLLOW[MAX_NON_TERMINALS] = {false};
LL1 ParseTable[MAX_NON_TERMINALS][MAX_TERMINALS];

int GetNonTerminalIndex(char nonTerminal) {
    for (int i = 0; i < MAX_NON_TERMINALS; i++) {
        if (nonTerminals[i] == nonTerminal) {
            return i;
        }
    }

    return -1;
}

void FillFirst() {
    while (true) {
        bool hasChanges = false;

        for (int i = 0; i < prodLength; i++) {
            int startIndex = GetNonTerminalIndex(ProductionRules[i].start);
            int endIndex = -1;

            int length = strlen(ProductionRules[i].end);

            if (strcmp(ProductionRules[i].end, "ε") == 0) {
                endIndex = EPSILON_INDEX;
            }
            else {
                endIndex = (int)ProductionRules[i].end[0];
            }

            if (endIndex != -1 && FIRST[startIndex][endIndex] == false) {
                FIRST[startIndex][endIndex] = true;
                hasChanges = true;
                continue;
            }
        }

        if (!hasChanges) {
            break;
        }
    }
}

void FillFollow() {
    if (prodLength < 1) {
        return;
    }

    char startingSymbol = ProductionRules[0].start;
    int startSymbolIndex = GetNonTerminalIndex(startingSymbol);

    FOLLOW[startSymbolIndex] = true;
    
    while (true) {
        bool hasChanges = false;

        for (int i = 0; i < prodLength; i++) {
            int startIndex = GetNonTerminalIndex(ProductionRules[i].start);

            int length = strlen(ProductionRules[i].end);

            if (length != 2) {
                continue;
            }

            char nonTerminal = ProductionRules[i].end[1];
            int endIndex = GetNonTerminalIndex(nonTerminal);

            if (FOLLOW[startIndex] == true && FOLLOW[endIndex] == false) {
                FOLLOW[endIndex] = true;
                hasChanges = true;
            }
        }

        if (!hasChanges) {
            break;
        }
    }
}

void FillParsingTable() {
    for (int i = 0; i < MAX_NON_TERMINALS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            ParseTable[i][j].index = -1;
        }
    }

    for (int i = 0; i < prodLength; i++) {
        char start = ProductionRules[i].start;
        int startIndex = GetNonTerminalIndex(start);
        int endIndex = -1;

        if (strcmp(ProductionRules[i].end, "ε") == 0) {
            endIndex = EPSILON_INDEX;

            if (FOLLOW[startIndex] == false) {
                continue;
            }
        }
        else {
            endIndex = (int) ProductionRules[i].end[0];

            if (FIRST[startIndex][endIndex] == false) {
                continue;
            }
        }

        if (ParseTable[startIndex][endIndex].index != -1) {
            printf("The Parse Table cannot be made!\n");
            return;
        }

        strcpy(ParseTable[startIndex][endIndex].production, ProductionRules[i].end);
        ParseTable[startIndex][endIndex].index = ProductionRules[i].index;
    }
}

void PrintParsingTable() {
     for (int i = 0; i < MAX_NON_TERMINALS; i++) {
        for (int j = 0; j < MAX_TERMINALS; j++) {
            if (ParseTable[i][j].index == -1) {
                continue;
            }

            printf("%s - index: %d | ", ParseTable[i][j].production, ParseTable[i][j].index);
        }
        printf("\n");
    }
}

int* ParseWord(char* word) {
    if (prodLength < 1) {
        return NULL;
    }

    char stack[512];
    int* resultIndexes = (int*) malloc(512 * sizeof(int)); 

    for (int i = 0; i < 512; i++) {
        resultIndexes[i] = -1;
    }

    int resultLength = 0;

    char startSymbol = ProductionRules[0].start;

    stack[0] = startSymbol;
    stack[1] = '\0';

    while (true) {
        int wordLength = strlen(word);
        int stackLength = strlen(stack);

        char symbol = stack[0];
        int symbolIndex = GetNonTerminalIndex(symbol);

        if (wordLength == 0 && stackLength > 1) {
            printf("Error on parsing\n");
            return NULL;
        }

        if (wordLength == 0 && ParseTable[symbolIndex][EPSILON_INDEX].index == -1) {
            printf("Error on parsing\n");
            return NULL;
        }

        if (wordLength == 0) {
            return resultIndexes;
        }

        if (stackLength == 2) {
            stack[0] = stack[1];
            stack[1] = stack[2];

            word++;

            continue;
        }

        if (ParseTable[symbolIndex][(int)*word].index == -1) {
            printf("Error on parsing\n");
            return NULL;
        }

        resultIndexes[resultLength++] = ParseTable[symbolIndex][(int)*word].index;
        strcpy(stack, ParseTable[symbolIndex][(int)*word].production);
    }
}