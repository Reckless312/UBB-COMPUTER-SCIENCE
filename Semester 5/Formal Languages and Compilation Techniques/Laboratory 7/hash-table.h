#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define ST_SIZE 10
#define STRING_SIZE 257

typedef struct {
    int firstValue;
    int secondValue;
}Pair;

struct node {
    char token[STRING_SIZE];
    Pair indexes;
    struct node* next;
};

typedef struct {
    int numOfElements;
    struct node* array[ST_SIZE];
}ST;

void initializeHashMap(ST* symbolTable);

int hashFunction(char* token);

void showSymbolTable(ST* symbolTable);

Pair insert(ST* symbolTable, char* token);

void setNode(struct node* node, char* token, int hashIndex, int arrayIndex);

Pair createPair(int firstValue, int secondValue);

#endif