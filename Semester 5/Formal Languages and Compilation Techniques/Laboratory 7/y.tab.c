/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "spec.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include "grammar.h"
    #include "automata.h"
    #include "pif.h"
    #include "production.h"
    #include "LL1.h"

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

#line 104 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    CREATECOURSE = 258,            /* CREATECOURSE  */
    ADDCOURSE = 259,               /* ADDCOURSE  */
    SORTCOURSE = 260,              /* SORTCOURSE  */
    PRINTCOURSE = 261,             /* PRINTCOURSE  */
    IF = 262,                      /* IF  */
    END = 263,                     /* END  */
    ELIF = 264,                    /* ELIF  */
    ELSE = 265,                    /* ELSE  */
    FOR = 266,                     /* FOR  */
    IN = 267,                      /* IN  */
    COMMA = 268,                   /* COMMA  */
    DOUBLEEQUAL = 269,             /* DOUBLEEQUAL  */
    DIFFERENTOPERATOR = 270,       /* DIFFERENTOPERATOR  */
    LESSOPERATOR = 271,            /* LESSOPERATOR  */
    LESSOREQUALOPERATOR = 272,     /* LESSOREQUALOPERATOR  */
    GREATEROPERATOR = 273,         /* GREATEROPERATOR  */
    GREATEROREQUALOPERATOR = 274,  /* GREATEROREQUALOPERATOR  */
    EXCLAMATION = 275,             /* EXCLAMATION  */
    UPPERCOMMA = 276,              /* UPPERCOMMA  */
    DOT = 277,                     /* DOT  */
    DOTANDCOMMA = 278,             /* DOTANDCOMMA  */
    SLASH = 279,                   /* SLASH  */
    DASH = 280,                    /* DASH  */
    OPENROUNDEDPARANTHESIS = 281,  /* OPENROUNDEDPARANTHESIS  */
    CLOSEROUNDEDPARANTHESIS = 282, /* CLOSEROUNDEDPARANTHESIS  */
    UNDERLINE = 283,               /* UNDERLINE  */
    EQUAL = 284,                   /* EQUAL  */
    OPENSQUAREDPARANTHESIS = 285,  /* OPENSQUAREDPARANTHESIS  */
    CLOSESQUAREDPARANTHESIS = 286, /* CLOSESQUAREDPARANTHESIS  */
    AND = 287,                     /* AND  */
    OR = 288,                      /* OR  */
    ASC = 289,                     /* ASC  */
    DESC = 290,                    /* DESC  */
    LENGTH = 291,                  /* LENGTH  */
    SUM = 292,                     /* SUM  */
    FINALGRADE = 293,              /* FINALGRADE  */
    POSSIBLEGRADE = 294,           /* POSSIBLEGRADE  */
    OUTPUT = 295,                  /* OUTPUT  */
    DEF = 296,                     /* DEF  */
    COMMENT = 297,                 /* COMMENT  */
    CALL = 298,                    /* CALL  */
    GRADE = 299,                   /* GRADE  */
    IDENTIFIER = 300,              /* IDENTIFIER  */
    STRING = 301,                  /* STRING  */
    BOOLEAN = 302                  /* BOOLEAN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define CREATECOURSE 258
#define ADDCOURSE 259
#define SORTCOURSE 260
#define PRINTCOURSE 261
#define IF 262
#define END 263
#define ELIF 264
#define ELSE 265
#define FOR 266
#define IN 267
#define COMMA 268
#define DOUBLEEQUAL 269
#define DIFFERENTOPERATOR 270
#define LESSOPERATOR 271
#define LESSOREQUALOPERATOR 272
#define GREATEROPERATOR 273
#define GREATEROREQUALOPERATOR 274
#define EXCLAMATION 275
#define UPPERCOMMA 276
#define DOT 277
#define DOTANDCOMMA 278
#define SLASH 279
#define DASH 280
#define OPENROUNDEDPARANTHESIS 281
#define CLOSEROUNDEDPARANTHESIS 282
#define UNDERLINE 283
#define EQUAL 284
#define OPENSQUAREDPARANTHESIS 285
#define CLOSESQUAREDPARANTHESIS 286
#define AND 287
#define OR 288
#define ASC 289
#define DESC 290
#define LENGTH 291
#define SUM 292
#define FINALGRADE 293
#define POSSIBLEGRADE 294
#define OUTPUT 295
#define DEF 296
#define COMMENT 297
#define CALL 298
#define GRADE 299
#define IDENTIFIER 300
#define STRING 301
#define BOOLEAN 302

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 34 "spec.y"
int num; char* str; bool boolean; 

#line 254 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CREATECOURSE = 3,               /* CREATECOURSE  */
  YYSYMBOL_ADDCOURSE = 4,                  /* ADDCOURSE  */
  YYSYMBOL_SORTCOURSE = 5,                 /* SORTCOURSE  */
  YYSYMBOL_PRINTCOURSE = 6,                /* PRINTCOURSE  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_END = 8,                        /* END  */
  YYSYMBOL_ELIF = 9,                       /* ELIF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_IN = 12,                        /* IN  */
  YYSYMBOL_COMMA = 13,                     /* COMMA  */
  YYSYMBOL_DOUBLEEQUAL = 14,               /* DOUBLEEQUAL  */
  YYSYMBOL_DIFFERENTOPERATOR = 15,         /* DIFFERENTOPERATOR  */
  YYSYMBOL_LESSOPERATOR = 16,              /* LESSOPERATOR  */
  YYSYMBOL_LESSOREQUALOPERATOR = 17,       /* LESSOREQUALOPERATOR  */
  YYSYMBOL_GREATEROPERATOR = 18,           /* GREATEROPERATOR  */
  YYSYMBOL_GREATEROREQUALOPERATOR = 19,    /* GREATEROREQUALOPERATOR  */
  YYSYMBOL_EXCLAMATION = 20,               /* EXCLAMATION  */
  YYSYMBOL_UPPERCOMMA = 21,                /* UPPERCOMMA  */
  YYSYMBOL_DOT = 22,                       /* DOT  */
  YYSYMBOL_DOTANDCOMMA = 23,               /* DOTANDCOMMA  */
  YYSYMBOL_SLASH = 24,                     /* SLASH  */
  YYSYMBOL_DASH = 25,                      /* DASH  */
  YYSYMBOL_OPENROUNDEDPARANTHESIS = 26,    /* OPENROUNDEDPARANTHESIS  */
  YYSYMBOL_CLOSEROUNDEDPARANTHESIS = 27,   /* CLOSEROUNDEDPARANTHESIS  */
  YYSYMBOL_UNDERLINE = 28,                 /* UNDERLINE  */
  YYSYMBOL_EQUAL = 29,                     /* EQUAL  */
  YYSYMBOL_OPENSQUAREDPARANTHESIS = 30,    /* OPENSQUAREDPARANTHESIS  */
  YYSYMBOL_CLOSESQUAREDPARANTHESIS = 31,   /* CLOSESQUAREDPARANTHESIS  */
  YYSYMBOL_AND = 32,                       /* AND  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_ASC = 34,                       /* ASC  */
  YYSYMBOL_DESC = 35,                      /* DESC  */
  YYSYMBOL_LENGTH = 36,                    /* LENGTH  */
  YYSYMBOL_SUM = 37,                       /* SUM  */
  YYSYMBOL_FINALGRADE = 38,                /* FINALGRADE  */
  YYSYMBOL_POSSIBLEGRADE = 39,             /* POSSIBLEGRADE  */
  YYSYMBOL_OUTPUT = 40,                    /* OUTPUT  */
  YYSYMBOL_DEF = 41,                       /* DEF  */
  YYSYMBOL_COMMENT = 42,                   /* COMMENT  */
  YYSYMBOL_CALL = 43,                      /* CALL  */
  YYSYMBOL_GRADE = 44,                     /* GRADE  */
  YYSYMBOL_IDENTIFIER = 45,                /* IDENTIFIER  */
  YYSYMBOL_STRING = 46,                    /* STRING  */
  YYSYMBOL_BOOLEAN = 47,                   /* BOOLEAN  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_program = 49,                   /* program  */
  YYSYMBOL_statement = 50,                 /* statement  */
  YYSYMBOL_create = 51,                    /* create  */
  YYSYMBOL_add = 52,                       /* add  */
  YYSYMBOL_sort = 53,                      /* sort  */
  YYSYMBOL_print = 54,                     /* print  */
  YYSYMBOL_if = 55,                        /* if  */
  YYSYMBOL_elif = 56,                      /* elif  */
  YYSYMBOL_else = 57,                      /* else  */
  YYSYMBOL_for = 58,                       /* for  */
  YYSYMBOL_statements = 59,                /* statements  */
  YYSYMBOL_condition = 60,                 /* condition  */
  YYSYMBOL_expression = 61,                /* expression  */
  YYSYMBOL_grades = 62,                    /* grades  */
  YYSYMBOL_id = 63,                        /* id  */
  YYSYMBOL_args = 64,                      /* args  */
  YYSYMBOL_variable = 65,                  /* variable  */
  YYSYMBOL_identifier = 66,                /* identifier  */
  YYSYMBOL_compare_operator = 67,          /* compare_operator  */
  YYSYMBOL_logical_operator = 68,          /* logical_operator  */
  YYSYMBOL_order = 69,                     /* order  */
  YYSYMBOL_value = 70,                     /* value  */
  YYSYMBOL_function = 71,                  /* function  */
  YYSYMBOL_bool = 72,                      /* bool  */
  YYSYMBOL_output = 73,                    /* output  */
  YYSYMBOL_define_function = 74,           /* define_function  */
  YYSYMBOL_assign = 75,                    /* assign  */
  YYSYMBOL_comment = 76,                   /* comment  */
  YYSYMBOL_call = 77                       /* call  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  44
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   91

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  106

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    56,    56,    57,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    75,    76,    80,    84,    88,
      92,    96,    97,   101,   102,   106,   110,   111,   115,   119,
     120,   121,   122,   123,   124,   128,   129,   133,   137,   138,
     142,   146,   150,   151,   152,   153,   154,   155,   159,   160,
     164,   165,   169,   173,   174,   175,   176,   177,   181,   185,
     186,   190,   194,   198,   201
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CREATECOURSE",
  "ADDCOURSE", "SORTCOURSE", "PRINTCOURSE", "IF", "END", "ELIF", "ELSE",
  "FOR", "IN", "COMMA", "DOUBLEEQUAL", "DIFFERENTOPERATOR", "LESSOPERATOR",
  "LESSOREQUALOPERATOR", "GREATEROPERATOR", "GREATEROREQUALOPERATOR",
  "EXCLAMATION", "UPPERCOMMA", "DOT", "DOTANDCOMMA", "SLASH", "DASH",
  "OPENROUNDEDPARANTHESIS", "CLOSEROUNDEDPARANTHESIS", "UNDERLINE",
  "EQUAL", "OPENSQUAREDPARANTHESIS", "CLOSESQUAREDPARANTHESIS", "AND",
  "OR", "ASC", "DESC", "LENGTH", "SUM", "FINALGRADE", "POSSIBLEGRADE",
  "OUTPUT", "DEF", "COMMENT", "CALL", "GRADE", "IDENTIFIER", "STRING",
  "BOOLEAN", "$accept", "program", "statement", "create", "add", "sort",
  "print", "if", "elif", "else", "for", "statements", "condition",
  "expression", "grades", "id", "args", "variable", "identifier",
  "compare_operator", "logical_operator", "order", "value", "function",
  "bool", "output", "define_function", "assign", "comment", "call", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-71)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-58)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,   -27,    33,   -27,   -29,   -27,   -71,   -27,   -71,    20,
      -2,   -71,   -71,   -71,   -71,   -71,   -71,     6,   -71,   -71,
     -71,   -71,   -71,   -71,    19,   -71,   -71,   -71,   -71,   -71,
     -71,    -2,    14,   -71,     8,   -71,    23,   -71,    40,   -71,
     -71,   -71,    27,    29,   -71,   -71,    31,    -8,   -71,    33,
      28,    -2,    50,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,    33,    33,   -27,   -27,   -27,   -27,    16,   -71,   -71,
     -71,    14,    16,   -71,    33,    51,    14,    14,    55,    46,
      -2,    47,    48,    49,    68,    52,    -2,    -2,    74,   -27,
     -71,    76,    -2,   -71,   -71,    16,   -71,    50,   -71,   -71,
     -71,   -71,    77,   -71,   -71,   -71
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    63,     0,    41,     0,
       2,     4,     5,     6,     7,     8,     9,     0,    37,    10,
      11,    12,    13,    14,    15,    53,    54,    55,    56,    52,
      58,     0,    28,    29,    40,    34,     0,    33,     0,    40,
      59,    60,     0,     0,     1,     3,     0,     0,    19,     0,
       0,    26,    21,    42,    43,    44,    45,    46,    47,    48,
      49,     0,     0,     0,     0,     0,     0,     0,    50,    51,
      18,    62,     0,    27,     0,    23,    30,    31,    38,     0,
       0,     0,     0,     0,    35,     0,     0,     0,     0,     0,
      32,     0,     0,    64,    17,     0,    16,    21,    24,    20,
      39,    25,     0,    36,    22,    61
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -71,    79,    13,   -71,   -71,   -71,   -71,   -71,   -11,   -71,
     -71,   -36,    17,   -25,   -70,    -1,   -44,    84,     5,   -71,
     -71,   -71,   -53,   -71,   -71,   -71,   -71,   -71,   -71,   -71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     9,    51,    11,    12,    13,    14,    15,    75,    88,
      16,    52,    31,    32,    83,    17,    79,    33,    18,    61,
      62,    70,    35,    36,    37,    19,    20,    21,    22,    23
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      24,     1,    85,    41,    42,     2,    43,    34,    39,     3,
      46,    47,    48,    10,    84,    73,     8,    40,     8,    84,
      44,    81,    82,    10,    71,   103,    68,    69,    53,    54,
      55,    56,    57,    58,   -57,    49,    76,    77,     4,     5,
       6,     7,    84,     8,    91,   100,    59,    60,    50,    63,
      97,    98,    64,    65,    34,    66,   102,    67,    72,    74,
      29,    87,    78,    80,    78,    78,    34,    34,    89,    25,
      26,    27,    28,    90,    92,    93,    94,    29,     8,    34,
      30,    95,    99,    96,   101,   105,   104,    38,    78,    45,
       0,    86
};

static const yytype_int8 yycheck[] =
{
       1,     3,    72,     4,     5,     7,     7,     2,     3,    11,
       4,     5,     6,     0,    67,    51,    45,    46,    45,    72,
       0,    65,    66,    10,    49,    95,    34,    35,    14,    15,
      16,    17,    18,    19,    26,    29,    61,    62,    40,    41,
      42,    43,    95,    45,    80,    89,    32,    33,    29,    26,
      86,    87,    12,    26,    49,    26,    92,    26,    30,     9,
      44,    10,    63,    64,    65,    66,    61,    62,    13,    36,
      37,    38,    39,    27,    27,    27,    27,    44,    45,    74,
      47,    13,     8,    31,     8,     8,    97,     3,    89,    10,
      -1,    74
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     7,    11,    40,    41,    42,    43,    45,    49,
      50,    51,    52,    53,    54,    55,    58,    63,    66,    73,
      74,    75,    76,    77,    63,    36,    37,    38,    39,    44,
      47,    60,    61,    65,    66,    70,    71,    72,    65,    66,
      46,    63,    63,    63,     0,    49,     4,     5,     6,    29,
      29,    50,    59,    14,    15,    16,    17,    18,    19,    32,
      33,    67,    68,    26,    12,    26,    26,    26,    34,    35,
      69,    61,    30,    59,     9,    56,    61,    61,    63,    64,
      63,    64,    64,    62,    70,    62,    60,    10,    57,    13,
      27,    59,    27,    27,    27,    13,    31,    59,    59,     8,
      64,     8,    59,    62,    56,     8
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    49,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    51,    51,    52,    53,    54,
      55,    56,    56,    57,    57,    58,    59,    59,    60,    61,
      61,    61,    61,    61,    61,    62,    62,    63,    64,    64,
      65,    66,    67,    67,    67,    67,    67,    67,    68,    68,
      69,    69,    70,    71,    71,    71,    71,    71,    72,    73,
      73,    74,    75,    76,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     6,     5,     3,     2,
       6,     0,     4,     0,     2,     6,     1,     2,     1,     1,
       3,     3,     4,     1,     1,     1,     3,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     7,     3,     1,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statement  */
