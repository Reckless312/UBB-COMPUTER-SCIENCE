//
// Created by Cora on 11/11/25.
//

#include "grammar.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

grammar_node* CreateGrammar(const char* filePath) {
    FILE *file = fopen(filePath, "r");

    if (file == NULL) {
        printf("Wrong file path: %s\n", filePath);
        return NULL;
    }

    char* line = NULL;
    size_t length = 0;

    if (getline(&line, &length, file) == -1) {
        printf("File doesn't have a starting production\n");
        return NULL;
    }

    line[strcspn(line, "\n")] = 0;

    char* startingProduction = strdup(line);

    grammar_node* startingGrammarNode = NULL;
    grammar_node* currentGrammarNode = NULL;

    while (getline(&line, &length, file) != -1) {
        line[strcspn(line, "\n")] = 0;

        grammar_node* newNode = malloc(sizeof(grammar_node));
        newNode->production = NULL;
        newNode->next = NULL;

        strcpy(newNode->start, startingProduction);

        const char* symbol = strtok(line, " ->|");

        if (symbol == NULL) {
            printf("No left side provided");
            free(newNode);
            continue;
        }

        char* leftSide = strdup(symbol);

        symbol = strtok(NULL, " ->|");

        if (symbol == NULL) {
            printf("No right side provided");
            free(newNode);
            continue;
        }

        production_node* currentProduction = NULL;

        if (currentGrammarNode == NULL) {
            startingGrammarNode = newNode;
        }
        else {
            currentGrammarNode->next = newNode;
        }
        currentGrammarNode = newNode;

        while (symbol != NULL) {
            production_node* newProduction = malloc(sizeof(production_node));

            strcpy(newProduction->start, leftSide);
            strcpy(newProduction->end, symbol);
            newProduction->next = NULL;

            if (currentProduction == NULL) {
                currentGrammarNode->production = newProduction;
            }
            else {
                currentProduction->next = newProduction;
            }
            currentProduction = newProduction;

            symbol = strtok(NULL, " ->|");
        }

        free(leftSide);
    }

    free(line);
    free(startingProduction);

    fclose(file);
    return startingGrammarNode;
}

void PrintGrammar(const grammar_node* grammar) {
    const grammar_node* currentGrammarNode = grammar;

    while (currentGrammarNode != NULL) {
        production_node* currentProduction = currentGrammarNode->production;
        printf("%s -> ", currentProduction->start);
        while (currentProduction != NULL) {
            printf("%s | ", currentProduction->end);
            currentProduction = currentProduction->next;
        }
        printf("\n");
        currentGrammarNode = currentGrammarNode->next;
    }
}

bool VerifyWord(grammar_node* grammar, const char* word) {
    if (grammar == NULL || word == NULL) {
        printf("One parameter is null!\n");
        return false;
    }

    const int onlyTerminalLength = 1;

    bool isWordValid = false;

    const char* wordCopy = word;

    unsigned int wordLength = strlen(wordCopy);

    char start[BUFFER_SIZE];

    strcpy(start, grammar->start);

    const grammar_node* currentGrammarNode = grammar;

    while (currentGrammarNode != NULL) {
        const production_node* currentProductionNode = currentGrammarNode->production;

        if (strcmp(currentProductionNode->start, start) != 0) {
            currentGrammarNode = currentGrammarNode->next;
            continue;
        }

        while (currentProductionNode != NULL) {
            const unsigned int productionLength = strlen(currentProductionNode->end);

            const int compareResult = strncmp(wordCopy, currentProductionNode->end, onlyTerminalLength);

            if (compareResult != 0) {
                currentProductionNode = currentProductionNode->next;
                continue;
            }

            if (productionLength == onlyTerminalLength) {
                if (wordLength == 1) {
                    return true;
                }

                currentProductionNode = currentProductionNode->next;
                continue;
            }

            if (wordLength == 1) {
                currentProductionNode = currentProductionNode->next;
                continue;
            }

            strcpy(start, currentProductionNode->end + productionLength - 1);
            wordCopy++;
            wordLength--;

            isWordValid = true;
            break;
        }

        if (isWordValid) {
            currentGrammarNode = grammar;
            isWordValid = false;
        }
        else {
            currentGrammarNode = currentGrammarNode->next;
        }
    }

    return false;
}
