#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "pif.h"

/* External references from lexer and grammar */
extern int yylex(void);
extern FILE *yyin;
extern int lineNumber;
extern int errorFound;

/* yylval - token value, used by flex lexer */
union {
    int num;
    char* str;
    bool boolean;
} yylval;

/* yywrap - called at end of input, returns 1 to stop scanning */
int yywrap(void) {
    return 1;
}

/* Parser state */
static ParserState parser_state = {0};
static int next_token = 0;  /* Lookahead token */

/* Token lookahead */
static int current_token_type(void) {
    return parser_state.current_token;
}

/**
 * Peek at the next token without consuming it
 */
static int peek_token(void) {
    // This is a simplified version that would need proper implementation
    // For now, return the next_token if available
    return next_token;
}

/**
 * Initialize parser - call this before parsing
 */
void parser_init(void) {
    parser_state.current_token = 0;
    parser_state.line_number = 1;
    parser_state.error_found = 0;
    parser_state.token_index = 0;
    advance_token();
}

/**
 * Cleanup parser resources
 */
void parser_destroy(void) {
    if (yyin) {
        fclose(yyin);
    }
}

/**
 * Move to next token from lexer
 */
void advance_token(void) {
    parser_state.current_token = yylex();
    // Store the current token value in parser state
    // Note: yylval is set by the lexer
}

/**
 * Report parser error with line number
 */
void parser_error(const char* message) {
    fprintf(stderr, "Parser Error at line %d: %s\n", parser_state.line_number, message);
    parser_state.error_found = 1;
    errorFound = 1;
}

/**
 * Match expected token, advance if found
 * Returns 1 on success, 0 on failure
 */
static int match(int expected_token) {
    if (current_token_type() == expected_token) {
        advance_token();
        return 1;
    }
    return 0;
}

/**
 * Expect token, error if not found
 * Returns 1 on success, 0 on failure
 */
static int expect(int expected_token, const char* error_msg) {
    if (!match(expected_token)) {
        parser_error(error_msg);
        return 0;
    }
    return 1;
}

/* ============================================================
 * Grammar Production Rules (Recursive Descent Parser)
 * ============================================================ */

/**
 * program: statement
 *        | statement program
 */
int parse_program(void) {
    printf("[Program Start]\n");
    
    while (current_token_type() != TOKEN_EOF) {
        if (!parse_statement()) {
            // Try to recover by skipping to next statement
            if (current_token_type() != TOKEN_EOF) {
                advance_token();
            }
        }
    }
    
    printf("[Program End]\n");
    return !parser_state.error_found;
}

/**
 * statement: create | add | sort | print | if | for | output
 *          | define_function | assign | comment | call
 */
int parse_statement(void) {
    switch (current_token_type()) {
        case TOKEN_CREATECOURSE:
            printf("Statement -> create\n");
            return parse_create();
        case TOKEN_ADDCOURSE:
            printf("Statement -> add\n");
            return parse_add();
        case TOKEN_SORTCOURSE:
            printf("Statement -> sort\n");
            return parse_sort();
        case TOKEN_PRINTCOURSE:
            printf("Statement -> print\n");
            return parse_print();
        case TOKEN_IF:
            printf("Statement -> if\n");
            return parse_if();
        case TOKEN_FOR:
            printf("Statement -> for\n");
            return parse_for();
        case TOKEN_OUTPUT:
            printf("Statement -> output\n");
            return parse_output();
        case TOKEN_DEF:
            printf("Statement -> define_function\n");
            return parse_define_function();
        case TOKEN_IDENTIFIER:
            printf("Statement -> assign or call or add/sort/print\n");
            // Save current position to potentially backtrack
            // Try to determine which rule this is by looking ahead
            // For now, try to parse as add/sort/print/assign
            return parse_id_statement();
        case TOKEN_COMMENT:
            printf("Statement -> comment\n");
            return parse_comment();
        case TOKEN_CALL:
            printf("Statement -> call\n");
            return parse_call();
        default:
            parser_error("Unexpected token in statement");
            return 0;
    }
}

/**
 * parse_id_statement: Handle id-based statements (add, sort, print, assign)
 * These can be:
 * - add: id ADDCOURSE (...)
 * - sort: id SORTCOURSE order
 * - print: id PRINTCOURSE
 * - assign: id = expression
 */
