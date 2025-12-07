#ifndef PIF_H
#define PIF_H

#include "hash-table.h"

#define PIF_SIZE 100

extern PIF ProgramInternalForm[PIF_SIZE]
extern int pifLength;

typedef struct {
    char token[257];
    Pair symbolTableCode;
}PIF;

void addToPIF(char* token, Pair stCode);

void showProgramInternalForm();

#endif