/*** Definition Section ***/
%{
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"
#include "y.tab.h"

#define ST_SIZE 10
#define PIF_SIZE 100
#define STRING_SIZE 257

extern automata_node* identifierAutomata;
extern automata_node* stringAutomata;
extern automata_node* numberAutomata;
extern automata_node* booleanAutomata;

// ST and PIF happy corner
// ---------------------------------------------------
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

ST* symbolTable;

PIF ProgramInternalForm[300];
int pifLength = 0;

// --------------------------------------------------

int errorFound = 0;
int lineNumber = 1;

%}

STRING   \"([^\"\\]|\\.)*\"
GRADE [0-9]+
COMMENT \/\/[^\n]*
GENERAL [a-zA-Z_][a-zA-Z0-9_]*

/*** Rule Section ***/
%%
					/* yytext is the text in the buffer */
create_course                                   { return CREATECOURSE;}
add                                   { return ADDCOURSE;}
sort                                  { return SORTCOURSE;}
print                                  { return PRINTCOURSE;}
if                                  { return IF;}
end                                   { return END;}
elif                                  { return ELIF;}
else                                  { return ELSE;}
for                                  { return FOR;}
in                                   { return IN;}
\,                                   { return COMMA;}
\==                                 { return DOUBLEEQUAL;}
\!=                                  { return DIFFERENTOPERATOR;}
\<                                  { return LESSOPERATOR;}
\<=                                 { return LESSOREQUALOPERATOR;}
\>                                   { return GREATEROPERATOR;}
\>=                                  { return GREATEROREQUALOPERATOR;}
\!                                  { return EXCLAMATION;}
\'                                  { return UPPERCOMMA;}
\.                                 { return DOT;}
\;                                  { return DOTANDCOMMA;}
\/                                   { return SLASH;}
\-                                   { return DASH;}
\(                                   { return OPENROUNDEDPARANTHESIS;}
\)                                   { return CLOSEROUNDEDPARANTHESIS;}
\_                                   { return UNDERLINE;}
\=                                   { return EQUAL;}
\[                                   { return OPENSQUAREDPARANTHESIS;}
\]                                   { return CLOSESQUAREDPARANTHESIS;}
and                                  { return AND;}
or                                   { return OR;}
asc                                  { return ASC;}
desc                                  { return DESC;}
length                                  { return LENGTH;}
sum                                 { return SUM;}
final_grade                                   { return FINALGRADE;}
possible_grade                                   { return POSSIBLEGRADE;}
output                                   { return OUTPUT;}
def                                   { return DEF;}
call                                   { return CALL;}
{STRING}                              { if (VerifyWordAutomata(stringAutomata, yytext) == true) {
                                                yylval.str = strdup(yytext); return STRING;
                                        } 
                                        }
{GRADE}                               { yylval.num = atoi(yytext); return GRADE; }
{COMMENT}                             { return COMMENT; }
{GENERAL}                              {
                                        if (VerifyWordAutomata(booleanAutomata, yytext) == true) {
                                            yylval.boolean = (strcmp(yytext, "true") == 0) ? true : false;
                                            return BOOLEAN;
                                        }
                                        else if (VerifyWordAutomata(identifierAutomata, yytext) == true) {
                                                yylval.str = strdup(yytext);
                                                return IDENTIFIER;
                                        }
                                        else if (VerifyWordAutomata(numberAutomata, yytext) == true) {
                                                yylval.num = atoi(yytext);
                                                return GRADE;
                                        }
                                        else {
                                                errorFound = 1; 
                                                printf("Invalid token %s at line %d !\n", yytext, lineNumber);
                                        }
                                    }
[\n]					        { ++lineNumber; }
[ \t\n]+             			{ ; /* eat up whitespace */ }
%%

int yyrap (void) {return 1;}