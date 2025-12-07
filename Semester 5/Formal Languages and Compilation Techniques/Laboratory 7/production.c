#include "production.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prodLength = 0;
PROD ProductionRules[PROD_SIZE];

void InitializeProductionRules() {
    const char* productionRulesFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 7/production-rules.txt";

    ReadProductionsFromFile(productionRulesFilePath);
}

void ReadProductionsFromFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");

    if (file == NULL) {
        printf("Wrong file path: %s\n", filePath);
        return;
    }

    char* line = NULL;
    size_t length = 0;

    while (getline(&line, &length, file) != -1) {
        line[strcspn(line, "\n")] = 0;

        const char* symbol = strtok(line, "->");

        if (symbol == NULL) {
            printf("No left side provided");
            continue;
        }

        char* leftSide = strdup(symbol);
        
        symbol = strtok(NULL, "->");

        if (symbol == NULL) {
            printf("No right side provided");
            continue;
        }

        ProductionRules[prodLength].start = leftSide[0];
        strcpy(ProductionRules[prodLength].end, symbol);
        ProductionRules[prodLength].index = prodLength;

        free(leftSide);

        prodLength++;
    }

    free(line);

    fclose(file);
}

void PrintProductions() {
    for (int i = 0; i < prodLength; i++) {
        printf("%c -> %s | index: %d\n", ProductionRules[i].start, ProductionRules[i].end, ProductionRules[i].index);
    }
}