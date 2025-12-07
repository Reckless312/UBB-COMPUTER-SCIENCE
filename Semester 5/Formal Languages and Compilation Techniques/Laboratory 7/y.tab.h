/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

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
#line 30 "spec.y"
int num; char* str; bool boolean; 

#line 164 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
