/*** Definition Section ***/
%{
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"
#include "y.tab.h"
#include "pif.h"

extern automata_node* identifierAutomata;
extern automata_node* stringAutomata;
extern automata_node* numberAutomata;
extern automata_node* booleanAutomata;

extern ST* symbolTable;

extern int errorFound;
extern int lineNumber;

%}

STRING   \"([^\"\\]|\\.)*\"
COMMENT \/\/[^\n]*
GENERAL [a-zA-Z_][a-zA-Z0-9_]*

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
call                                   { addToPIF(yytext, createPair(-1, -1)); return CALL;}
{STRING}                              { if (VerifyWordAutomata(stringAutomata, yytext) == true) {
                                                Pair stCode = insert(symbolTable, yytext);
                                                addToPIF(yytext, stCode);
                                                yylval.str = strdup(yytext);
                                                return STRING;
                                        } 
                                        }
{COMMENT}                             { return COMMENT; }
{GENERAL}                              {
                                        if (VerifyWordAutomata(booleanAutomata, yytext) == true) {
                                            Pair stCode = insert(symbolTable, yytext);
                                            addToPIF(yytext, stCode);
                                            yylval.boolean = (strcmp(yytext, "true") == 0) ? true : false;
                                            return BOOLEAN;
                                        }
                                        else if (VerifyWordAutomata(identifierAutomata, yytext) == true) {
                                                Pair stCode = insert(symbolTable, yytext);
                                                addToPIF(yytext, stCode);
                                                yylval.str = strdup(yytext);
                                                return IDENTIFIER;
                                        }
                                        else if (VerifyWordAutomata(numberAutomata, yytext) == true) {
                                                Pair stCode = insert(symbolTable, yytext);
                                                addToPIF(yytext, stCode);
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