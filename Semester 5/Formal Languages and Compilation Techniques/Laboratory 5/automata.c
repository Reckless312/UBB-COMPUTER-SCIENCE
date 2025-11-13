//
// Created by Cora on 11/13/25.
//

#include "automata.h"
#include "grammar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

automata_node* CreateAutomata(grammar_node* grammar) {
    if (grammar == NULL) {
        printf("Null grammar provided\n");
        return NULL;
    }

    char* initialState = strdup(grammar->start);

    automata_node* startingAutomataNode = NULL;
    automata_node* currentAutomataNode = NULL;

    const grammar_node* currentGrammarNode = grammar;

    while (currentGrammarNode != NULL) {
        automata_node* newNode = malloc(sizeof(automata_node));
        newNode->next = NULL;
        newNode->function = NULL;
        strcpy(newNode->initialState, initialState);

        const production_node* currentProduction = currentGrammarNode->production;

        if (currentAutomataNode == NULL) {
            startingAutomataNode = newNode;
        }
        else {
            currentAutomataNode->next = newNode;
        }
        currentAutomataNode = newNode;

        bool isFinal = false;

        function_node* currentFunction = NULL;

        while (currentProduction != NULL) {
            function_node* newFunction = malloc(sizeof(function_node));

            strcpy(newFunction->start, currentProduction->start);

            newFunction->next = NULL;

            const unsigned int productionLength = strlen(currentProduction->end);

            int compareResultEpsilon = strcmp(currentProduction->end, "ε");

            newFunction->value[0] = currentProduction->end[0];
            newFunction->value[1] = '\0';

            if (productionLength == 1 || compareResultEpsilon == 0) {
                newFunction->end[0] = '@';

                isFinal = true;
            }
            else{
                newFunction->end[0] = currentProduction->end[1];
            }

            if (compareResultEpsilon == 0) {
                strcpy(newFunction->value, "ε");
            }

            newFunction->end[1] = '\0';

            if (currentFunction == NULL) {
                currentAutomataNode->function = newFunction;
            }
            else {
                currentFunction->next = newFunction;
            }
            currentFunction = newFunction;

            currentProduction = currentProduction->next;
        }
        currentAutomataNode->isFinal = isFinal;

        currentGrammarNode = currentGrammarNode->next;
    }
    free(initialState);

    return startingAutomataNode;
}

void PrintAutomata(const automata_node* automata) {
    const automata_node* currentAutomataNode = automata;

    while (currentAutomataNode != NULL) {
        function_node* currentFunction = currentAutomataNode->function;
        while (currentFunction != NULL) {
            printf("%s ->(%s) %s | ", currentFunction->start, currentFunction->value, currentFunction->end);
            currentFunction = currentFunction->next;
        }
        printf("is final: %d\n", currentAutomataNode->isFinal);
        currentAutomataNode = currentAutomataNode->next;
    }
}

bool VerifyWordAutomata(const automata_node* automata, const char* word) {
    if (automata == NULL || word == NULL) {
        printf("One parameter is null!\n");
        return false;
    }

    bool isWordValid = false;

    const char* wordCopy = word;

    unsigned int wordLength = strlen(wordCopy);

    char start[BUFFER_SIZE];

    strcpy(start, automata->initialState);

    const automata_node* currentAutomataNode = automata;

    if (wordLength == 0) {
        return CheckEpsilonAutomata(automata);
    }

    while (currentAutomataNode != NULL) {
        const function_node* currentFunctionNode = currentAutomataNode->function;

        if (strcmp(currentFunctionNode->start, start) != 0) {
            currentAutomataNode = currentAutomataNode->next;
            continue;
        }

        while (currentFunctionNode != NULL) {
            const int compareResult = strncmp(wordCopy, currentFunctionNode->value, 1);

            if (compareResult != 0) {
                currentFunctionNode = currentFunctionNode->next;
                continue;
            }

            if (currentFunctionNode->end[0] == '@') {
                if (wordLength == 1) {
                    return true;
                }

                currentFunctionNode = currentFunctionNode->next;
                continue;
            }

            if (wordLength == 1) {
                currentFunctionNode = currentFunctionNode->next;
                continue;
            }

            strcpy(start, currentFunctionNode->end);
            wordCopy++;
            wordLength--;

            isWordValid = true;

            break;
        }

        if (isWordValid) {
            currentAutomataNode = automata;
            isWordValid = false;
        }
        else {
            currentAutomataNode = currentAutomataNode->next;
        }
    }
    return false;
}

bool CheckEpsilonAutomata (const automata_node* automata) {
    const char* epsilon = "ε";
    const char* finalState = "@";

    const automata_node* currentAutomataNode = automata;

    const char* start = currentAutomataNode->initialState;

    while (currentAutomataNode != NULL) {
        const function_node* currentFunctionNode = currentAutomataNode->function;

        if (strcmp(currentFunctionNode->start, start) != 0) {
            currentAutomataNode = currentAutomataNode->next;
            continue;
        }
        break;
    }

    if (currentAutomataNode == NULL) {
        return false;
    }

    const function_node* currentFunctionNode = currentAutomataNode->function;

    while (currentFunctionNode != NULL) {
        if (strcmp(currentFunctionNode->value, epsilon) == 0 && strcmp(currentFunctionNode->end, finalState) == 0) {
            return true;
        }
        currentFunctionNode = currentFunctionNode->next;
    }
    return false;
}