#ifndef PRODUCTION_RULES_H
#define PRODUCTION_RULES_H

#define END_SIZE 1024
#define PROD_SIZE 1000

typedef struct {
    char start;
    char end[END_SIZE];
    int index;
}PROD;

extern PROD ProductionRules[PROD_SIZE];
extern int prodLength;

void InitializeProductionRules();
void ReadProductionsFromFile(const char* filePath);
void PrintProductions();

#endif