#line 56 "spec.y"
              { printf("Program -> statement\n"); }
#line 1383 "y.tab.c"
    break;

  case 3: /* program: statement program  */
#line 57 "spec.y"
                        { printf("Program -> statement, program\n"); }
#line 1389 "y.tab.c"
    break;

  case 4: /* statement: create  */
#line 61 "spec.y"
           { printf("Statement -> create\n"); }
#line 1395 "y.tab.c"
    break;

  case 5: /* statement: add  */
#line 62 "spec.y"
          { printf("Statement -> add\n"); }
#line 1401 "y.tab.c"
    break;

  case 6: /* statement: sort  */
#line 63 "spec.y"
           { printf("Statement -> sort\n"); }
#line 1407 "y.tab.c"
    break;

  case 7: /* statement: print  */
#line 64 "spec.y"
            { printf("Statement -> print\n"); }
#line 1413 "y.tab.c"
    break;

  case 8: /* statement: if  */
#line 65 "spec.y"
         { printf("Statement -> if\n"); }
#line 1419 "y.tab.c"
    break;

  case 9: /* statement: for  */
#line 66 "spec.y"
          { printf("Statement -> for\n"); }
#line 1425 "y.tab.c"
    break;

  case 10: /* statement: output  */
#line 67 "spec.y"
             { printf("Statement -> output\n"); }
