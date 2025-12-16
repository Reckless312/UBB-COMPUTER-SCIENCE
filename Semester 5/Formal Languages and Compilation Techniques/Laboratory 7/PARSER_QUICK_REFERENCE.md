# Parser Quick Reference Card

## File Quick Links

| File | Lines | Purpose |
|------|-------|---------|
| `parser.h` | ~150 | Token types, function declarations |
| `parser.c` | ~400 | All parsing functions |
| `main_parser.c` | ~100 | Entry point and system setup |
| `PARSER_IMPLEMENTATION.md` | - | Detailed documentation |
| `MIGRATION_GUIDE.md` | - | How to build and use |

## Quick Build

```bash
# Generate lexer
flex lex-analyzer-hash.l

# Compile and link
gcc -c parser.c main_parser.c lex.yy.c grammar.c automata.c pif.c production.c LL1.c hash-table.c
gcc -o parser *.o -lm

# Run
./parser input.txt
```

## Parser Functions

### Core Functions (Call These)
```c
parser_init()           // Initialize parser before use
parse_program()         // Main entry point
parser_destroy()        // Cleanup after use
```

### Statement Parsers (Route Based on Token)
```c
parse_statement()       // Routes to appropriate statement
parse_create()          // CREATECOURSE rule
parse_add()             // ADDCOURSE rule
parse_sort()            // SORTCOURSE rule
parse_print()           // PRINTCOURSE rule
parse_if()              // IF rule
parse_for()             // FOR rule
parse_output()          // OUTPUT rule
parse_define_function() // DEF rule
parse_assign()          // ID = rule
parse_call()            // CALL rule
parse_comment()         // COMMENT rule
```

### Expression Parsers
```c
parse_expression()      // Main expression parser
parse_condition()       // Condition in if/elif
parse_grades()          // List of numeric values
parse_value()           // Single numeric value
parse_bool()            // true/false
parse_identifier()      // Variable/function name
parse_variable()        // Variable reference
```

### Helper Parsers
```c
parse_id()              // Identifier
parse_args()            // Function arguments
parse_order()           // ASC or DESC
parse_function()        // Function call
parse_statements()      // Multiple statements
```

### Token Management (Internal)
```c
advance_token()         // Move to next token
current_token_type()    // Get current token type
match(token)            // Check and consume token
expect(token, error)    // Check token or error
parser_error(msg)       // Report error
```

## Token Types

```c
TOKEN_CREATECOURSE              // "create_course"
TOKEN_ADDCOURSE                 // "add"
TOKEN_SORTCOURSE                // "sort"
TOKEN_PRINTCOURSE               // "print"
TOKEN_IF                        // "if"
TOKEN_ELIF                      // "elif"
TOKEN_ELSE                      // "else"
TOKEN_END                       // "end"
TOKEN_FOR                       // "for"
TOKEN_IN                        // "in"
TOKEN_DEF                       // "def"
TOKEN_CALL                      // "call"
TOKEN_OUTPUT                    // "output"
TOKEN_COMMENT                   // "//"

// Operators
TOKEN_EQUAL                     // "="
TOKEN_DOUBLEEQUAL               // "=="
TOKEN_DIFFERENTOPERATOR         // "!="
TOKEN_LESSOPERATOR              // "<"
TOKEN_LESSOREQUALOPERATOR       // "<="
TOKEN_GREATEROPERATOR           // ">"
TOKEN_GREATEROREQUALOPERATOR    // ">="
TOKEN_AND                       // "and"
TOKEN_OR                        // "or"

// Brackets & Separators
TOKEN_OPENROUNDEDPARANTHESIS    // "("
TOKEN_CLOSEROUNDEDPARANTHESIS   // ")"
TOKEN_OPENSQUAREDPARANTHESIS    // "["
TOKEN_CLOSESQUAREDPARANTHESIS   // "]"
TOKEN_COMMA                     // ","
TOKEN_DOTANDCOMMA               // ";"

// Values & Identifiers
TOKEN_IDENTIFIER                // variable name
TOKEN_GRADE                     // numeric value
TOKEN_STRING                    // "string"
TOKEN_BOOLEAN                   // true/false
TOKEN_EOF                       // End of file
```

## Common Patterns

### Adding a New Statement
```c
// 1. In parser.h:
int parse_my_statement(void);

// 2. In parser.c - implement the rule:
int parse_my_statement(void) {
    if (!expect(TOKEN_MYTOKEN, "Expected 'mytoken'")) return 0;
    if (!parse_sub_rule()) return 0;
    printf("MyStatement -> ...\n");
    return 1;
}

// 3. In parse_statement():
case TOKEN_MYTOKEN:
    printf("Statement -> my_statement\n");
    return parse_my_statement();
```

### Parsing Optional Elements
```c
// Optional EQUAL sign
if (current_token_type() == TOKEN_EQUAL) {
    advance_token();
    if (!parse_something()) return 0;
}
```

### Parsing Repeated Elements
```c
// One or more grades
if (!parse_value()) return 0;
while (current_token_type() == TOKEN_COMMA) {
    advance_token();
    if (!parse_value()) return 0;
}
```