int parse_id_statement(void) {
    if (!parse_id()) return 0;
    
    // Now check what comes after the id
    switch (current_token_type()) {
        case TOKEN_ADDCOURSE:
            printf("  -> add operation\n");
            if (!expect(TOKEN_ADDCOURSE, "Expected 'add'")) return 0;
            if (!expect(TOKEN_OPENROUNDEDPARANTHESIS, "Expected '('")) return 0;
            if (!parse_grades()) return 0;
            if (!expect(TOKEN_CLOSEROUNDEDPARANTHESIS, "Expected ')'")) return 0;
            printf("Add -> id ADDCOURSE (grades)\n");
            return 1;
            
        case TOKEN_SORTCOURSE:
            printf("  -> sort operation\n");
            if (!expect(TOKEN_SORTCOURSE, "Expected 'sort'")) return 0;
            char* order_val = NULL;
            if (!parse_order(&order_val)) return 0;
            printf("Sort -> id SORTCOURSE order\n");
            return 1;
            
        case TOKEN_PRINTCOURSE:
            printf("  -> print operation\n");
            if (!expect(TOKEN_PRINTCOURSE, "Expected 'print'")) return 0;
            printf("Print -> id PRINTCOURSE\n");
            return 1;
            
        case TOKEN_EQUAL:
            printf("  -> assignment\n");
            if (!expect(TOKEN_EQUAL, "Expected '='")) return 0;
            if (!parse_expression()) return 0;
            printf("Assign -> id = expression\n");
            return 1;
            
        default:
            parser_error("Expected '=', 'add', 'sort', or 'print' after identifier");
            return 0;
    }
}

/**
 * create: CREATECOURSE id
 *       | CREATECOURSE id EQUAL OPENSQUAREDPARANTHESIS grades CLOSESQUAREDPARANTHESIS
 */
int parse_create(void) {
    if (!expect(TOKEN_CREATECOURSE, "Expected 'create_course'")) return 0;
    
    if (!parse_id()) return 0;
    
    if (current_token_type() == TOKEN_EQUAL) {
        advance_token();
        if (!expect(TOKEN_OPENSQUAREDPARANTHESIS, "Expected '['")) return 0;
        if (!parse_grades()) return 0;
        if (!expect(TOKEN_CLOSESQUAREDPARANTHESIS, "Expected ']'")) return 0;
        printf("Create -> CREATECOURSE id = [grades]\n");
    } else {
        printf("Create -> CREATECOURSE id\n");
    }
    
    return 1;
}

/**
 * add: id ADDCOURSE OPENROUNDEDPARANTHESIS grades CLOSEROUNDEDPARANTHESIS
 */
int parse_add(void) {
    if (!parse_id()) return 0;
    if (!expect(TOKEN_ADDCOURSE, "Expected 'add'")) return 0;
    if (!expect(TOKEN_OPENROUNDEDPARANTHESIS, "Expected '('")) return 0;
    if (!parse_grades()) return 0;
    if (!expect(TOKEN_CLOSEROUNDEDPARANTHESIS, "Expected ')'")) return 0;
    
    printf("Add -> id ADDCOURSE (grades)\n");
    return 1;
}

/**
 * sort: id SORTCOURSE order
 */
int parse_sort(void) {
    if (!parse_id()) return 0;
    if (!expect(TOKEN_SORTCOURSE, "Expected 'sort'")) return 0;
    
    char* order_val = NULL;
    if (!parse_order(&order_val)) return 0;
    
    printf("Sort -> id SORTCOURSE order\n");
    return 1;
}

/**
 * print: id PRINTCOURSE
 */
int parse_print(void) {
    if (!parse_id()) return 0;
    if (!expect(TOKEN_PRINTCOURSE, "Expected 'print'")) return 0;
    
    printf("Print -> id PRINTCOURSE\n");
    return 1;
}

/**
 * if: IF condition statements elif else END
 */
int parse_if(void) {
    if (!expect(TOKEN_IF, "Expected 'if'")) return 0;
    if (!parse_condition()) return 0;
    if (!parse_statements()) return 0;
    
    while (current_token_type() == TOKEN_ELIF) {
        if (!parse_elif()) return 0;
    }
    
    if (current_token_type() == TOKEN_ELSE) {
        if (!parse_else()) return 0;
    }
    
    if (!expect(TOKEN_END, "Expected 'end'")) return 0;
    
    printf("If -> IF condition statements [elif] [else] END\n");
    return 1;
}

/**
 * elif: ELIF condition statements elif
 */
int parse_elif(void) {
    if (!expect(TOKEN_ELIF, "Expected 'elif'")) return 0;
    if (!parse_condition()) return 0;
    if (!parse_statements()) return 0;
    
    if (current_token_type() == TOKEN_ELIF) {
        if (!parse_elif()) return 0;
    }
    
    printf("Elif -> ELIF condition statements [elif]\n");
    return 1;
}

