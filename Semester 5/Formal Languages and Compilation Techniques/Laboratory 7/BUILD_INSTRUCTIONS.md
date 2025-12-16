# Example Makefile for Custom Parser

## Makefile for Building the Custom Recursive Descent Parser

```makefile
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -O2
LDFLAGS = -lm

# Flex lexer generator
LEX = flex

# Target executable
TARGET = parser

# Source files
SOURCES = parser.c main_parser.c lex.yy.c grammar.c automata.c pif.c \
          production.c LL1.c hash-table.c
HEADERS = parser.h grammar.h automata.h pif.h production.h LL1.h hash-table.h

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Build executable
$(TARGET): $(OBJECTS)
	@echo "Linking $@..."
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build successful: $(TARGET)"

# Generate lexer from flex grammar
lex.yy.c: lex-analyzer-hash.l $(HEADERS)
	@echo "Generating lexer from lex-analyzer-hash.l..."
	$(LEX) lex-analyzer-hash.l

# Compile C source files
%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Run parser on test file
run: $(TARGET)
	./$(TARGET) simple_program.txt

# Run parser on more complex test
run-complex: $(TARGET)
	./$(TARGET) not_so_simple_program.txt

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -f $(OBJECTS) $(TARGET) lex.yy.c
	@echo "Clean complete"

# Remove everything and rebuild
rebuild: clean all

# Show help
help:
	@echo "Recursive Descent Parser - Makefile Targets"
	@echo "==========================================="
	@echo "make              - Build the parser"
	@echo "make run          - Build and run on simple_program.txt"
	@echo "make run-complex  - Build and run on not_so_simple_program.txt"
	@echo "make rebuild      - Clean and rebuild everything"
	@echo "make clean        - Remove build artifacts"
	@echo "make help         - Show this help message"

# Phony targets (not real files)
.PHONY: all run run-complex clean rebuild help

```

Save this as `Makefile` in your project directory.

## Usage

### Build Parser
```bash
make
```

### Run on Test File
```bash
make run
```

### Rebuild Everything
```bash
make rebuild
```

### Clean
```bash
make clean
```

## Advanced Makefile with Debug Target

```makefile
# Advanced Makefile with multiple configurations

CC = gcc
CFLAGS_BASE = -Wall -Wextra -g
CFLAGS_DEBUG = $(CFLAGS_BASE) -DDEBUG -O0
CFLAGS_RELEASE = $(CFLAGS_BASE) -O2
LDFLAGS = -lm

LEX = flex

TARGET = parser
TARGET_DEBUG = parser-debug

SOURCES = parser.c main_parser.c lex.yy.c grammar.c automata.c pif.c \
          production.c LL1.c hash-table.c
HEADERS = parser.h grammar.h automata.h pif.h production.h LL1.h hash-table.h

OBJECTS = $(SOURCES:.c=.o)
OBJECTS_DEBUG = $(SOURCES:.c=.debug.o)

# Default - release build
all: $(TARGET)

# Debug build with extra output
debug: CFLAGS = $(CFLAGS_DEBUG)
debug: $(TARGET_DEBUG)

# Release build
$(TARGET): CFLAGS = $(CFLAGS_RELEASE)
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Release build complete: $(TARGET)"

# Debug build
$(TARGET_DEBUG): $(OBJECTS_DEBUG)
	$(CC) $(OBJECTS_DEBUG) -o $(TARGET_DEBUG) $(LDFLAGS)
	@echo "Debug build complete: $(TARGET_DEBUG)"

# Generate lexer
lex.yy.c: lex-analyzer-hash.l $(HEADERS)
	$(LEX) lex-analyzer-hash.l

# Compile release objects
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS_RELEASE) -c $< -o $@

# Compile debug objects
%.debug.o: %.c $(HEADERS)
	$(CC) $(CFLAGS_DEBUG) -c $< -o $@

# Run release version
run: $(TARGET)
	./$(TARGET) simple_program.txt

# Run debug version with gdb
run-debug: $(TARGET_DEBUG)
	gdb ./$(TARGET_DEBUG)

# Run with valgrind for memory checking
check-memory: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all \
	         ./$(TARGET) simple_program.txt

# Generate documentation
docs:
	@echo "Parser Documentation:"
	@echo "  - PARSER_IMPLEMENTATION.md - Detailed documentation"
	@echo "  - MIGRATION_GUIDE.md - How to build and use"
	@echo "  - PARSER_QUICK_REFERENCE.md - Quick reference"

clean:
	rm -f $(OBJECTS) $(OBJECTS_DEBUG) $(TARGET) $(TARGET_DEBUG) lex.yy.c

rebuild: clean all

.PHONY: all debug run run-debug check-memory docs clean rebuild

```