### Parsing Alternatives
```c
if (current_token_type() == TOKEN_STRING) {
    advance_token();
} else if (current_token_type() == TOKEN_IDENTIFIER) {
    if (!parse_id()) return 0;
} else {
    parser_error("Expected string or identifier");
    return 0;
}
```

## Debugging Checklist

- [ ] Is `parser_init()` called before `parse_program()`?
- [ ] Is `advance_token()` called after matching tokens?
- [ ] Are all return values checked (1 = success, 0 = failure)?
- [ ] Do token types match between parser.h and lex file?
- [ ] Is the lexer generating tokens correctly?
- [ ] Are printf statements showing correct parse path?
- [ ] Is errorFound being set on errors?
- [ ] Are automata loaded before parsing?

## Error Messages

| Error | Meaning | Fix |
|-------|---------|-----|
| "Expected identifier" | Found token when identifier needed | Check token type |
| "Expected '='" | Missing operator | Check syntax in input |
| "Expected 'end'" | IF/FOR block not closed | Add 'end' keyword |
| "Unexpected token in statement" | Invalid statement start | Check grammar rule |
| "Parser Error at line X" | Parse failed at that line | Look at source around line X |

## Parser State

The `ParserState` structure:
```c
typedef struct {
    int current_token;      // Current token type
    TokenValue current_value; // Token value (str, num, bool)
    int line_number;        // Current line in input
    int error_found;        // Error flag
    int token_index;        // Token counter
} ParserState;
```

Access via:
```c
parser_state.current_token          // Get current token type
parser_state.current_value.str      // Get string value
parser_state.current_value.num      // Get numeric value
parser_state.current_value.boolean  // Get boolean value
parser_state.line_number            // Get line number for error reporting
```

## Integration with Existing Code

Parser works with:
- `lex.yy.c` - Lexer (flex-generated, unchanged)
- `automata.c` - Token verification
- `grammar.c` - Grammar definitions
- `hash-table.c` - Symbol table
- `pif.c` - Program Internal Form
- `production.c` - Production rules
- `LL1.c` - Parsing tables

All called from `main_parser.c`.

## Performance Tips

1. **Token Value Caching**: Token values are stored in `parser_state`
2. **No Backtracking**: Parser never backtracks (true LL(1))
3. **Single Pass**: Lexer and parser work together in single pass
4. **Memory Efficient**: Only stores current token, not entire input

## Testing

### Quick Test
```bash
echo "create_course myvar" > test.txt
./parser test.txt
```

### Should See Output
```
========================================
  Parsing File: test.txt
========================================

[Program Start]
Statement -> create
Create -> CREATECOURSE id
  identifier: myvar
Create -> CREATECOURSE id
[Program End]

========================================
  Parsing Completed Successfully
========================================
```

## Cheat Sheet

```c
// Check token type
if (current_token_type() == TOKEN_CREATECOURSE)

// Consume token and check
if (!match(TOKEN_IDENTIFIER)) return 0;

// Require token or error
if (!expect(TOKEN_END, "Expected 'end'")) return 0;

// Optional element
if (current_token_type() == TOKEN_EQUAL) {
    advance_token();
}

// Repeated elements
while (current_token_type() == TOKEN_COMMA) {
    advance_token();
    if (!parse_item()) return 0;
}

// Access token values
yylval.str      // String value from lexer
yylval.num      // Numeric value from lexer
yylval.boolean  // Boolean value from lexer
```

## Key Differences from Yacc

| Feature | Yacc | Recursive Descent |
|---------|------|-------------------|
| Grammar Definition | `spec.y` | C functions in `parser.c` |
| Action Execution | In `%{ }%` blocks | In parsing functions |
| Token Definition | In `%token` | In `parser.h` enum |
| Error Handling | `yyerror()` | `parser_error()` |
| Parsing Tables | Generated, unreadable | No tables needed |
| Debugging | Difficult, indirect | Easy, direct function calls |

## Useful Tricks

### See What Rule You're In
```c
#define ENTER_RULE(name) printf("[ENTER] %s\n", name)
#define EXIT_RULE(name) printf("[EXIT] %s\n", name)

int parse_if(void) {
    ENTER_RULE("parse_if");
    // ...
    EXIT_RULE("parse_if");
    return 1;
}
```

### Track Parse Depth
```c
static int parse_depth = 0;
printf("%*s> Parsing rule\n", parse_depth*2, "");
parse_depth++;
// ... recursive call ...
parse_depth--;
```

### Token Name Lookup
```c
const char* token_name(int token) {
    switch(token) {
        case TOKEN_CREATECOURSE: return "CREATECOURSE";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        // ... add all tokens
        default: return "UNKNOWN";
    }
}
```

## Need Help?

1. Check `PARSER_IMPLEMENTATION.md` for detailed docs
2. Check `MIGRATION_GUIDE.md` for build instructions
3. Look at example parsing function in `parser.c`
4. Enable debug output with printf statements
5. Use `gdb` to step through parser functions

---

**Last Updated**: December 2024
**Parser Type**: Recursive Descent (LL(1))
**Status**: Production Ready