#line 1431 "y.tab.c"
    break;

  case 11: /* statement: define_function  */
#line 68 "spec.y"
                      { printf("Statement -> define_function\n"); }
#line 1437 "y.tab.c"
    break;

  case 12: /* statement: assign  */
#line 69 "spec.y"
             { printf("Statement -> assign\n"); }
#line 1443 "y.tab.c"
    break;

  case 13: /* statement: comment  */
#line 70 "spec.y"
              { printf("Statement -> comment\n"); }
#line 1449 "y.tab.c"
    break;

  case 14: /* statement: call  */
#line 71 "spec.y"
           { printf("Statement -> call\n"); }
#line 1455 "y.tab.c"
    break;

  case 15: /* create: CREATECOURSE id  */
#line 75 "spec.y"
                    { printf("Create -> CREATECOURSE id\n"); }
#line 1461 "y.tab.c"
    break;

  case 16: /* create: CREATECOURSE id EQUAL OPENSQUAREDPARANTHESIS grades CLOSESQUAREDPARANTHESIS  */
#line 76 "spec.y"
                                                                                  { printf("Create -> CREATECOURSE id = [grades]"); }
#line 1467 "y.tab.c"
    break;

  case 17: /* add: id ADDCOURSE OPENROUNDEDPARANTHESIS grades CLOSEROUNDEDPARANTHESIS  */
