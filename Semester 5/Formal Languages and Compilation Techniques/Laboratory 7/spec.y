%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "grammar.h"
    #include "automata.h"
    #include "pif.h"

    int yylex(void);
    void yyerror(char *s);
    extern FILE *yyin;
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
    int errorFound = 0;
    int lineNumber = 1;
%}

%union {int num; char* str; bool boolean; }

%token CREATECOURSE ADDCOURSE SORTCOURSE PRINTCOURSE IF END ELIF ELSE FOR IN
%token COMMA DOUBLEEQUAL DIFFERENTOPERATOR LESSOPERATOR LESSOREQUALOPERATOR
%token GREATEROPERATOR GREATEROREQUALOPERATOR EXCLAMATION UPPERCOMMA DOT DOTANDCOMMA
%token SLASH DASH OPENROUNDEDPARANTHESIS CLOSEROUNDEDPARANTHESIS UNDERLINE EQUAL
%token OPENSQUAREDPARANTHESIS CLOSESQUAREDPARANTHESIS AND OR ASC DESC LENGTH SUM
%token FINALGRADE POSSIBLEGRADE OUTPUT DEF COMMENT CALL
%token <num> GRADE
%token <str> IDENTIFIER STRING
%token <boolean> BOOLEAN

%type <str> id identifier variable args grades order
%type <num> value
%type <boolean> bool

%left OR
%left AND
%nonassoc DOUBLEEQUAL DIFFERENTOPERATOR LESSOPERATOR LESSOREQUALOPERATOR GREATEROPERATOR GREATEROREQUALOPERATOR
%%

program:
    statement { printf("Program -> statement\n"); }
    | statement program { printf("Program -> statement, program\n"); }
    ;

statement:
    create { printf("Statement -> create\n"); }
    | add { printf("Statement -> add\n"); }
    | sort { printf("Statement -> sort\n"); }
    | print { printf("Statement -> print\n"); }
    | if { printf("Statement -> if\n"); }
    | for { printf("Statement -> for\n"); }
    | output { printf("Statement -> output\n"); }
    | define_function { printf("Statement -> define_function\n"); }
    | assign { printf("Statement -> assign\n"); }
    | comment { printf("Statement -> comment\n"); }
    | call { printf("Statement -> call\n"); }
    ;

create:
    CREATECOURSE id { printf("Create -> CREATECOURSE id\n"); }
    | CREATECOURSE id EQUAL OPENSQUAREDPARANTHESIS grades CLOSESQUAREDPARANTHESIS { printf("Create -> CREATECOURSE id = [grades]"); }
    ;

add:
    id ADDCOURSE OPENROUNDEDPARANTHESIS grades CLOSEROUNDEDPARANTHESIS { printf("Add -> id ADDCOURSE [grades]\n"); }
    ;

sort:
    id SORTCOURSE order { printf("Sort -> id SORTCOURSE order\n"); }
    ;

print:
    id PRINTCOURSE { printf("Print -> id PRINTCOURSE\n"); }
    ;

if:
    IF condition statements elif else END { printf("If -> IF ... END\n"); }
    ;

elif:
    /* epsilon */ { }
    | ELIF condition statements elif { printf("Elif -> ELIF ...\n"); }
    ;

else:
    /* epsilon */ { }
    | ELSE statements { printf("Else -> ELSE ...\n"); }
    ;

for:
    FOR variable IN id statements END { printf("For -> FOR variable IN id ... END\n"); }
    ;

statements:
    statement { }
    | statement statements { }
    ;

condition:
    expression { }
    ;

expression:
    variable { }
    | expression compare_operator expression { }
    | expression logical_operator expression { }
    | function OPENROUNDEDPARANTHESIS args CLOSEROUNDEDPARANTHESIS { }
    | bool { }
    | value { }
    ;

grades:
    value { }
    | value COMMA grades { }
    ;

id:
    identifier { }
    ;

args:
    id { }
    | id COMMA args { }
    ;

variable:
    identifier { }
    ;

identifier:
    IDENTIFIER { }
    ;

compare_operator:
    DOUBLEEQUAL
    | DIFFERENTOPERATOR
    | LESSOPERATOR
    | LESSOREQUALOPERATOR
    | GREATEROPERATOR
    | GREATEROREQUALOPERATOR
    ;

logical_operator:
    AND
    | OR
    ;

order:
    ASC {$$ = "ASC";}
    | DESC {$$ = "DESC";}
    ;

value:
    GRADE { }
    ;

function:
    LENGTH
    | SUM
    | FINALGRADE
    | POSSIBLEGRADE
    | identifier
    ;

bool:
    BOOLEAN { }
    ;

output:
    OUTPUT STRING
    | OUTPUT id
    ;

define_function:
    DEF id OPENROUNDEDPARANTHESIS args CLOSEROUNDEDPARANTHESIS statements END
    ;

assign:
    id EQUAL expression
    ;

comment:
    COMMENT { printf("comment -> Comment\n"); }

call:
    CALL id OPENROUNDEDPARANTHESIS args CLOSEROUNDEDPARANTHESIS
    ;
%%

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
    yyin = fp;

    yyparse();

    if (errorFound == 0) {
    		showSymbolTable(symbolTable);
    		showProgramInternalForm();
	}
    
    return 0;
}

void yyerror(char* s) {
    fprintf(stderr, "Error: %s\n", s);
}