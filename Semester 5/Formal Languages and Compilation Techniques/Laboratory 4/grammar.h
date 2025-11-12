//
// Created by Cora on 11/11/25.
//

#ifndef LABORATORY_4_GRAMMAR_H
#define LABORATORY_4_GRAMMAR_H

#define BUFFER_SIZE 1024

typedef struct production_node {
    char start[BUFFER_SIZE];
    char end[BUFFER_SIZE];
    struct production_node* next;
} production_node;

typedef struct grammar_node {
    char start[BUFFER_SIZE];
    struct production_node* production;
    struct grammar_node* next;
} grammar_node;

grammar_node* CreateGrammar(const char* filePath);
void PrintGrammar(const grammar_node* grammar);

#endif //LABORATORY_4_GRAMMAR_H