/**
 * else: ELSE statements
 */
int parse_else(void) {
    if (!expect(TOKEN_ELSE, "Expected 'else'")) return 0;
    if (!parse_statements()) return 0;
    
    printf("Else -> ELSE statements\n");
    return 1;
}

/**
 * for: FOR variable IN id statements END
 */
int parse_for(void) {
    if (!expect(TOKEN_FOR, "Expected 'for'")) return 0;
    if (!parse_variable()) return 0;
    if (!expect(TOKEN_IN, "Expected 'in'")) return 0;
    if (!parse_id()) return 0;
    if (!parse_statements()) return 0;
    if (!expect(TOKEN_END, "Expected 'end'")) return 0;
    
    printf("For -> FOR variable IN id statements END\n");
    return 1;
}

/**
 * statements: statement | statement statements
 */
int parse_statements(void) {
    while (current_token_type() != TOKEN_EOF &&
           current_token_type() != TOKEN_END &&
           current_token_type() != TOKEN_ELIF &&
           current_token_type() != TOKEN_ELSE) {
        
        if (!parse_statement()) return 0;
    }
    
    return 1;
}

/**
 * condition: expression
 */
int parse_condition(void) {
    return parse_expression();
}

/**
 * expression: variable
 *           | expression compare_operator expression
 *           | expression logical_operator expression
 *           | function ( args )
 *           | bool
 *           | value
 */
int parse_expression(void) {
    int left_parsed = 0;
    
    // Parse primary expression
    switch (current_token_type()) {
        case TOKEN_IDENTIFIER:
            left_parsed = parse_variable();
            break;
        case TOKEN_BOOLEAN:
            left_parsed = parse_bool();
            break;
        case TOKEN_GRADE:
            left_parsed = parse_value();
            break;
        case TOKEN_LENGTH:
        case TOKEN_SUM:
        case TOKEN_FINALGRADE:
        case TOKEN_POSSIBLEGRADE:
            left_parsed = parse_function();
            break;
        default:
            parser_error("Expected expression");
            return 0;
    }
    
    if (!left_parsed) return 0;
    
    // Handle operators
    while (1) {
        if (current_token_type() >= TOKEN_DOUBLEEQUAL && 
            current_token_type() <= TOKEN_GREATEROREQUALOPERATOR) {
            // Comparison operator
            if (!parse_compare_operator()) return 0;
            if (!parse_expression()) return 0;
        } else if (current_token_type() == TOKEN_AND || 
                   current_token_type() == TOKEN_OR) {
            // Logical operator
            if (!parse_logical_operator()) return 0;
            if (!parse_expression()) return 0;
        } else {
            break;
        }
    }
    
    return 1;
}

/**
 * grades: value | value COMMA grades
 */
int parse_grades(void) {
    if (!parse_value()) return 0;
    
    while (current_token_type() == TOKEN_COMMA) {
        advance_token();
        if (!parse_value()) return 0;
    }
    
    return 1;
}

/**
 * id: identifier
 */
int parse_id(void) {
    return parse_identifier();
}

/**
 * identifier: IDENTIFIER
 */
int parse_identifier(void) {
    if (current_token_type() != 300) {  // TOKEN_IDENTIFIER = 300
        parser_error("Expected identifier");
        return 0;
    }
    
    // Access the identifier from lexer's yylval
    if (yylval.str) {
        printf("  identifier: %s\n", yylval.str);
    }
    advance_token();
    return 1;
}

/**
 * variable: identifier
 */
int parse_variable(void) {
    return parse_identifier();
}

/**
 * args: id | id COMMA args
 */
int parse_args(void) {
    if (!parse_id()) return 0;
    
    while (current_token_type() == TOKEN_COMMA) {
        advance_token();
        if (!parse_id()) return 0;
    }
    
    return 1;
}

/**
 * value: GRADE
 */
int parse_value(void) {
    if (current_token_type() != 299) {  // TOKEN_GRADE = 299
        parser_error("Expected numeric value");
        return 0;
    }
    
    printf("  value: %d\n", yylval.num);
    advance_token();
    return 1;
}

/**
 * compare_operator: == | != | < | <= | > | >=
 */
int parse_compare_operator(void) {
    switch (current_token_type()) {
        case TOKEN_DOUBLEEQUAL:
        case TOKEN_DIFFERENTOPERATOR:
        case TOKEN_LESSOPERATOR:
        case TOKEN_LESSOREQUALOPERATOR:
        case TOKEN_GREATEROPERATOR:
        case TOKEN_GREATEROREQUALOPERATOR:
            advance_token();
            return 1;
        default:
            parser_error("Expected comparison operator");
            return 0;
    }
}

