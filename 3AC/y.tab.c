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
#line 2 "yacc.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define YYDEBUG 1
int yylex();
extern FILE* yyin;
extern int yylineno;
int mainExists = 0;

static FILE* codeFile;
static int currentTemp = 0;

enum Operator {
    OP_PLUS = 1093,
    OP_MINUS,
    OP_MUL,
    OP_DIV,
    OP_ASSIGN,
    OP_EQ,
    OP_LT,
    OP_LTE,
    OP_GT,
    OP_GTE,
    OP_OR,
    OP_AND,
    OP_MOD,
    OP_NEQ,
    OP_NEG,
    OP_NOT,
    OP_IF,
    OP_GOTO,
    OP_NOP,
    OP_ASSIGN_ADDR,
    OP_ASSIGN_PTR,
    OP_PTR_ASSIGN,
    OP_LABEL

};

enum TempVarType {
    UK_VAR_TYPE = 1903,
    INT_VAR_TYPE,
    INT_CONST_TYPE,
    FLOAT_VAR_TYPE,
    FLOAT_CONST_TYPE,
    CHAR_VAR_TYPE,
    CHAR_CONST_TYPE,
    STRING_CONST_TYPE,
    
};

struct TempVar {
    char* name;
    enum TempVarType type;
};

static struct TempVar tempVarStack[100];
static int nVars = 0;

struct Quadruple {
    enum Operator op;
    char* arg1;
    char* arg2;
    char* result;
};

static struct Quadruple* intermediateCode[100];
static int nCode = 0;

void pushToTempStack(char* var, enum TempVarType type)
{
    struct TempVar* tVar = (struct TempVar*)malloc(sizeof(struct TempVar));
    tVar->name = strdup(var);
    tVar->type = type;
    tempVarStack[nVars] = *tVar;
    nVars++;
}

struct TempVar popFromTempStack()
{
    return tempVarStack[--nVars];
}

char* NewTempVar()
{
    char* var = (char *)malloc(3*sizeof(char));
    sprintf(var, "t%d", currentTemp);
    currentTemp++;
    return var;
}

char* NewLabel(int temp1) {
    char* label = (char*)malloc(10);
    sprintf(label, "%d", temp1);
    return label;
}

void AddCode(enum Operator op, char* arg1, char* arg2, char* result)
{
	if (op == OP_LABEL) {
        //printf("%s:\n", arg1);  // Print the label followed by a colon
        return;
    }
    struct Quadruple* quad = (struct Quadruple*)malloc(sizeof(struct Quadruple));
    quad->op = op;
    quad->arg1 = arg1;
    quad->arg2 = arg2;
    quad->result = result;
    intermediateCode[nCode] = quad;
    nCode++;
}

void AddCodeBefore(int n, enum Operator op, char* arg1, char* arg2, char* result)
{
    int start = nCode - n;
    for(int i = n - 1; i >= 0; i--)
    {
        intermediateCode[start + i + 1] = intermediateCode[start + i];
    }
    
    struct Quadruple* quad = (struct Quadruple*)malloc(sizeof(struct Quadruple));
    quad->op = op;
    quad->arg1 = arg1;
    quad->arg2 = arg2;
    quad->result = result;
    intermediateCode[start] = quad;
    nCode++;
}

void pushCodetoBottom(int index, int n, int nPush)
{
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < nPush; j++)
        {
            struct Quadrauple* t1 = intermediateCode[j+index];
            intermediateCode[j + index] = intermediateCode[j + index + 1];
            intermediateCode[j + index + 1] = t1;
        }
        index--;
    }
}


void RepeatStatementAt(int n, int statementIndex)
{
    int start = nCode - n;
    for(int i = n - 1; i >= 0; i--)
    {
        intermediateCode[start + i + 1] = intermediateCode[start + i];
    }

    struct Quadruple* quad = (struct Quadruple*)malloc(sizeof(struct Quadruple));
    quad->op = intermediateCode[statementIndex]->op;
    quad->arg1 = intermediateCode[statementIndex]->arg1;
    quad->arg2 = intermediateCode[statementIndex]->arg2;
    quad->result = intermediateCode[statementIndex]->result;
    intermediateCode[start] = quad;
    nCode++;
}

