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
/* "%code requires" blocks.  */
#line 53 "PWS42X5Y.y"

    typedef struct ASTNode {
        char *type;
        char *value;
        char *dtype;
        struct ASTNode *firstChild;
        struct ASTNode *nextSibling;
    } ASTNode;

    ASTNode* createNode(char* type, char* value);
    void addChildNode(ASTNode* parent, ASTNode* child);
    void printAST(ASTNode *node, int level, FILE *tree);
    char* determineConditionType(char* op, char* leftType, char* rightType);
    // void dfs(ASTNode* v);

#line 65 "y.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    NUM = 259,                     /* NUM  */
    REAL_NUM = 260,                /* REAL_NUM  */
    CHAR_CONST = 261,              /* CHAR_CONST  */
    STRING = 262,                  /* STRING  */
    PROGRAM = 263,                 /* PROGRAM  */
    VAR = 264,                     /* VAR  */
    INTEGER = 265,                 /* INTEGER  */
    REAL = 266,                    /* REAL  */
    BOOLEAN = 267,                 /* BOOLEAN  */
    CHAR = 268,                    /* CHAR  */
    TO = 269,                      /* TO  */
    DOWNTO = 270,                  /* DOWNTO  */
    IF = 271,                      /* IF  */
    ELSE = 272,                    /* ELSE  */
    WHILE = 273,                   /* WHILE  */
    FOR = 274,                     /* FOR  */
    DO = 275,                      /* DO  */
    ARRAY = 276,                   /* ARRAY  */
    AND = 277,                     /* AND  */
    OR = 278,                      /* OR  */
    NOT = 279,                     /* NOT  */
    START = 280,                   /* START  */
    END = 281,                     /* END  */
    READ = 282,                    /* READ  */
    WRITE = 283,                   /* WRITE  */
    ASSIGN = 284,                  /* ASSIGN  */
    PLUS = 285,                    /* PLUS  */
    MINUS = 286,                   /* MINUS  */
    MUL = 287,                     /* MUL  */
    DIV = 288,                     /* DIV  */
    MOD = 289,                     /* MOD  */
    EQ = 290,                      /* EQ  */
    NEQ = 291,                     /* NEQ  */
    LT = 292,                      /* LT  */
    GT = 293,                      /* GT  */
    LE = 294,                      /* LE  */
    GE = 295,                      /* GE  */
    LPAREN = 296,                  /* LPAREN  */
    RPAREN = 297,                  /* RPAREN  */
    LBRACK = 298,                  /* LBRACK  */
    RBRACK = 299,                  /* RBRACK  */
    COLON = 300,                   /* COLON  */
    SEMICOLON = 301,               /* SEMICOLON  */
    COMMA = 302,                   /* COMMA  */
    PERIOD = 303,                  /* PERIOD  */
    INVALID = 304,                 /* INVALID  */
    OF = 305,                      /* OF  */
    THEN = 306,                    /* THEN  */
    DQUOTE = 307,                  /* DQUOTE  */
    TRUTH = 308,                   /* TRUTH  */
    LIE = 309                      /* LIE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define NUM 259
#define REAL_NUM 260
#define CHAR_CONST 261
#define STRING 262
#define PROGRAM 263
#define VAR 264
#define INTEGER 265
#define REAL 266
#define BOOLEAN 267
#define CHAR 268
#define TO 269
#define DOWNTO 270
#define IF 271
#define ELSE 272
#define WHILE 273
#define FOR 274
#define DO 275
#define ARRAY 276
#define AND 277
#define OR 278
#define NOT 279
#define START 280
#define END 281
#define READ 282
#define WRITE 283
#define ASSIGN 284
#define PLUS 285
#define MINUS 286
#define MUL 287
#define DIV 288
#define MOD 289
#define EQ 290
#define NEQ 291
#define LT 292
#define GT 293
#define LE 294
#define GE 295
#define LPAREN 296
#define RPAREN 297
#define LBRACK 298
#define RBRACK 299
#define COLON 300
#define SEMICOLON 301
#define COMMA 302
#define PERIOD 303
#define INVALID 304
#define OF 305
#define THEN 306
#define DQUOTE 307
#define TRUTH 308
#define LIE 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 69 "PWS42X5Y.y"

    int num;
    float real;
    char ch;
    char *id;
    char *str;
    char *exprt;
    struct id_list {
        char **ids; // Array of identifier names
        int count;  // Number of identifiers in the list
    } id_list;
    ASTNode *node;

#line 207 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