## Using Custom Makefile

### Basic Setup
1. Save as `Makefile` in project directory
2. Run `make` to build
3. Run `make run` to test

### With Configuration Files
Create `config.mk` for customization:

```makefile
# config.mk - Parser Configuration

# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g -O2

# Input files
TEST_SIMPLE = simple_program.txt
TEST_COMPLEX = not_so_simple_program.txt

# Flex settings
LEX = flex
LEX_FLAGS = 

# Project directories
OBJ_DIR = build
BIN_DIR = bin

```

Then include it in main `Makefile`:

```makefile
include config.mk

# ... rest of Makefile
```

## Integration with Existing Build System

### If You Have a Larger Project

```bash
# Project structure
project/
├── src/
│   ├── parser.c
│   ├── main_parser.c
│   ├── lex-analyzer-hash.l
│   ├── grammar.c
│   └── ... other sources
├── include/
│   ├── parser.h
│   ├── grammar.h
│   └── ... other headers
├── test/
│   ├── simple_program.txt
│   └── not_so_simple_program.txt
├── build/
│   └── (generated object files)
└── Makefile
```

Corresponding Makefile:

```makefile
SRCDIR = src
INCDIR = include
OBJDIR = build
BINDIR = .

SOURCES = $(SRCDIR)/parser.c $(SRCDIR)/main_parser.c $(SRCDIR)/lex.yy.c \
          $(SRCDIR)/grammar.c $(SRCDIR)/automata.c $(SRCDIR)/pif.c \
          $(SRCDIR)/production.c $(SRCDIR)/LL1.c $(SRCDIR)/hash-table.c

HEADERS = $(INCDIR)/parser.h $(INCDIR)/grammar.h $(INCDIR)/automata.h \
          $(INCDIR)/pif.h $(INCDIR)/production.h $(INCDIR)/LL1.h \
          $(INCDIR)/hash-table.h

OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.c=.o)))

CC = gcc
CFLAGS = -I$(INCDIR) -Wall -Wextra -g -O2
LDFLAGS = -lm

TARGET = parser

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $(BINDIR)/$(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCDIR)/lex.yy.c: $(SRCDIR)/lex-analyzer-hash.l
	flex -o $@ $<

clean:
	rm -rf $(OBJDIR) $(BINDIR)/$(TARGET)

.PHONY: all clean
```

## One-Line Build Command

If you don't want to use Makefile:

```bash
# Quick compile without Makefile
gcc -c parser.c main_parser.c grammar.c automata.c pif.c production.c LL1.c hash-table.c && \
flex lex-analyzer-hash.l && \
gcc -c lex.yy.c && \
gcc -o parser *.o -lm && \
./parser simple_program.txt
```

## CMake Alternative

If your project uses CMake:

```cmake
# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)
project(CustomParser)

# C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# Find Flex
find_package(FLEX REQUIRED)

# Generate lexer
flex_target(Scanner
    lex-analyzer-hash.l
    ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c
    COMPILE_FLAGS ""
)

# Add executable
add_executable(parser
    parser.c
    main_parser.c
    ${FLEX_Scanner_OUTPUTS}
    grammar.c
    automata.c
    pif.c
    production.c
    LL1.c
    hash-table.c
)

# Include directories
target_include_directories(parser PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link libraries
target_link_libraries(parser m)

# Add test targets
add_test(NAME SimpleTest COMMAND parser simple_program.txt)
add_test(NAME ComplexTest COMMAND parser not_so_simple_program.txt)
```

Build with CMake:
```bash
mkdir build
cd build
cmake ..
make
./parser ../simple_program.txt
```

## Visual Studio / MSVC Setup

For Windows development:

```batch
@echo off
REM build.bat - Windows build script

echo Generating lexer...
flex -o lex.yy.c lex-analyzer-hash.l

echo Compiling...
cl /W4 /Zi /I. parser.c main_parser.c lex.yy.c grammar.c automata.c ^
   pif.c production.c LL1.c hash-table.c /link /OUT:parser.exe

echo Build complete: parser.exe
parser.exe simple_program.txt
```

## Summary

Choose the build system that fits your workflow:

- **Simple Project**: Use basic Makefile (first example)
- **Medium Project**: Use advanced Makefile with debug targets
- **Large Project**: Use CMake or organized Makefile with directories
- **Quick Testing**: Use one-line command
- **Windows Development**: Use batch script

All approaches compile the same parser code - just different automation!
