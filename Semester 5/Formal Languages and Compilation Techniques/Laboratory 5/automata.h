//
// Created by Cora on 11/13/25.
//

#ifndef LABORATORY_5_AUTOMATA_H
#define LABORATORY_5_AUTOMATA_H

#define BUFFER_SIZE 1024
#include <stdbool.h>
#include "grammar.h"

typedef struct function_node {
    char start[BUFFER_SIZE];
    char value[BUFFER_SIZE];
    char end[BUFFER_SIZE];
    struct function_node* next;
} function_node;

typedef struct automata_node {
    char initialState[BUFFER_SIZE];
    function_node* function;
    struct automata_node* next;
    bool isFinal;
} automata_node;

automata_node* CreateAutomata(grammar_node* grammar);
void PrintAutomata(const automata_node* automata);
bool VerifyWordAutomata(const automata_node* automata, const char* word);
bool CheckEpsilonAutomata (const automata_node* automata);

#endif //LABORATORY_5_AUTOMATA_H