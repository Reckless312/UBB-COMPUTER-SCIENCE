/*** Definition Section ***/
%{
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "automata.h"
#include "y.tab.h"

extern automata_node* identifierAutomata;
extern automata_node* stringAutomata;
extern automata_node* numberAutomata;
extern automata_node* booleanAutomata;

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