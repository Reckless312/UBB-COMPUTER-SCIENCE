//
// Created by Cora on 11/11/25.
//

#ifndef LABORATORY_4_GRAMMAR_H
#define LABORATORY_4_GRAMMAR_H

#define BUFFER_SIZE 1024

typedef struct grammar_node{
    // Need a starting symbol and a production rule.
    // + a way to get to the next prod rule in the batch

    char start[BUFFER_SIZE];
    char end[BUFFER_SIZE];
    struct grammar_node* next;
} grammar_node;

typedef struct {
    grammar_node* grammar;
    char start;
    int size;
} grammar_vector;

grammar_vector* CreateGrammar(const char* filePath);

#endif //LABORATORY_4_GRAMMAR_H