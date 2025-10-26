/*** Definition Section ***/
%{
#include <string.h>
#include <stdlib.h>
#include <string.h>

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
    return;
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
IDENTIFIER   [a-zA-Z][a-z0-9A-Z]*
STRING       \".*\"

/*** Rule Section ***/
%%
					/* yytext is the text in the buffer */
create_course                                   { addToPIF(yytext, createPair(-1, -1)); }
add                                   { addToPIF(yytext, createPair(-1, -1)); }
sort                                  { addToPIF(yytext, createPair(-1, -1)); }
print                                  { addToPIF(yytext, createPair(-1, -1)); }
if                                  { addToPIF(yytext, createPair(-1, -1)); }
end                                   { addToPIF(yytext, createPair(-1, -1)); }
elif                                  { addToPIF(yytext, createPair(-1, -1)); }
else                                  { addToPIF(yytext, createPair(-1, -1)); }
for                                  { addToPIF(yytext, createPair(-1, -1)); }
in                                   { addToPIF(yytext, createPair(-1, -1)); }
\,                                   { addToPIF(yytext, createPair(-1, -1)); }
\==                                 { addToPIF(yytext, createPair(-1, -1)); }
\!=                                  { addToPIF(yytext, createPair(-1, -1)); }
\<                                  { addToPIF(yytext, createPair(-1, -1)); }
\<=                                 { addToPIF(yytext, createPair(-1, -1)); }
\>                                   { addToPIF(yytext, createPair(-1, -1)); }
\>=                                  { addToPIF(yytext, createPair(-1, -1)); }
\!                                  { addToPIF(yytext, createPair(-1, -1)); }
\'                                  { addToPIF(yytext, createPair(-1, -1)); }
\.                                 { addToPIF(yytext, createPair(-1, -1)); }
\;                                  { addToPIF(yytext, createPair(-1, -1)); }
\/                                   { addToPIF(yytext, createPair(-1, -1)); }
\-                                   { addToPIF(yytext, createPair(-1, -1)); }
\(                                   { addToPIF(yytext, createPair(-1, -1)); }
\)                                   { addToPIF(yytext, createPair(-1, -1)); }
\_                                   { addToPIF(yytext, createPair(-1, -1)); }
\=                                   { addToPIF(yytext, createPair(-1, -1)); }
\[                                   { addToPIF(yytext, createPair(-1, -1)); }
\]                                   { addToPIF(yytext, createPair(-1, -1)); }
and                                  { addToPIF(yytext, createPair(-1, -1)); }
or                                   { addToPIF(yytext, createPair(-1, -1)); }
asc                                  { addToPIF(yytext, createPair(-1, -1)); }
desc                                  { addToPIF(yytext, createPair(-1, -1)); }
length                                  { addToPIF(yytext, createPair(-1, -1)); }
sum                                 { addToPIF(yytext, createPair(-1, -1)); }
final_grade                                   { addToPIF(yytext, createPair(-1, -1)); }
possible_grade                                   { addToPIF(yytext, createPair(-1, -1)); }
output                                   { addToPIF(yytext, createPair(-1, -1)); }
def                                   { addToPIF(yytext, createPair(-1, -1)); }
{IDENTIFIER}				{ Pair stCode = insert(symbolTable, yytext); addToPIF(yytext, stCode); }
{GRADE}                           { Pair stCode = insert(symbolTable, yytext); addToPIF(yytext, stCode); }
{STRING}				{ Pair stCode = insert(symbolTable, yytext); addToPIF(yytext, stCode); }
[\n]					{ ++lineNumber; }
[ \t\n]+             			{ ; /* eat up whitespace */ }
.                			{ errorFound = 1; printf("Illegal token %s at line %d !", yytext, lineNumber); printf("\n"); }
%%

/* yywrap() - wraps the above rule section */
int yywrap() {}

int main(int argc, char** argv) {

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