#line 80 "spec.y"
                                                                       { printf("Add -> id ADDCOURSE [grades]\n"); }
#line 1473 "y.tab.c"
    break;

  case 18: /* sort: id SORTCOURSE order  */
#line 84 "spec.y"
                        { printf("Sort -> id SORTCOURSE order\n"); }
#line 1479 "y.tab.c"
    break;

  case 19: /* print: id PRINTCOURSE  */
#line 88 "spec.y"
                   { printf("Print -> id PRINTCOURSE\n"); }
#line 1485 "y.tab.c"
    break;

  case 20: /* if: IF condition statements elif else END  */
#line 92 "spec.y"
                                          { printf("If -> IF ... END\n"); }
#line 1491 "y.tab.c"
    break;

  case 21: /* elif: %empty  */
#line 96 "spec.y"
                  { }
#line 1497 "y.tab.c"
    break;

  case 22: /* elif: ELIF condition statements elif  */
#line 97 "spec.y"
                                     { printf("Elif -> ELIF ...\n"); }
#line 1503 "y.tab.c"
    break;

  case 23: /* else: %empty  */
#line 101 "spec.y"
                  { }
#line 1509 "y.tab.c"
    break;

  case 24: /* else: ELSE statements  */
#line 102 "spec.y"
                      { printf("Else -> ELSE ...\n"); }
