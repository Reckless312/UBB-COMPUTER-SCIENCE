//
// Created by Cora on 11/11/25.
//

#include "grammar.h"

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

    const char* startingProduction = strdup(line);

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

        const char* leftSide = strdup(symbol);

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
    }

    free(line);

    fclose(file);

    return startingGrammarNode;
}
