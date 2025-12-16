#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/* ==========================================
 * OPTIMIZED HASH TABLE (SYMBOL TABLE)
 * ========================================== */
#define ST_SIZE 1024 // Power of 2 for bitwise masking optimization
#define BUFFER_SIZE 256

typedef struct Node {
    char token[BUFFER_SIZE];
    struct Node* next;
} Node;

Node* symbolTable[ST_SIZE];

// DJB2 Hash function - standard for fast string hashing
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % ST_SIZE;
}

void addToSymbolTable(char* token) {
    unsigned long h = hash(token);
    Node* current = symbolTable[h];
    
    // Check if exists
    while (current != NULL) {
        if (strcmp(current->token, token) == 0) return; // Already exists
        current = current->next;
    }

    // Insert new
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) { fprintf(stderr, "Memory allocation error\n"); exit(1); }
    strcpy(newNode->token, token);
    newNode->next = symbolTable[h];
    symbolTable[h] = newNode;
}

/* ==========================================
 * PARSER / LEXER LOGIC
 * ========================================== */

// Global file pointer for stream reading
FILE *fp;
char peekChar = 0;
int lineNum = 1;

// Efficient lookahead
char nextChar() {
    if (peekChar != 0) {
        char c = peekChar;
        peekChar = 0;
        return c;
    }
    return fgetc(fp);
}

void retract(char c) {
    peekChar = c;
}

/* * MICROSOFT OPTIMIZATION NOTE:
 * Instead of a generic DFA, we hardcode the grammar rules:
 * S->tA, A->rC, C->uD, D->e  (true)
 * S->fB, B->aE, E->lF, F->sD (false)
 */

void parseBoolean(char first) {
    char buf[6]; 
    int idx = 0;
    buf[idx++] = first;

    if (first == 't') {
        // Expecting r -> u -> e
        char c = nextChar();
        if (c == 'r') {
            buf[idx++] = c;
            c = nextChar();
            if (c == 'u') {
                buf[idx++] = c;
                c = nextChar();
                if (c == 'e') {
                    buf[idx++] = c;
                    buf[idx] = '\0';
                    // Lookahead to ensure it's not "trueValue" (ID)
                    char next = nextChar();
                    if (!isalnum(next) && next != '_') {
                        printf("BOOLEAN: true\n");
                        retract(next);
                        return;
                    }
                    buf[idx++] = next; // It was an identifier starting with true
                } else { buf[idx++] = c; }
            } else { buf[idx++] = c; }
        } else { buf[idx++] = c; }
    } 
    else if (first == 'f') {
        // Expecting a -> l -> s -> e
        char c = nextChar();
        if (c == 'a') {
            buf[idx++] = c;
            c = nextChar();
            if (c == 'l') {
                buf[idx++] = c;
                c = nextChar();
                if (c == 's') {
                    buf[idx++] = c;
                    c = nextChar();
                    if (c == 'e') {
                        buf[idx++] = c;
                        buf[idx] = '\0';
                        char next = nextChar();
                        if (!isalnum(next) && next != '_') {
                            printf("BOOLEAN: false\n");
                            retract(next);
                            return;
                        }
                        buf[idx++] = next;
                    } else { buf[idx++] = c; }
                } else { buf[idx++] = c; }
            } else { buf[idx++] = c; }
        } else { buf[idx++] = c; }
    }

    // If we fell through, it's an ID, continue reading rest of ID
    char c = nextChar();
    while (isalnum(c) || c == '_') {
        if (idx < BUFFER_SIZE - 1) buf[idx++] = c;
        c = nextChar();
    }
    buf[idx] = '\0';
    retract(c);
    addToSymbolTable(buf);
    printf("IDENTIFIER: %s\n", buf);
}

void parseString() {
    char buf[BUFFER_SIZE];
    int idx = 0;
    // We already consumed the opening "
    
    char c = nextChar();
    while (c != '"' && c != EOF) {
        if (idx < BUFFER_SIZE - 1) buf[idx++] = c;
        c = nextChar();
    }
    buf[idx] = '\0';
    
    if (c == EOF) {
        printf("ERROR: Unterminated string at line %d\n", lineNum);
        return;
    }
    
    printf("STRING: \"%s\"\n", buf);
}

void parseNumber(char first) {
    char buf[BUFFER_SIZE];
    int idx = 0;
    buf[idx++] = first;
    
    char c = nextChar();
    while (isdigit(c)) {
        if (idx < BUFFER_SIZE - 1) buf[idx++] = c;
        c = nextChar();
    }
    buf[idx] = '\0';
    retract(c);
    
    addToSymbolTable(buf); // Numbers often added to ST or Constant Table
    printf("NUMBER: %s\n", buf);
}

void parseIdentifier(char first) {
    char buf[BUFFER_SIZE];
    int idx = 0;
    buf[idx++] = first;
    
    char c = nextChar();
    while (isalnum(c) || c == '_') {
        if (idx < BUFFER_SIZE - 1) buf[idx++] = c;
        c = nextChar();
    }
    buf[idx] = '\0';
    retract(c);
    
    addToSymbolTable(buf);
    printf("IDENTIFIER: %s\n", buf);
}

void scan() {
    char c = nextChar();
    
    while (c != EOF) {
        if (isspace(c)) {
            if (c == '\n') lineNum++;
            // Skip whitespace
            c = nextChar();
            continue;
        }

        // Logic routing based on grammar start symbols
        if (c == 't' || c == 'f') {
            parseBoolean(c);
        }
        else if (isdigit(c)) {
            parseNumber(c);
        }
        else if (c == '"') {
            parseString();
        }
        else if (isalpha(c) || c == '_') {
            parseIdentifier(c);
        }
        else {
            // Handle symbols or errors
            printf("SYMBOL: %c\n", c);
        }

        c = nextChar();
    }
}

/* ==========================================
 * MAIN
 * ========================================== */
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    // Initialize Hash Table
    for(int i=0; i<ST_SIZE; i++) symbolTable[i] = NULL;

    printf("--- Starting Optimized Analysis ---\n");
    scan();
    printf("--- End of Analysis ---\n");
    
    // Optional: Print Symbol Table
    // printf("\n--- Symbol Table ---\n");
    // for(int i=0; i<ST_SIZE; i++) {
    //     Node* tmp = symbolTable[i];
    //     while(tmp) { printf("%s\n", tmp->token); tmp = tmp->next; }
    // }

    fclose(fp);
    return 0;
}