/**
 * logical_operator: AND | OR
 */
int parse_logical_operator(void) {
    if (current_token_type() == TOKEN_AND || current_token_type() == TOKEN_OR) {
        advance_token();
        return 1;
    }
    
    parser_error("Expected logical operator");
    return 0;
}

/**
 * order: ASC | DESC
 */
int parse_order(char** result) {
    if (current_token_type() == TOKEN_ASC) {
        *result = "ASC";
        advance_token();
        return 1;
    } else if (current_token_type() == TOKEN_DESC) {
        *result = "DESC";
        advance_token();
        return 1;
    }
    
    parser_error("Expected 'asc' or 'desc'");
    return 0;
}

/**
 * function: LENGTH | SUM | FINALGRADE | POSSIBLEGRADE | identifier
 */
int parse_function(void) {
    switch (current_token_type()) {
        case TOKEN_LENGTH:
        case TOKEN_SUM:
        case TOKEN_FINALGRADE:
        case TOKEN_POSSIBLEGRADE:
            advance_token();
            if (!expect(TOKEN_OPENROUNDEDPARANTHESIS, "Expected '('")) return 0;
            if (!parse_args()) return 0;
            if (!expect(TOKEN_CLOSEROUNDEDPARANTHESIS, "Expected ')'")) return 0;
            return 1;
        case TOKEN_IDENTIFIER:
            return parse_identifier();
        default:
            parser_error("Expected function name");
            return 0;
    }
}

/**
 * bool: BOOLEAN
 */
int parse_bool(void) {
    if (current_token_type() != 302) {  // TOKEN_BOOLEAN = 302
        parser_error("Expected boolean value");
        return 0;
    }
    
    printf("  bool: %s\n", yylval.boolean ? "true" : "false");
    advance_token();
    return 1;
}

/**
 * output: OUTPUT STRING | OUTPUT id
 */
int parse_output(void) {
    if (!expect(TOKEN_OUTPUT, "Expected 'output'")) return 0;
    
    if (current_token_type() == 301) {  // TOKEN_STRING = 301
        advance_token();
    } else if (current_token_type() == 300) {  // TOKEN_IDENTIFIER = 300
        if (!parse_id()) return 0;
    } else {
        parser_error("Expected string or identifier after 'output'");
        return 0;
    }
    
    printf("Output -> OUTPUT (string|id)\n");
    return 1;
}

/**
 * define_function: DEF id ( args ) statements END
 */
int parse_define_function(void) {
    if (!expect(TOKEN_DEF, "Expected 'def'")) return 0;
    if (!parse_id()) return 0;
    if (!expect(TOKEN_OPENROUNDEDPARANTHESIS, "Expected '('")) return 0;
    
    if (current_token_type() != TOKEN_CLOSEROUNDEDPARANTHESIS) {
        if (!parse_args()) return 0;
    }
    
    if (!expect(TOKEN_CLOSEROUNDEDPARANTHESIS, "Expected ')'")) return 0;
    if (!parse_statements()) return 0;
    if (!expect(TOKEN_END, "Expected 'end'")) return 0;
    
    printf("DefineFunction -> DEF id ( args ) statements END\n");
    return 1;
}

/**
 * assign: id EQUAL expression
 */
int parse_assign(void) {
    if (!parse_id()) return 0;
    if (!expect(TOKEN_EQUAL, "Expected '='")) return 0;
    if (!parse_expression()) return 0;
    
    printf("Assign -> id = expression\n");
    return 1;
}

/**
 * comment: COMMENT
 */
int parse_comment(void) {
    if (!expect(TOKEN_COMMENT, "Expected comment")) return 0;
    
    printf("Comment -> COMMENT\n");
    return 1;
}

/**
 * call: CALL id ( args )
 */
int parse_call(void) {
    if (!expect(TOKEN_CALL, "Expected 'call'")) return 0;
    if (!parse_id()) return 0;
    if (!expect(TOKEN_OPENROUNDEDPARANTHESIS, "Expected '('")) return 0;
    
    if (current_token_type() != TOKEN_CLOSEROUNDEDPARANTHESIS) {
        if (!parse_args()) return 0;
    }
    
    if (!expect(TOKEN_CLOSEROUNDEDPARANTHESIS, "Expected ')'")) return 0;
    
    printf("Call -> CALL id ( args )\n");
    return 1;
}
