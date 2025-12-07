#include "pif.h"
#include <stdio.h>
#include <string.h>

int pifLength = 0;
PIF ProgramInternalForm[PIF_SIZE];

void addToPIF(char* token, Pair stCode) {
	strcpy(ProgramInternalForm[pifLength].token, token);
	ProgramInternalForm[pifLength].symbolTableCode = stCode;
	
	pifLength++;
}

void showProgramInternalForm() {
    printf("~~~~~~~ Program internal form ~~~~~~~\n");
    
    for(int i = 0; i < pifLength; i++) {
    
        printf(" %s  (%d, %d)", ProgramInternalForm[i].token, ProgramInternalForm[i].symbolTableCode.firstValue, ProgramInternalForm[i].symbolTableCode.secondValue);
        printf("\n");
    }
    
    printf("~~~~~~~ End PIF ~~~~~~~\n");
    printf("\n");
}