/*** Definition Section ***/
%{
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"

#define ST_UPPER_BOUND 100
#define PIF_SIZE 100
#define STRING_SIZE 257

int symLength = 0;


struct node {
    char token[STRING_SIZE];
    int index;
    struct node* left;
    struct node* right;
};

void setNode(struct node** node, char* token, int index)
{
    *node = (struct node*)malloc(sizeof(struct node));
    strncpy((*node)->token, token, STRING_SIZE - 1);
    (*node)->index = index;
    (*node)->right = NULL;
    (*node)->left = NULL;
    return;
}

int insert(struct node** node, char* token) {
    if (*node == NULL) {
        setNode(node, token, symLength);
        symLength++;
        return symLength - 1;
    }

    if (strcmp(token, (*node)->token) < 0) {
        return insert(&(*node)->left, token);
    }
    else if(strcmp(token, (*node)->token) > 0){
        return insert(&(*node)->right, token);
    }
    else{
        return (*node)->index;
    }
}

void inOrder(struct node* node) {
    if (node != NULL) {
        inOrder(node->left);
        printf("%s   %d\n", node->token, node->index);
        inOrder(node->right);
    }
}

const char * identifierFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/identifier.txt";
const char * stringFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/string.txt";
const char * numberFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/numerical.txt";
const char * booleanFilePath = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Formal Languages and Compilation Techniques/Laboratory 5/boolean.txt";

grammar_node* identifierGrammar;
grammar_node* stringGrammar;
grammar_node* numberGrammar;
grammar_node* booleanGrammar; 

typedef struct {
    char token[257];
    int symbolTableCode;
}PIF;

struct node* symbolTable;

PIF ProgramInternalForm[300];
int pifLength = 0;
int lineNumber = 1;

int errorFound = 0;

void addToPIF(char* token, int stCode) {
	strcpy(ProgramInternalForm[pifLength].token, token);
	ProgramInternalForm[pifLength].symbolTableCode = stCode;
	
	pifLength++;
}

void showSymbolTable() {
    printf("~~~~~~~ Symbol table ~~~~~~~\n");

    inOrder(symbolTable);

    printf("~~~~~~~ End ST ~~~~~~~\n");
    printf("\n");
}

void showProgramInternalForm() {
    printf("~~~~~~~ Program internal form ~~~~~~~\n");
    
    for(int i = 0; i < pifLength; i++) {
    
        printf(" %s  %d", ProgramInternalForm[i].token, ProgramInternalForm[i].symbolTableCode);
        printf("\n");
    }
    
    printf("~~~~~~~ End PIF ~~~~~~~\n");
    printf("\n");
}

%}


GRADE   (10|[1-9])
BOOLEAN (true|false)
IDENTIFIER   [a-zA-Z][a-z0-9A-Z]*
STRING       \"[a-zA-Z 1-9_]*\"

/*** Rule Section ***/
%%
					/* yytext is the text in the buffer */
create_course                                   { addToPIF(yytext, -1); }
add                                   { addToPIF(yytext, -1); }
sort                                  { addToPIF(yytext, -1); }
print                                  { addToPIF(yytext, -1); }
if                                  { addToPIF(yytext, -1); }
end                                   { addToPIF(yytext, -1); }
elif                                  { addToPIF(yytext, -1); }
else                                  { addToPIF(yytext, -1); }
for                                  { addToPIF(yytext, -1); }
in                                   { addToPIF(yytext, -1); }
and                                  { addToPIF(yytext, -1); }
or                                   { addToPIF(yytext, -1); }
asc                                  { addToPIF(yytext, -1); }
desc                                  { addToPIF(yytext, -1); }
length                                  { addToPIF(yytext, -1); }
sum                                 { addToPIF(yytext, -1); }
final_grade                                   { addToPIF(yytext, -1); }
possible_grade                                   { addToPIF(yytext, -1); }
output                                   { addToPIF(yytext, -1); }
def                                   { addToPIF(yytext, -1); }
\,                                   { addToPIF(yytext, -1); }
\==                                 { addToPIF(yytext, -1); }
\!=                                  { addToPIF(yytext, -1); }
\<                                  { addToPIF(yytext, -1); }
\<=                                 { addToPIF(yytext, -1); }
\>                                   { addToPIF(yytext, -1); }
\>=                                  { addToPIF(yytext, -1); }
\!                                  { addToPIF(yytext, -1); }
\'                                  { addToPIF(yytext, -1); }
\.                                 { addToPIF(yytext, -1); }
\;                                  { addToPIF(yytext, -1); }
\/                                   { addToPIF(yytext, -1); }
\-                                   { addToPIF(yytext, -1); }
\(                                   { addToPIF(yytext, -1); }
\)                                   { addToPIF(yytext, -1); }
\_                                   { addToPIF(yytext, -1); }
\=                                   { addToPIF(yytext, -1); }
\[                                   { addToPIF(yytext, -1); }
\]                                   { addToPIF(yytext, -1); }
\"                                   { addToPIF(yytext, -1); }
{BOOLEAN}				{ if (VerifyWordGrammar(booleanGrammar, yytext) == true) {int stCode = insert(&symbolTable, yytext); addToPIF(yytext, stCode);} else {printf("Invalid boolean %s at line %d !\n", yytext, lineNumber);}}
{IDENTIFIER}		    { if (VerifyWordGrammar(identifierGrammar, yytext) == true) {int stCode = insert(&symbolTable, yytext); addToPIF(yytext, stCode);} else {printf("Invalid identifier %s at line %d !\n", yytext, lineNumber);} }
{GRADE}                 { if (VerifyWordGrammar(numberGrammar, yytext) == true) {int stCode = insert(&symbolTable, yytext); addToPIF(yytext, stCode);} else {printf("Invalid number %s at line %d !\n", yytext, lineNumber);} }
{STRING}				{ if (VerifyWordGrammar(stringGrammar, yytext) == true) {int stCode = insert(&symbolTable, yytext); addToPIF(yytext, stCode);} else {printf("Invalid string %s at line %d !\n", yytext, lineNumber);} }
[\n]					{ ++lineNumber; }
[ \t]+             			{ ; /* eat up whitespace */ }
.                			{ errorFound = 1; printf("Illegal token %s at line %d !", yytext, lineNumber); printf("\n"); }
%%

/* yywrap() - wraps the above rule section */
int yywrap() {}

int main(int argc, char** argv) {

    identifierGrammar = CreateGrammar(identifierFilePath);
    stringGrammar = CreateGrammar(stringFilePath);
    numberGrammar = CreateGrammar(numberFilePath);
    booleanGrammar = CreateGrammar(booleanFilePath); 

    symbolTable = NULL;
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