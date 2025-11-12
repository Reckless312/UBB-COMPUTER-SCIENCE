#include <stdbool.h>
#include <stdio.h>
#include "grammar.h"

int main(void) {
    const char * identifierFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 4/identifier.txt";
    const char * stringFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 4/string.txt";
    const char * numberFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 4/numerical.txt";
    const char * booleanFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 4/boolean.txt";

    const grammar_node* identifierGrammar = CreateGrammar(identifierFilePath);
    const grammar_node* stringGrammar = CreateGrammar(stringFilePath);
    const grammar_node* numberGrammar = CreateGrammar(numberFilePath);
    const grammar_node* booleanGrammar = CreateGrammar(booleanFilePath);

    PrintGrammar(identifierGrammar);
    PrintGrammar(stringGrammar);
    PrintGrammar(numberGrammar);
    PrintGrammar(booleanGrammar);

    char* word = "";

    const bool isIdentifier = VerifyWord(identifierGrammar, word);
    const bool isString = VerifyWord(stringGrammar, word);
    const bool isNumber = VerifyWord(numberGrammar, word);
    const bool isBoolean = VerifyWord(booleanGrammar, word);

    printf("Word %s is identifier: %d\n", word, isIdentifier);
    printf("Word %s is string: %d\n", word, isString);
    printf("Word %s is number: %d\n", word, isNumber);
    printf("Word %s is boolean: %d\n", word, isBoolean);

    return 0;
}