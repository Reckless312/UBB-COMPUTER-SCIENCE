#include <stdbool.h>
#include <stdio.h>
#include "grammar.h"
#include "automata.h"

int main(void) {
    const char * identifierFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/identifier.txt";
    const char * stringFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/string.txt";
    const char * numberFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/numerical.txt";
    const char * booleanFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/boolean.txt";

    grammar_node* identifierGrammar = CreateGrammar(identifierFilePath);
    grammar_node* stringGrammar = CreateGrammar(stringFilePath);
    grammar_node* numberGrammar = CreateGrammar(numberFilePath);
    grammar_node* booleanGrammar = CreateGrammar(booleanFilePath);

    const automata_node* identifierAutomata = CreateAutomata(identifierGrammar);
    const automata_node* stringAutomata = CreateAutomata(stringGrammar);
    const automata_node* numberAutomata = CreateAutomata(numberGrammar);
    const automata_node* booleanAutomata = CreateAutomata(booleanGrammar);

    PrintGrammar(identifierGrammar);
    PrintGrammar(stringGrammar);
    PrintGrammar(numberGrammar);
    PrintGrammar(booleanGrammar);

    printf("----------------------------------------------------------------\n");

    PrintAutomata(identifierAutomata);
    PrintAutomata(stringAutomata);
    PrintAutomata(numberAutomata);
    PrintAutomata(booleanAutomata);

    printf("----------------------------------------------------------------\n");

    char* word = "true";

    const bool isIdentifierGrammar = VerifyWordGrammar(identifierGrammar, word);
    const bool isStringGrammar = VerifyWordGrammar(stringGrammar, word);
    const bool isNumberGrammar = VerifyWordGrammar(numberGrammar, word);
    const bool isBooleanGrammar = VerifyWordGrammar(booleanGrammar, word);

    const bool isIdentifierAutomata = VerifyWordAutomata(identifierAutomata, word);
    const bool isStringAutomata = VerifyWordAutomata(stringAutomata, word);
    const bool isNumberAutomata = VerifyWordAutomata(numberAutomata, word);
    const bool isBooleanAutomata = VerifyWordAutomata(booleanAutomata, word);

    printf("Word %s is identifier: %d\n", word, isIdentifierGrammar);
    printf("Word %s is string: %d\n", word, isStringGrammar);
    printf("Word %s is number: %d\n", word, isNumberGrammar);
    printf("Word %s is boolean: %d\n", word, isBooleanGrammar);

    printf("----------------------------------------------------------------\n");

    printf("Word %s is identifier: %d\n", word, isIdentifierAutomata);
    printf("Word %s is string: %d\n", word, isStringAutomata);
    printf("Word %s is number: %d\n", word, isNumberAutomata);
    printf("Word %s is boolean: %d\n", word, isBooleanAutomata);

    return 0;
}