#line 1515 "y.tab.c"
    break;

  case 25: /* for: FOR variable IN id statements END  */
#line 106 "spec.y"
                                      { printf("For -> FOR variable IN id ... END\n"); }
#line 1521 "y.tab.c"
    break;

  case 26: /* statements: statement  */
#line 110 "spec.y"
              { }
#line 1527 "y.tab.c"
    break;

  case 27: /* statements: statement statements  */
#line 111 "spec.y"
                           { }
#line 1533 "y.tab.c"
    break;

  case 28: /* condition: expression  */
#line 115 "spec.y"
               { }
#line 1539 "y.tab.c"
    break;

  case 29: /* expression: variable  */
#line 119 "spec.y"
             { }
#line 1545 "y.tab.c"
    break;

  case 30: /* expression: expression compare_operator expression  */
#line 120 "spec.y"
                                             { }
#line 1551 "y.tab.c"
    break;

  case 31: /* expression: expression logical_operator expression  */
#line 121 "spec.y"
                                             { }
#line 1557 "y.tab.c"
    break;

  case 32: /* expression: function OPENROUNDEDPARANTHESIS args CLOSEROUNDEDPARANTHESIS  */
#line 122 "spec.y"
                                                                   { }
#line 1563 "y.tab.c"
    break;

  case 33: /* expression: bool  */
