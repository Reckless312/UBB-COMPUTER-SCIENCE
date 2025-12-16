#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "grammar.h"
#include "automata.h"
#include "pif.h"
#include "production.h"
#include "LL1.h"

/* Global automata and grammar structures */
automata_node* identifierAutomata;
automata_node* stringAutomata;
automata_node* numberAutomata;
automata_node* booleanAutomata;

ST* symbolTable;
int errorFound = 0;
int lineNumber = 1;

/* File paths for automata definitions */
const char * identifierFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/identifier.txt";
const char * stringFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/string.txt";
const char * numberFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/numerical.txt";
const char * booleanFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/boolean.txt";

/**
 * Initialize parser system - load automata, grammars, and parsing tables
 */
int init_parser_system(void) {
    printf("[Initializing Parser System]\n");
    
    // Create automata from grammar files
    grammar_node* identifierGrammar = CreateGrammar(identifierFilePath);
    grammar_node* stringGrammar = CreateGrammar(stringFilePath);
    grammar_node* numberGrammar = CreateGrammar(numberFilePath);
    grammar_node* booleanGrammar = CreateGrammar(booleanFilePath);
    
    identifierAutomata = CreateAutomata(identifierGrammar);
    stringAutomata = CreateAutomata(stringGrammar);
    numberAutomata = CreateAutomata(numberGrammar);
    booleanAutomata = CreateAutomata(booleanGrammar);
    
    // Initialize symbol table
    symbolTable = (ST*)malloc(sizeof(ST));
    if (!symbolTable) {
        fprintf(stderr, "Error: Failed to allocate symbol table\n");
        return 0;
    }
    initializeHashMap(symbolTable);
    
    // Initialize production rules for LL(1) parsing
    InitializeProductionRules();
    FillFirst();
    FillFollow();
    FillParsingTable();
    
    printf("[Parser System Initialized Successfully]\n");
    return 1;
}

/**
 * Clean up parser system resources
 */
void cleanup_parser_system(void) {
    printf("[Cleaning up Parser System]\n");
    // Free automata and other resources as needed
}

/**
 * Main entry point
 */
int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    // Initialize parser system
    if (!init_parser_system()) {
        fprintf(stderr, "Error: Failed to initialize parser system\n");
        return EXIT_FAILURE;
    }
    
    // Open input file
    extern FILE *yyin;
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    printf("\n========================================\n");
    printf("  Parsing File: %s\n", argv[1]);
    printf("========================================\n\n");
    
    // Initialize and run parser
    parser_init();
    int parse_result = parse_program();
    
    printf("\n========================================\n");
    if (parse_result && !errorFound) {
        printf("  Parsing Completed Successfully\n");
        printf("========================================\n");
    } else {
        printf("  Parsing Failed with Errors\n");
        printf("========================================\n");
        parser_destroy();
        cleanup_parser_system();
        return EXIT_FAILURE;
    }
    
    // Optionally display results
    printf("\n[Symbol Table]\n");
    // showSymbolTable(symbolTable);
    
    printf("\n[Program Internal Form (PIF)]\n");
    // showProgramInternalForm();
    
    // Cleanup
    parser_destroy();
    cleanup_parser_system();
    
    return EXIT_SUCCESS;
}
