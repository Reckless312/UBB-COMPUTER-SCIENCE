//
// Created by Cora on 11/11/25.
//

#include "grammar.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

grammar_vector* CreateGrammar(const char* filePath) {
    FILE *file = fopen(filePath, "r");

    if (file == NULL) {
        printf("Wrong file path: %s\n", filePath);
        return NULL;
    }

    grammar_vector* grammar = malloc(sizeof(grammar_vector));

    char* line = NULL;
    size_t length = 0;

    if (getline(&line, &length, file) == -1) {
        printf("File doesn't have a starting production\n");
        return NULL;
    }

    grammar->start = line[0];

    grammar_node* rule = malloc(sizeof(grammar_node));

    grammar->grammar = rule;

    int productionRulesLength = 0;
    // S -> A | B
    while (getline(&line, &length, file) != -1) {
        // Left side :)
        char* symbol = strtok(line, " ->|");
        strcpy(rule->start, symbol);
        printf("%s\n", rule->start);
        // Right side :(
        while (symbol != NULL) {
            symbol = strtok(NULL, " ->|");
        }
    }

    fclose(file);

    return grammar;
}
