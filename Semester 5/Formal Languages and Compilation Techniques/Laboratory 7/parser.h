#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "pif.h"

/* Token type definitions */
typedef enum {
    TOKEN_EOF = 0,
    TOKEN_CREATECOURSE = 258,
    TOKEN_ADDCOURSE = 259,
    TOKEN_SORTCOURSE = 260,
    TOKEN_PRINTCOURSE = 261,
    TOKEN_IF = 262,
    TOKEN_END = 263,
    TOKEN_ELIF = 264,
    TOKEN_ELSE = 265,
    TOKEN_FOR = 266,
    TOKEN_IN = 267,
    TOKEN_COMMA = 268,
    TOKEN_DOUBLEEQUAL = 269,
    TOKEN_DIFFERENTOPERATOR = 270,
    TOKEN_LESSOPERATOR = 271,
    TOKEN_LESSOREQUALOPERATOR = 272,
    TOKEN_GREATEROPERATOR = 273,
    TOKEN_GREATEROREQUALOPERATOR = 274,
    TOKEN_EXCLAMATION = 275,
    TOKEN_UPPERCOMMA = 276,
    TOKEN_DOT = 277,
    TOKEN_DOTANDCOMMA = 278,
    TOKEN_SLASH = 279,
    TOKEN_DASH = 280,
    TOKEN_OPENROUNDEDPARANTHESIS = 281,
    TOKEN_CLOSEROUNDEDPARANTHESIS = 282,
    TOKEN_UNDERLINE = 283,
    TOKEN_EQUAL = 284,
    TOKEN_OPENSQUAREDPARANTHESIS = 285,
    TOKEN_CLOSESQUAREDPARANTHESIS = 286,
    TOKEN_AND = 287,
    TOKEN_OR = 288,
    TOKEN_ASC = 289,
    TOKEN_DESC = 290,
    TOKEN_LENGTH = 291,
    TOKEN_SUM = 292,
    TOKEN_FINALGRADE = 293,
    TOKEN_POSSIBLEGRADE = 294,
    TOKEN_OUTPUT = 295,
    TOKEN_DEF = 296,
    TOKEN_COMMENT = 297,
    TOKEN_CALL = 298,
    TOKEN_GRADE = 299,
    TOKEN_IDENTIFIER = 300,
    TOKEN_STRING = 301,
    TOKEN_BOOLEAN = 302
} TokenType;

/* Union for token values */
typedef union {
    int num;
    char* str;
    bool boolean;
} TokenValue;

/* Token structure */
typedef struct {
    TokenType type;
    TokenValue value;
    int line;
} Token;

/* Parser state */
typedef struct {
    int current_token;
    TokenValue current_value;
    int line_number;
    int error_found;
    int token_index;
} ParserState;

/* Parser interface functions */
void parser_init(void);
void parser_destroy(void);
int parse_program(void);
void parser_error(const char* message);
void advance_token(void);

/* Internal parsing functions */
int parse_statement(void);
int parse_id_statement(void);
int parse_create(void);
int parse_add(void);
int parse_sort(void);
int parse_print(void);
int parse_if(void);
int parse_elif(void);
int parse_else(void);
int parse_for(void);
int parse_statements(void);
int parse_condition(void);
int parse_expression(void);
int parse_grades(void);
int parse_id(void);
int parse_identifier(void);
int parse_variable(void);
int parse_args(void);
int parse_value(void);
int parse_compare_operator(void);
int parse_logical_operator(void);
int parse_order(char** result);
int parse_function(void);
int parse_bool(void);
int parse_output(void);
int parse_define_function(void);
int parse_assign(void);
int parse_comment(void);
int parse_call(void);

#endif /* PARSER_H */