void PrintIntermediateCode()
{
    printf("Intermediate Code: \n");
    for(int i = 0; i < nCode; i++)
    {
        printf("%d:\t", i);
        switch (intermediateCode[i]->op)
        {
            case OP_PLUS:
                printf("%s = %s + %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_MINUS:
                printf("%s = %s - %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_MUL:
                printf("%s = %s * %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_DIV:
                printf("%s = %s / %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_ASSIGN:
                printf("%s = %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1);
                break;
            case OP_EQ:
                printf("%s = %s == %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_LT:
                printf("%s = %s < %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_LTE:
                printf("%s = %s <= %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_GT:
                printf("%s = %s > %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_GTE:
                printf("%s = %s >= %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_OR:
                printf("%s = %s || %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_AND:
                printf("%s = %s && %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_MOD:
                printf("%s = %s \% %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_NEQ:
                printf("%s = %s != %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1, intermediateCode[i]->arg2);
                break;
            case OP_NEG:
                printf("%s = -%s\n", intermediateCode[i]->result, intermediateCode[i]->arg1);
                break;
            case OP_NOT:
                printf("%s = !%s\n", intermediateCode[i]->result, intermediateCode[i]->arg1);
                break;
            case OP_IF: // arg1 = condition arg2 = goto offset
                printf("if %s goto %d\n", intermediateCode[i]->arg1, i + atoi(intermediateCode[i]->arg2));
                break;
            case OP_GOTO: // arg1 = goto offset
                printf("goto %d\n", i + atoi(intermediateCode[i]->arg1));
                break;
            case OP_NOP:
                printf("nop\n");
                break;
            case OP_ASSIGN_ADDR:
                printf("%s = &%s\n", intermediateCode[i]->result, intermediateCode[i]->arg1);
                break;
            case OP_ASSIGN_PTR:
                printf("%s = *%s\n", intermediateCode[i]->result, intermediateCode[i]->arg1);
                break;
            case OP_PTR_ASSIGN:
                printf("*%s = %s\n", intermediateCode[i]->result, intermediateCode[i]->arg1);
                break;
            
            default:
                printf("NONE\n");
                break;
        }
    }
}


#line 320 "y.tab.c"

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
    PROGRAM = 258,                 /* PROGRAM  */
    VAR = 259,                     /* VAR  */
    INTEGER = 260,                 /* INTEGER  */
    REAL = 261,                    /* REAL  */
    BOOLEAN = 262,                 /* BOOLEAN  */
    CHAR = 263,                    /* CHAR  */
    TO = 264,                      /* TO  */
    DOWNTO = 265,                  /* DOWNTO  */
    IF = 266,                      /* IF  */
    ELSE = 267,                    /* ELSE  */
    WHILE = 268,                   /* WHILE  */
    FOR = 269,                     /* FOR  */
    DO = 270,                      /* DO  */
    ARRAY = 271,                   /* ARRAY  */
    AND = 272,                     /* AND  */
    OR = 273,                      /* OR  */
    NOT = 274,                     /* NOT  */
    START = 275,                   /* START  */
    END = 276,                     /* END  */
    READ = 277,                    /* READ  */
    WRITE = 278,                   /* WRITE  */
    ASSIGN = 279,                  /* ASSIGN  */
    PLUS = 280,                    /* PLUS  */
    MINUS = 281,                   /* MINUS  */
    MUL = 282,                     /* MUL  */
    DIV = 283,                     /* DIV  */
    MOD = 284,                     /* MOD  */
    EQ = 285,                      /* EQ  */
    NEQ = 286,                     /* NEQ  */
    LT = 287,                      /* LT  */
    GT = 288,                      /* GT  */
    LE = 289,                      /* LE  */
    GE = 290,                      /* GE  */
    LPAREN = 291,                  /* LPAREN  */
    RPAREN = 292,                  /* RPAREN  */
    LBRACK = 293,                  /* LBRACK  */
    RBRACK = 294,                  /* RBRACK  */
    COLON = 295,                   /* COLON  */
    SEMICOLON = 296,               /* SEMICOLON  */
    COMMA = 297,                   /* COMMA  */
    PERIOD = 298,                  /* PERIOD  */
    INVALID = 299,                 /* INVALID  */
    OF = 300,                      /* OF  */
    THEN = 301,                    /* THEN  */
    DQUOTE = 302,                  /* DQUOTE  */
    STRING = 303,                  /* STRING  */
    TRUTH = 304,                   /* TRUTH  */
    LIE = 305,                     /* LIE  */
    ID = 306,                      /* ID  */
    NUM = 307,                     /* NUM  */
    REAL_NUM = 308,                /* REAL_NUM  */
    CHAR_CONST = 309               /* CHAR_CONST  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define PROGRAM 258
#define VAR 259
#define INTEGER 260
#define REAL 261
#define BOOLEAN 262
#define CHAR 263
#define TO 264
#define DOWNTO 265
#define IF 266
#define ELSE 267
#define WHILE 268
#define FOR 269
#define DO 270
#define ARRAY 271
#define AND 272
#define OR 273
#define NOT 274
#define START 275
#define END 276
#define READ 277
#define WRITE 278
#define ASSIGN 279
#define PLUS 280
#define MINUS 281
#define MUL 282
#define DIV 283
#define MOD 284
#define EQ 285
#define NEQ 286
#define LT 287
#define GT 288
#define LE 289
#define GE 290
#define LPAREN 291
#define RPAREN 292
#define LBRACK 293
#define RBRACK 294
#define COLON 295
#define SEMICOLON 296
#define COMMA 297
#define PERIOD 298
#define INVALID 299
#define OF 300
#define THEN 301
#define DQUOTE 302
#define STRING 303
#define TRUTH 304
#define LIE 305
#define ID 306
#define NUM 307
#define REAL_NUM 308
#define CHAR_CONST 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 253 "yacc.y"

    char* strval;
    int intval;
    struct idList {
        char* idArray[20];
        int size;
    } idList;

    enum DeclareType {
        INT_TYPE,
        FLOAT_TYPE,
        CHAR_TYPE
    }

#line 496 "y.tab.c"

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
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_INTEGER = 5,                    /* INTEGER  */
  YYSYMBOL_REAL = 6,                       /* REAL  */
  YYSYMBOL_BOOLEAN = 7,                    /* BOOLEAN  */
  YYSYMBOL_CHAR = 8,                       /* CHAR  */
  YYSYMBOL_TO = 9,                         /* TO  */
  YYSYMBOL_DOWNTO = 10,                    /* DOWNTO  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_DO = 15,                        /* DO  */
  YYSYMBOL_ARRAY = 16,                     /* ARRAY  */
  YYSYMBOL_AND = 17,                       /* AND  */
  YYSYMBOL_OR = 18,                        /* OR  */
  YYSYMBOL_NOT = 19,                       /* NOT  */
  YYSYMBOL_START = 20,                     /* START  */
  YYSYMBOL_END = 21,                       /* END  */
  YYSYMBOL_READ = 22,                      /* READ  */
  YYSYMBOL_WRITE = 23,                     /* WRITE  */
  YYSYMBOL_ASSIGN = 24,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 25,                      /* PLUS  */
  YYSYMBOL_MINUS = 26,                     /* MINUS  */
  YYSYMBOL_MUL = 27,                       /* MUL  */
  YYSYMBOL_DIV = 28,                       /* DIV  */
  YYSYMBOL_MOD = 29,                       /* MOD  */
  YYSYMBOL_EQ = 30,                        /* EQ  */
  YYSYMBOL_NEQ = 31,                       /* NEQ  */
  YYSYMBOL_LT = 32,                        /* LT  */
  YYSYMBOL_GT = 33,                        /* GT  */
  YYSYMBOL_LE = 34,                        /* LE  */
  YYSYMBOL_GE = 35,                        /* GE  */
  YYSYMBOL_LPAREN = 36,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 37,                    /* RPAREN  */
  YYSYMBOL_LBRACK = 38,                    /* LBRACK  */
  YYSYMBOL_RBRACK = 39,                    /* RBRACK  */
  YYSYMBOL_COLON = 40,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 41,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 42,                     /* COMMA  */
  YYSYMBOL_PERIOD = 43,                    /* PERIOD  */
  YYSYMBOL_INVALID = 44,                   /* INVALID  */
  YYSYMBOL_OF = 45,                        /* OF  */
  YYSYMBOL_THEN = 46,                      /* THEN  */
  YYSYMBOL_DQUOTE = 47,                    /* DQUOTE  */
  YYSYMBOL_STRING = 48,                    /* STRING  */
  YYSYMBOL_TRUTH = 49,                     /* TRUTH  */
  YYSYMBOL_LIE = 50,                       /* LIE  */
  YYSYMBOL_ID = 51,                        /* ID  */
  YYSYMBOL_NUM = 52,                       /* NUM  */
  YYSYMBOL_REAL_NUM = 53,                  /* REAL_NUM  */
  YYSYMBOL_CHAR_CONST = 54,                /* CHAR_CONST  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_program = 56,                   /* program  */
  YYSYMBOL_var_decl_section = 57,          /* var_decl_section  */
  YYSYMBOL_var_decl_list = 58,             /* var_decl_list  */
  YYSYMBOL_var_decl = 59,                  /* var_decl  */
  YYSYMBOL_ID_list = 60,                   /* ID_list  */
  YYSYMBOL_type = 61,                      /* type  */
  YYSYMBOL_begin_end = 62,                 /* begin_end  */
  YYSYMBOL_stmt_list = 63,                 /* stmt_list  */
  YYSYMBOL_stmt = 64,                      /* stmt  */
  YYSYMBOL_assign_stmt = 65,               /* assign_stmt  */
  YYSYMBOL_if_stmt = 66,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 67,                /* while_stmt  */
  YYSYMBOL_for_stmt = 68,                  /* for_stmt  */
  YYSYMBOL_read_stmt = 69,                 /* read_stmt  */
  YYSYMBOL_write_stmt = 70,                /* write_stmt  */
  YYSYMBOL_c_stmt_list = 71,               /* c_stmt_list  */
  YYSYMBOL_ifelse_stmt_list = 72,          /* ifelse_stmt_list  */
  YYSYMBOL_w_ID_list = 73,                 /* w_ID_list  */
  YYSYMBOL_expr = 74,                      /* expr  */
  YYSYMBOL_condn = 75                      /* condn  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   231

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   309


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   293,   293,   299,   299,   302,   302,   305,   309,   314,
     320,   324,   329,   330,   331,   332,   335,   338,   338,   341,
     342,   343,   344,   345,   346,   349,   357,   376,   388,   401,
     420,   446,   470,   470,   473,   473,   473,   476,   479,   482,
     482,   486,   495,   504,   513,   522,   531,   535,   539,   544,
     549,   553,   557,   577,   583,   593,   605,   615,   625,   635,
     645,   649,   659,   669,   677
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
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "VAR",
  "INTEGER", "REAL", "BOOLEAN", "CHAR", "TO", "DOWNTO", "IF", "ELSE",
  "WHILE", "FOR", "DO", "ARRAY", "AND", "OR", "NOT", "START", "END",
  "READ", "WRITE", "ASSIGN", "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQ",
  "NEQ", "LT", "GT", "LE", "GE", "LPAREN", "RPAREN", "LBRACK", "RBRACK",
  "COLON", "SEMICOLON", "COMMA", "PERIOD", "INVALID", "OF", "THEN",
  "DQUOTE", "STRING", "TRUTH", "LIE", "ID", "NUM", "REAL_NUM",
  "CHAR_CONST", "$accept", "program", "var_decl_section", "var_decl_list",
  "var_decl", "ID_list", "type", "begin_end", "stmt_list", "stmt",
  "assign_stmt", "if_stmt", "while_stmt", "for_stmt", "read_stmt",
  "write_stmt", "c_stmt_list", "ifelse_stmt_list", "w_ID_list", "expr",
  "condn", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-79)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,   -28,    55,    20,   -79,    63,    17,    49,    -3,    17,
     -79,    35,    -6,    34,   174,    67,   -79,   179,     0,     0,
      69,    85,    89,   -20,   105,    -6,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,    86,    99,   122,
     -79,   100,     0,     0,   -79,   -79,   138,   -79,   -79,   -79,
     166,    -8,   187,   153,   137,    48,    40,    40,   -79,   -79,
     151,   -79,   -79,   -79,   128,     4,    40,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    40,    40,     0,     0,
     169,   186,    40,   -26,    40,   170,    36,   171,   141,    31,
      83,   167,   -79,   -79,    88,    54,    54,   -79,   -79,   -79,
     118,   118,   118,   118,   118,   118,   -79,   192,    -6,   -79,
     199,    -6,   -79,    37,   172,    40,   146,   173,   161,   175,
     176,   -79,   191,   177,   -79,   197,   186,   198,    40,    40,
     -79,   103,   -79,   180,   -79,   -79,   -79,    40,   178,   182,
     -79,   182,   108,   123,   184,    78,   185,   -79,   186,   186,
     188,   -79,   181,   -79,   -79,   -79,   179,   190,   -79
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     4,     0,     0,     0,     3,
       5,     0,     0,     0,     0,     0,     6,     0,     0,     0,
       0,     0,     0,     0,     0,    18,    19,    20,    21,    22,
      23,    24,     2,    12,    13,    14,    15,     0,     0,    11,
      10,     0,     0,     0,    50,    51,    47,    46,    48,    49,
      64,     0,     0,     0,     0,     0,     0,     0,    16,    17,
       0,     7,     8,    63,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    47,     0,     0,     0,
       0,     0,    53,    60,     0,    41,    42,    43,    44,    45,
      54,    55,    56,    57,    58,    59,    61,    62,     0,    27,
       0,     0,    29,     0,     0,     0,     0,     0,     0,     0,
       0,    25,     0,     0,    52,     0,     0,     0,     0,     0,
      32,     0,    34,    40,    39,    36,    35,     0,     0,    38,
      28,     0,     0,     0,     0,     0,     0,    37,     0,     0,
       0,    26,     0,    30,    31,    33,     0,     0,     9
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   -79,   -79,   216,   212,   -17,   -79,   -23,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -78,   -79,   110,   -42,
       1
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     7,     9,    10,    11,    38,    13,    24,    25,
      26,    27,    28,    29,    30,    31,   109,   110,    87,    50,
      51
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    64,    59,   112,    56,    18,     1,    19,    20,    78,
      79,   114,   115,    88,    89,    90,    21,    22,    57,    42,
      52,    78,    79,     3,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,    43,    14,    80,    15,
     113,    93,   116,    63,    65,    23,   128,   129,   140,    44,
      45,    46,    47,    48,    49,     4,    67,    68,    69,    70,
      71,     5,    67,    68,    69,    70,    71,     6,     8,    12,
     153,   154,   121,   131,    66,    17,    84,    32,   118,   106,
     107,    69,    70,    71,    84,   125,   142,   143,   127,    44,
      45,    46,    47,    48,    49,   145,    85,    44,    45,    86,
      47,    48,    49,    67,    68,    69,    70,    71,    67,    68,
      69,    70,    71,    67,    68,    69,    70,    71,    39,   151,
      53,    54,   122,   148,    60,    55,    58,   124,    67,    68,
      69,    70,    71,    67,    68,    69,    70,    71,   149,   157,
      61,    62,   144,    67,    68,    69,    70,    71,    67,    68,
      69,    70,    71,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    15,    92,    67,    68,    69,    70,
      71,    67,    68,    69,    70,    71,    66,    82,   120,    33,
      34,    35,    36,    92,    33,    34,    35,    36,    83,   108,
      37,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    81,    91,    78,    79,   111,   117,   119,    78,
     123,   126,   133,   130,   132,   137,   135,   136,   139,   141,
     138,   150,   118,   147,   152,    16,   156,    40,   134,   155,
     146,   158
};

static const yytype_uint8 yycheck[] =
{
      17,    43,    25,    81,    24,    11,     3,    13,    14,    17,
      18,    37,    38,    55,    56,    57,    22,    23,    38,    19,
      19,    17,    18,    51,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    36,    40,    46,    42,
      82,    37,    84,    42,    43,    51,     9,    10,   126,    49,
      50,    51,    52,    53,    54,     0,    25,    26,    27,    28,
      29,    41,    25,    26,    27,    28,    29,     4,    51,    20,
     148,   149,    41,   115,    38,    40,    36,    43,    42,    78,
      79,    27,    28,    29,    36,   108,   128,   129,   111,    49,
      50,    51,    52,    53,    54,   137,    48,    49,    50,    51,
      52,    53,    54,    25,    26,    27,    28,    29,    25,    26,
      27,    28,    29,    25,    26,    27,    28,    29,    51,    41,
      51,    36,    39,    15,    38,    36,    21,    39,    25,    26,
      27,    28,    29,    25,    26,    27,    28,    29,    15,   156,
      41,    41,    39,    25,    26,    27,    28,    29,    25,    26,
      27,    28,    29,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    42,    37,    25,    26,    27,    28,
      29,    25,    26,    27,    28,    29,    38,    24,    37,     5,
       6,     7,     8,    37,     5,     6,     7,     8,    51,    20,
      16,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    15,    52,    17,    18,    20,    37,    37,    17,
      43,    12,    51,    41,    41,    24,    41,    41,    21,    21,
      43,    37,    42,    41,    39,     9,    45,    15,   118,    41,
      52,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    56,    51,     0,    41,     4,    57,    51,    58,
      59,    60,    20,    62,    40,    42,    59,    40,    11,    13,
      14,    22,    23,    51,    63,    64,    65,    66,    67,    68,
      69,    70,    43,     5,     6,     7,     8,    16,    61,    51,
      60,    61,    19,    36,    49,    50,    51,    52,    53,    54,
      74,    75,    75,    51,    36,    36,    24,    38,    21,    63,
      38,    41,    41,    75,    74,    75,    38,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    17,    18,
      46,    15,    24,    51,    36,    48,    51,    73,    74,    74,
      74,    52,    37,    37,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    74,    75,    75,    20,    71,
      72,    20,    71,    74,    37,    38,    74,    37,    42,    37,
      37,    41,    39,    43,    39,    63,    12,    63,     9,    10,
      41,    74,    41,    51,    73,    41,    41,    24,    43,    21,
      71,    21,    74,    74,    39,    74,    52,    41,    15,    15,
      37,    41,    39,    71,    71,    41,    45,    61,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    59,    59,    59,
      60,    60,    61,    61,    61,    61,    62,    63,    63,    64,
      64,    64,    64,    64,    64,    65,    65,    66,    66,    67,
      68,    68,    69,    69,    70,    70,    70,    71,    72,    73,
      73,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     2,     0,     1,     2,     4,     4,    12,
       3,     1,     1,     1,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     4,     7,     4,     6,     4,
       8,     8,     5,     8,     5,     5,     5,     4,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1
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
  case 2: /* program: PROGRAM ID SEMICOLON var_decl_section begin_end PERIOD  */
#line 293 "yacc.y"
                                                                { 

        return 0;
	}
#line 1667 "y.tab.c"
    break;

  case 7: /* var_decl: ID COLON type SEMICOLON  */
#line 306 "yacc.y"
        {
        
        }
#line 1675 "y.tab.c"
    break;

  case 8: /* var_decl: ID_list COLON type SEMICOLON  */
#line 310 "yacc.y"
        {
        	
        
        }
#line 1684 "y.tab.c"
    break;

  case 9: /* var_decl: ID COLON ARRAY LBRACK NUM PERIOD PERIOD NUM RBRACK OF type SEMICOLON  */
#line 315 "yacc.y"
        {
            
        }
#line 1692 "y.tab.c"
    break;

  case 10: /* ID_list: ID COMMA ID_list  */
#line 321 "yacc.y"
        {
      
        }
#line 1700 "y.tab.c"
    break;

  case 11: /* ID_list: ID  */
#line 325 "yacc.y"
        {
        }
#line 1707 "y.tab.c"
    break;

  case 12: /* type: INTEGER  */
#line 329 "yacc.y"
              {  }
#line 1713 "y.tab.c"
    break;

  case 13: /* type: REAL  */
#line 330 "yacc.y"
           {  }
#line 1719 "y.tab.c"
    break;

  case 14: /* type: BOOLEAN  */
#line 331 "yacc.y"
              {  }
#line 1725 "y.tab.c"
    break;

  case 15: /* type: CHAR  */
#line 332 "yacc.y"
           {  }
#line 1731 "y.tab.c"
    break;

  case 16: /* begin_end: START stmt_list END  */
#line 335 "yacc.y"
                               {(yyval.intval) = (yyvsp[-1].intval);}
#line 1737 "y.tab.c"
    break;

  case 17: /* stmt_list: stmt stmt_list  */
#line 338 "yacc.y"
                          {(yyval.intval) = (yyvsp[-1].intval) + (yyvsp[0].intval);}
#line 1743 "y.tab.c"
    break;

  case 18: /* stmt_list: stmt  */
#line 338 "yacc.y"
                                               {(yyval.intval)=(yyvsp[0].intval);}
#line 1749 "y.tab.c"
    break;

  case 19: /* stmt: assign_stmt  */
#line 341 "yacc.y"
                  {(yyval.intval)=(yyvsp[0].intval);}
#line 1755 "y.tab.c"
    break;

  case 20: /* stmt: if_stmt  */
#line 342 "yacc.y"
          {(yyval.intval)=(yyvsp[0].intval);}
#line 1761 "y.tab.c"
    break;

  case 21: /* stmt: while_stmt  */
#line 343 "yacc.y"
             {(yyval.intval)=(yyvsp[0].intval);}
#line 1767 "y.tab.c"
    break;

  case 22: /* stmt: for_stmt  */
#line 344 "yacc.y"
           {(yyval.intval)=(yyvsp[0].intval);}
#line 1773 "y.tab.c"
    break;

  case 23: /* stmt: read_stmt  */
#line 345 "yacc.y"
            {(yyval.intval)=(yyvsp[0].intval);}
#line 1779 "y.tab.c"
    break;

  case 24: /* stmt: write_stmt  */
#line 346 "yacc.y"
            {(yyval.intval)=(yyvsp[0].intval);}
#line 1785 "y.tab.c"
    break;

  case 25: /* assign_stmt: ID ASSIGN expr SEMICOLON  */
#line 350 "yacc.y"
            {
		struct TempVar var1 = popFromTempStack();

	    AddCode(OP_ASSIGN, var1.name, NULL, strdup((yyvsp[-3].strval)));
	    (yyval.intval) = 1 + (yyvsp[-1].intval);
            }
#line 1796 "y.tab.c"
    break;

  case 26: /* assign_stmt: ID LBRACK expr RBRACK ASSIGN expr SEMICOLON  */
#line 358 "yacc.y"
            {
            	struct TempVar rval2 = popFromTempStack();
	    struct TempVar rval1 = popFromTempStack();

	    char* res = NewTempVar();
	    AddCode(OP_ASSIGN_ADDR, strdup((yyvsp[-6].strval)), NULL, res);

	    char* res2 = NewTempVar();
	    AddCode(OP_MUL, "4", rval1.name, res2);

	    char* res1 = NewTempVar();
	    AddCode(OP_PLUS, res2, res, res1);
	    AddCode(OP_PTR_ASSIGN, rval2.name, NULL, res1);

	    (yyval.intval) = (yyvsp[-1].intval) + (yyvsp[-4].intval) + 4;
            }
#line 1817 "y.tab.c"
    break;

  case 27: /* if_stmt: IF condn THEN c_stmt_list  */
#line 376 "yacc.y"
                                   {
	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack

    	char* endLabel = NewLabel(nCode-(yyvsp[0].intval)+1);
        char* offsetBack = NewLabel(nCode);
        char* goBack = NewLabel(-(yyvsp[0].intval)-2);
        AddCodeBefore((yyvsp[0].intval), OP_IF, condResult.name, endLabel, NULL);  // Place conditional jump
        AddCodeBefore((yyvsp[0].intval), OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump
        
        (yyval.intval) = 2 + (yyvsp[0].intval) ;
}
#line 1833 "y.tab.c"
    break;

  case 28: /* if_stmt: IF condn THEN ifelse_stmt_list ELSE c_stmt_list  */
#line 388 "yacc.y"
                                                 {
	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack

    	char* endLabel = NewLabel(nCode-(yyvsp[-2].intval)-(yyvsp[0].intval)+1);
        char* offsetBack = NewLabel(nCode-(yyvsp[0].intval));
        char* goBack = NewLabel(-(yyvsp[-2].intval)-2);
        AddCodeBefore((yyvsp[-2].intval)+(yyvsp[0].intval), OP_IF, condResult.name, endLabel, NULL);  // Place conditional jump
        AddCodeBefore((yyvsp[-2].intval)+(yyvsp[0].intval), OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump
        
        (yyval.intval) = 2 + (yyvsp[-2].intval) + (yyvsp[0].intval);
}
#line 1849 "y.tab.c"
    break;

  case 29: /* while_stmt: WHILE condn DO c_stmt_list  */
#line 402 "yacc.y"
    {
	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack

    	char* endLabel = NewLabel(nCode-(yyvsp[0].intval)+1);
        char* offsetBack = NewLabel(nCode+1);
        char* goBack = NewLabel(-(yyvsp[0].intval)-2);
        AddCodeBefore((yyvsp[0].intval), OP_IF, condResult.name, endLabel, NULL);  // Place conditional jump
        AddCodeBefore((yyvsp[0].intval), OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump

        AddCode(OP_GOTO, goBack, NULL, NULL);  // Jump back to the start of the loop
        
        (yyval.intval) = 3 + (yyvsp[0].intval);
    }
#line 1867 "y.tab.c"
    break;

  case 30: /* for_stmt: FOR ID ASSIGN expr TO expr DO c_stmt_list  */
#line 420 "yacc.y"
                                                    {
    	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack
    	struct TempVar condResult1 = popFromTempStack();
    	struct TempVar condResult2 = popFromTempStack();
    	//printf("s", condResult.name);

	char* endLabel = NewLabel(nCode-(yyvsp[0].intval)+1);
        char* offsetBack = NewLabel(nCode+1);
        char* goBack = NewLabel(-(yyvsp[0].intval)-2);

	AddCodeBefore((yyvsp[0].intval), OP_ASSIGN, condResult1.name, NULL, strdup((yyvsp[-6].strval)));
	
    	
        
        char* res = (char *)malloc(30*sizeof(char));
    	sprintf(res, "%s < %s", strdup((yyvsp[-6].strval)), condResult.name);
        
        AddCodeBefore((yyvsp[0].intval), OP_IF, res, endLabel, NULL);  // Place conditional jump
        AddCodeBefore((yyvsp[0].intval), OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump
        

        AddCode(OP_GOTO, goBack, NULL, NULL);  // Jump back to the start of the loop
        
        (yyval.intval) = 3 + (yyvsp[0].intval);
}
#line 1897 "y.tab.c"
    break;

  case 31: /* for_stmt: FOR ID ASSIGN expr DOWNTO expr DO c_stmt_list  */
#line 446 "yacc.y"
                                                {
	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack
    	struct TempVar condResult1 = popFromTempStack();
	struct TempVar condResult2 = popFromTempStack();
	
    	char* endLabel = NewLabel(nCode-(yyvsp[0].intval)+1);
        char* offsetBack = NewLabel(nCode+1);
        char* goBack = NewLabel(-(yyvsp[0].intval)-2);
        
        AddCodeBefore((yyvsp[0].intval), OP_ASSIGN, condResult1.name, NULL, strdup((yyvsp[-6].strval)));
        
        char* res = (char *)malloc(30*sizeof(char));
    	sprintf(res, "%s > %s", strdup((yyvsp[-6].strval)), condResult.name);
    	
        AddCodeBefore((yyvsp[0].intval), OP_IF, res, endLabel, NULL);  // Place conditional jump
        AddCodeBefore((yyvsp[0].intval), OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump

        AddCode(OP_GOTO, goBack, NULL, NULL);  // Jump back to the start of the loop
        
        (yyval.intval) = 3 + (yyvsp[0].intval);
}
#line 1923 "y.tab.c"
    break;

  case 32: /* read_stmt: READ LPAREN ID RPAREN SEMICOLON  */
#line 470 "yacc.y"
                                           {(yyval.intval)=0;}
#line 1929 "y.tab.c"
    break;

  case 33: /* read_stmt: READ LPAREN ID LBRACK expr RBRACK RPAREN SEMICOLON  */
#line 470 "yacc.y"
                                                                                                       {(yyval.intval)=0;}
#line 1935 "y.tab.c"
    break;

  case 34: /* write_stmt: WRITE LPAREN STRING RPAREN SEMICOLON  */
#line 473 "yacc.y"
                                                 {(yyval.intval)=0;}
#line 1941 "y.tab.c"
    break;

  case 35: /* write_stmt: WRITE LPAREN expr RPAREN SEMICOLON  */
#line 473 "yacc.y"
                                                                                             {(yyval.intval)=0;}
#line 1947 "y.tab.c"
    break;

  case 36: /* write_stmt: WRITE LPAREN w_ID_list RPAREN SEMICOLON  */
#line 473 "yacc.y"
                                                                                                                                             {(yyval.intval)=0;}
#line 1953 "y.tab.c"
    break;

  case 37: /* c_stmt_list: START stmt_list END SEMICOLON  */
#line 476 "yacc.y"
                                           {(yyval.intval)=(yyvsp[-2].intval);}
#line 1959 "y.tab.c"
    break;

  case 38: /* ifelse_stmt_list: START stmt_list END  */
#line 479 "yacc.y"
                                      {(yyval.intval)=(yyvsp[-1].intval);}
#line 1965 "y.tab.c"
    break;

  case 39: /* w_ID_list: ID COMMA w_ID_list  */
#line 482 "yacc.y"
                              {}
#line 1971 "y.tab.c"
    break;

  case 40: /* w_ID_list: ID COMMA ID  */
#line 482 "yacc.y"
                                               {}
#line 1977 "y.tab.c"
    break;

  case 41: /* expr: expr PLUS expr  */
#line 486 "yacc.y"
                     {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_PLUS, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
}
#line 1991 "y.tab.c"
    break;

  case 42: /* expr: expr MINUS expr  */
#line 495 "yacc.y"
                  {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_MINUS, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
}
#line 2005 "y.tab.c"
    break;

  case 43: /* expr: expr MUL expr  */
#line 504 "yacc.y"
                {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_MUL, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
}
#line 2019 "y.tab.c"
    break;

  case 44: /* expr: expr DIV expr  */
#line 513 "yacc.y"
                {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_DIV, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
}
#line 2033 "y.tab.c"
    break;

  case 45: /* expr: expr MOD expr  */
#line 522 "yacc.y"
                {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_MOD, var2.name, var1.name, res);
	
    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
}
#line 2047 "y.tab.c"
    break;

  case 46: /* expr: NUM  */
#line 531 "yacc.y"
      {
    pushToTempStack(strdup((yyvsp[0].strval)), INT_CONST_TYPE);
    (yyval.intval) = 0;
}
#line 2056 "y.tab.c"
    break;

  case 47: /* expr: ID  */
#line 535 "yacc.y"
     {
    pushToTempStack(strdup((yyvsp[0].strval)), UK_VAR_TYPE);
    (yyval.intval) = 0;
}
#line 2065 "y.tab.c"
    break;

  case 48: /* expr: REAL_NUM  */
#line 540 "yacc.y"
    {
       pushToTempStack(strdup((yyvsp[0].strval)), FLOAT_CONST_TYPE);
    	(yyval.intval) = 0;
    }
#line 2074 "y.tab.c"
    break;

  case 49: /* expr: CHAR_CONST  */
#line 545 "yacc.y"
    {
    	pushToTempStack(strdup((yyvsp[0].strval)), CHAR_CONST_TYPE);
    	(yyval.intval) = 0;
    }
#line 2083 "y.tab.c"
    break;

  case 50: /* expr: TRUTH  */
#line 550 "yacc.y"
    {
    	
    }
#line 2091 "y.tab.c"
    break;

  case 51: /* expr: LIE  */
#line 554 "yacc.y"
    {

    }
#line 2099 "y.tab.c"
    break;

  case 52: /* expr: ID LBRACK expr RBRACK  */
#line 558 "yacc.y"
    {
    	struct TempVar rval = popFromTempStack();
	    char* res = NewTempVar();
	    AddCode(OP_ASSIGN_ADDR, strdup((yyvsp[-3].strval)), NULL, res);

	    char* res2 = NewTempVar();
	    AddCode(OP_MUL, "4", rval.name, res2);

	    char* res1 = NewTempVar();
	    AddCode(OP_PLUS, res2, res, res1);
	    // AddCode(OP_PTR_ASSIGN, rval.name, NULL, res1);

	    char temp[10] = "*";
	    strcat(temp, strdup(res1));

	    pushToTempStack(strdup(temp), FLOAT_TYPE);

	    (yyval.intval) = (yyvsp[-1].intval) + 3;
    }
#line 2123 "y.tab.c"
    break;

  case 53: /* expr: LPAREN expr RPAREN  */
#line 578 "yacc.y"
    {
    	(yyval.intval) = (yyvsp[-1].intval);
    }
#line 2131 "y.tab.c"
    break;

  case 54: /* condn: expr EQ expr  */
#line 583 "yacc.y"
                   {
	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s == %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
	}
#line 2145 "y.tab.c"
    break;

  case 55: /* condn: expr NEQ expr  */
#line 593 "yacc.y"
                 {
 	//char* res = NewTempVar();
    struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s <> %s", var1.name, var2.name);
    //AddCode(OP_NEQ, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
 	}
#line 2161 "y.tab.c"
    break;

  case 56: /* condn: expr LT expr  */
#line 605 "yacc.y"
                {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s < %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
 	}
#line 2175 "y.tab.c"
    break;

  case 57: /* condn: expr GT expr  */
#line 615 "yacc.y"
                {
 	printf("YYY");
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s > %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
 	}
#line 2190 "y.tab.c"
    break;

  case 58: /* condn: expr LE expr  */
#line 625 "yacc.y"
                {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s <= %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
 	}
#line 2204 "y.tab.c"
    break;

  case 59: /* condn: expr GE expr  */
#line 635 "yacc.y"
                {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s >= %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
 	}
#line 2218 "y.tab.c"
    break;

  case 60: /* condn: LPAREN condn RPAREN  */
#line 645 "yacc.y"
                       {
 	(yyval.intval) = (yyvsp[-1].intval);
 }
#line 2226 "y.tab.c"
    break;

  case 61: /* condn: condn AND condn  */
#line 649 "yacc.y"
                   {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s <> %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
 	}
#line 2240 "y.tab.c"
    break;

  case 62: /* condn: condn OR condn  */
#line 659 "yacc.y"
                  {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s <> %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    (yyval.intval) = 1 + (yyvsp[-2].intval) + (yyvsp[0].intval);
 	}
#line 2254 "y.tab.c"
    break;

  case 63: /* condn: NOT condn  */
#line 669 "yacc.y"
             {
 	struct TempVar un = popFromTempStack();
    char* var = NewTempVar();
    AddCode(OP_NOT, un.name, NULL, var);

    pushToTempStack(var, un.type);
    (yyval.intval) = 1 + (yyvsp[0].intval);
 	}
#line 2267 "y.tab.c"
    break;

  case 64: /* condn: expr  */
#line 677 "yacc.y"
       {
 	(yyval.intval) = (yyvsp[0].intval);
 }
#line 2275 "y.tab.c"
    break;


#line 2279 "y.tab.c"

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

#line 683 "yacc.y"



int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    yyin = file;
    if (!yyparse()) {
        printf("Parsing Done\n");
        PrintIntermediateCode();
    } else {
        printf("Failed\n");
    }
    fclose(yyin);
    return 0;
}
void yyerror(char *) {
    fprintf(stderr, "Error");
}

