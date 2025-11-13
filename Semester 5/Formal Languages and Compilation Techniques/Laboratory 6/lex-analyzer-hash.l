/*** Definition Section ***/
%{
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"
#include "automata.h"
#include "spec.tab.h"

#define ST_SIZE 10
#define PIF_SIZE 100
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

void setNode(struct node* node, char* token, int hashIndex, int arrayIndex)
{
    strncpy(node->token, token, STRING_SIZE - 1);
    node->indexes.firstValue = hashIndex;
    node->indexes.secondValue = arrayIndex;
    node->next = NULL;
    return;
}

typedef struct {
    int numOfElements;
    struct node* array[ST_SIZE];
}ST;

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

Pair createPair(int firstValue, int secondValue) {
    Pair result;
    result.firstValue = firstValue;
    result.secondValue = secondValue;
    return result;
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

typedef struct {
    char token[257];
    Pair symbolTableCode;
}PIF;

const char * identifierFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/identifier.txt";
const char * stringFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/string.txt";
const char * numberFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/numerical.txt";
const char * booleanFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/boolean.txt";

grammar_node* identifierGrammar;
grammar_node* stringGrammar;
grammar_node* numberGrammar;
grammar_node* booleanGrammar; 

automata_node* identifierAutomata;
automata_node* stringAutomata;
automata_node* numberAutomata;
automata_node* booleanAutomata;

ST* symbolTable;

PIF ProgramInternalForm[300];
int pifLength = 0;

int errorFound = 0;
int lineNumber = 1;

void addToPIF(char* token, Pair stCode) {
	strcpy(ProgramInternalForm[pifLength].token, token);
	ProgramInternalForm[pifLength].symbolTableCode = stCode;
	
	pifLength++;
}

void showSymbolTable() {
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

void showProgramInternalForm() {
    printf("~~~~~~~ Program internal form ~~~~~~~\n");
    
    for(int i = 0; i < pifLength; i++) {
    
        printf(" %s  (%d, %d)", ProgramInternalForm[i].token, ProgramInternalForm[i].symbolTableCode.firstValue, ProgramInternalForm[i].symbolTableCode.secondValue);
        printf("\n");
    }
    
    printf("~~~~~~~ End PIF ~~~~~~~\n");
    printf("\n");
}

%}


GRADE (10|[1-9])
BOOLEAN   (true|false)
IDENTIFIER   [a-zA-Z][a-z0-9A-Z]*
STRING       \".*\"

/*** Rule Section ***/
%%
					/* yytext is the text in the buffer */
create_course                                   { addToPIF(yytext, createPair(-1, -1)); return CREATECOURSE;}
add                                   { addToPIF(yytext, createPair(-1, -1)); return ADDCOURSE;}
sort                                  { addToPIF(yytext, createPair(-1, -1)); return SORTCOURSE;}
print                                  { addToPIF(yytext, createPair(-1, -1)); return PRINTCOURSE;}
if                                  { addToPIF(yytext, createPair(-1, -1)); return IF;}
end                                   { addToPIF(yytext, createPair(-1, -1)); return END;}
elif                                  { addToPIF(yytext, createPair(-1, -1)); return ELIF;}
else                                  { addToPIF(yytext, createPair(-1, -1)); return ELSE;}
for                                  { addToPIF(yytext, createPair(-1, -1)); return FOR;}
in                                   { addToPIF(yytext, createPair(-1, -1)); return IN;}
\,                                   { addToPIF(yytext, createPair(-1, -1)); return COMMA;}
\==                                 { addToPIF(yytext, createPair(-1, -1)); return DOUBLEEQUAL;}
\!=                                  { addToPIF(yytext, createPair(-1, -1)); return DIFFERENTOPERATOR;}
\<                                  { addToPIF(yytext, createPair(-1, -1)); return LESSOPERATOR;}
\<=                                 { addToPIF(yytext, createPair(-1, -1)); return LESSOREQUALOPERATOR;}
\>                                   { addToPIF(yytext, createPair(-1, -1)); return GREATEROPERATOR;}
\>=                                  { addToPIF(yytext, createPair(-1, -1)); return GREATEROREQUALOPERATOR;}
\!                                  { addToPIF(yytext, createPair(-1, -1)); return EXCLAMATION;}
\'                                  { addToPIF(yytext, createPair(-1, -1)); return UPPERCOMMA;}
\.                                 { addToPIF(yytext, createPair(-1, -1)); return DOT;}
\;                                  { addToPIF(yytext, createPair(-1, -1)); return DOTANDCOMMA;}
\/                                   { addToPIF(yytext, createPair(-1, -1)); return SLASH;}
\-                                   { addToPIF(yytext, createPair(-1, -1)); return DASH;}
\(                                   { addToPIF(yytext, createPair(-1, -1)); return OPENROUNDEDPARANTHESIS;}
\)                                   { addToPIF(yytext, createPair(-1, -1)); return CLOSEROUNDEDPARANTHESIS;}
\_                                   { addToPIF(yytext, createPair(-1, -1)); return UNDERLINE;}
\=                                   { addToPIF(yytext, createPair(-1, -1)); return EQUAL;}
\[                                   { addToPIF(yytext, createPair(-1, -1)); return OPENSQUAREDPARANTHESIS;}
\]                                   { addToPIF(yytext, createPair(-1, -1)); return CLOSESQUAREDPARANTHESIS;}
and                                  { addToPIF(yytext, createPair(-1, -1)); return AND;}
or                                   { addToPIF(yytext, createPair(-1, -1)); return OR;}
asc                                  { addToPIF(yytext, createPair(-1, -1)); return ASC;}
desc                                  { addToPIF(yytext, createPair(-1, -1)); return DESC;}
length                                  { addToPIF(yytext, createPair(-1, -1)); return LENGTH;}
sum                                 { addToPIF(yytext, createPair(-1, -1)); return SUM;}
final_grade                                   { addToPIF(yytext, createPair(-1, -1)); return FINALGRADE;}
possible_grade                                   { addToPIF(yytext, createPair(-1, -1)); return POSSIBLEGRADE;}
output                                   { addToPIF(yytext, createPair(-1, -1)); return OUTPUT;}
def                                   { addToPIF(yytext, createPair(-1, -1)); return DEF;}
{BOOLEAN}				{ if(VerifyWordAutomata(booleanAutomata, yytext) == true) {Pair stCode = insert(symbolTable, yytext); addToPIF(yytext, stCode); return BOOLEAN;} else {printf("Invalid boolean %s at line %d !\n", yytext, lineNumber);}}
{IDENTIFIER}				{ if(VerifyWordAutomata(identifierAutomata, yytext) == true) {Pair stCode = insert(symbolTable, yytext); addToPIF(yytext, stCode); return IDENTIFIER;} else {printf("Invalid identifier %s at line %d !\n", yytext, lineNumber);}}
{GRADE}                           { if(VerifyWordAutomata(numberAutomata, yytext) == true) {Pair stCode = insert(symbolTable, yytext); addToPIF(yytext, stCode); return GRADE;} else {printf("Invalid number %s at line %d !\n", yytext, lineNumber);}}
{STRING}				{ if(VerifyWordAutomata(stringAutomata, yytext) == true) {Pair stCode = insert(symbolTable, yytext); addToPIF(yytext, stCode); return STRING;} else {printf("Invalid string %s at line %d !\n", yytext, lineNumber);}}
[\n]					{ ++lineNumber; }
[ \t\n]+             			{ ; /* eat up whitespace */ }
.                			{ errorFound = 1; printf("Illegal token %s at line %d !", yytext, lineNumber); printf("\n"); }
%%

/* yywrap() - wraps the above rule section */
int yywrap() {}

int main(int argc, char** argv) {

    identifierGrammar = CreateGrammar(identifierFilePath);
    stringGrammar = CreateGrammar(stringFilePath);
    numberGrammar = CreateGrammar(numberFilePath);
    booleanGrammar = CreateGrammar(booleanFilePath);

    identifierAutomata = CreateAutomata(identifierGrammar);
    stringAutomata = CreateAutomata(stringGrammar);
    numberAutomata = CreateAutomata(numberGrammar);
    booleanAutomata = CreateAutomata(booleanGrammar);

    symbolTable = (ST*)malloc(sizeof(ST));
    initializeHashMap(symbolTable);

	FILE *fp;
	fp = fopen(argv[1], "r");
	
	/* yyin - takes the file pointer which contains the input*/
	yyin = fp;

	/* yylex() - this is the main flex function which runs the Rule Section*/ 
	yylex();
	
	if (errorFound == 0) {
    		showSymbolTable();
    		showProgramInternalForm();
	}
  
	return 0;
}