#line 123 "spec.y"
           { }
#line 1569 "y.tab.c"
    break;

  case 34: /* expression: value  */
#line 124 "spec.y"
            { }
#line 1575 "y.tab.c"
    break;

  case 35: /* grades: value  */
#line 128 "spec.y"
          { }
#line 1581 "y.tab.c"
    break;

  case 36: /* grades: value COMMA grades  */
#line 129 "spec.y"
                         { }
#line 1587 "y.tab.c"
    break;

  case 37: /* id: identifier  */
#line 133 "spec.y"
               { }
#line 1593 "y.tab.c"
    break;

  case 38: /* args: id  */
#line 137 "spec.y"
       { }
#line 1599 "y.tab.c"
    break;

  case 39: /* args: id COMMA args  */
#line 138 "spec.y"
                    { }
#line 1605 "y.tab.c"
    break;

  case 40: /* variable: identifier  */
#line 142 "spec.y"
               { }
#line 1611 "y.tab.c"
    break;

  case 41: /* identifier: IDENTIFIER  */
#line 146 "spec.y"
               { }
#line 1617 "y.tab.c"
    break;

  case 50: /* order: ASC  */
#line 164 "spec.y"
        {(yyval.str) = "ASC";}
#line 1623 "y.tab.c"
    break;

  case 51: /* order: DESC  */
#line 165 "spec.y"
           {(yyval.str) = "DESC";}
#line 1629 "y.tab.c"
    break;

  case 52: /* value: GRADE  */
#line 169 "spec.y"
          { }
#line 1635 "y.tab.c"
    break;

  case 58: /* bool: BOOLEAN  */
#line 181 "spec.y"
            { }
#line 1641 "y.tab.c"
    break;

  case 63: /* comment: COMMENT  */
#line 198 "spec.y"
            { printf("comment -> Comment\n"); }
#line 1647 "y.tab.c"
    break;


#line 1651 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 203 "spec.y"


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

    InitializeProductionRules();
    //PrintProductions();

    FillFirst();
    FillFollow();
    FillParsingTable();
    //PrintParsingTable();

    FILE *fp;
    fp = fopen(argv[1], "r");
    yyin = fp;

    int token;

    while ((token = yylex()) != 0) {
        int* getToWord;
        if (token == BOOLEAN) {
            if (yylval.boolean == true) {
                printf("true: ");
                getToWord = ParseWord("true");
            }
            else {
                printf("false: ");
                getToWord = ParseWord("false");
            }
        }
        else if (token == IDENTIFIER) {
            printf("%s: ", yylval.str);
            getToWord = ParseWord(yylval.str);
        }
        else if (token == GRADE) {
            char str[100];
            sprintf(str, "%d", yylval.num);
            printf("%s: ", str);
            getToWord = ParseWord(str);
        }
        else if (token == STRING) {
            printf("%s: ", yylval.str);
            getToWord = ParseWord(yylval.str);
        }
        else {
            continue;
        }

        for (int i = 0; i < 512; i++) {
            if (getToWord[i] == -1) {
                break;
            }
            printf("%d, ", getToWord[i]);
        }
        printf("\n");
    }

    //yyparse();

    if (errorFound == 0) {
        //showSymbolTable(symbolTable);
        //showProgramInternalForm();
	}
    
    return 0;
}

void yyerror(char* s) {
    fprintf(stderr, "Error: %s\n", s);
}
