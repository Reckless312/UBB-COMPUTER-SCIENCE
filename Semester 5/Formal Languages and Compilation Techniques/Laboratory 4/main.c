#include <stdio.h>
#include "grammar.h"

int main(void) {
    const char * identifierFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 4/identifier.txt";
    const char * stringFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 4/string.txt";
    const char * numberFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 4/numerical.txt";
    const char * booleanFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 4/boolean.txt";
    grammar_vector* identifierGrammar = CreateGrammar(identifierFilePath);
    grammar_vector* stringGrammar = CreateGrammar(stringFilePath);
    grammar_vector* numberGrammar = CreateGrammar(numberFilePath);
    grammar_vector* booleanGrammar = CreateGrammar(booleanFilePath);
    return 0;
}