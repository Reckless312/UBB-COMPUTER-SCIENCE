#include "hash-table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeHashMap(ST* symbolTable) {
    symbolTable->numOfElements = 0;
    for (int i = 0; i < ST_SIZE; i++) {
        symbolTable->array[i] = NULL;
    }
}

int hashFunction(char* token) {
    int index;
    int sum = 0;

    for (int i = 0; i < strlen(token); i++) {
        sum += (int)token[i];
        sum %= ST_SIZE;
    }

    index = sum;
    return index;
}

Pair insert(ST* symbolTable, char* token){
    int index = hashFunction(token);
    int counter = 0;

    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    struct node* prevNode = NULL;
    struct node* currentNode = symbolTable->array[index];

    if (currentNode == NULL) {
        setNode(newNode, token, index, counter);
        symbolTable->array[index] = newNode;
        symbolTable->numOfElements++;
        return createPair(index, counter);
    }

    while(currentNode != NULL){
        if (strcmp(token, currentNode->token) == 0) {
            return createPair(currentNode->indexes.firstValue, currentNode->indexes.secondValue);
        }
        counter++;

        prevNode = currentNode;
        currentNode = currentNode->next;
    }
    setNode(newNode, token, index, counter);
    prevNode->next = newNode;
    symbolTable->numOfElements++;

    return createPair(index, counter);
}

void showSymbolTable(ST* symbolTable) {
    printf("~~~~~~~ Symbol table ~~~~~~~\n");

    for(int i = 0; i < ST_SIZE; i++) {
        struct node* currentNode = symbolTable->array[i];

        while (currentNode != NULL) {
            printf(" %s  (%d, %d)", currentNode->token, currentNode->indexes.firstValue, currentNode->indexes.secondValue);            
            printf("\n");
            currentNode = currentNode->next;
        }
    }
    printf("~~~~~~~ End ST ~~~~~~~\n");
    printf("\n");
}

void setNode(struct node* node, char* token, int hashIndex, int arrayIndex)
{
    strncpy(node->token, token, STRING_SIZE - 1);
    node->indexes.firstValue = hashIndex;
    node->indexes.secondValue = arrayIndex;
    node->next = NULL;
    return;
}

Pair createPair(int firstValue, int secondValue) {
    Pair result;
    result.firstValue = firstValue;
    result.secondValue = secondValue;
    return result;
}