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
#line 1 "PWS42X5Y.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_TABLE_SIZE 1000

int yylex();
extern FILE *yyin;

typedef struct ASTNodeCopy {
    char *type;
    char *value;
    char *dtype;
    struct ASTNodeCopy *firstChild;
    struct ASTNodeCopy *nextSibling;
} ASTNodeCopy;
ASTNodeCopy* root;

typedef union {
    int intValue;
    float realValue;
    char charValue;
    int boolValue;
    int *arrayValue; // for arrays
} ValueUnion;

typedef struct {
    char *name;
    char *type;
    int declared;
    int referenced;
    int size;
    int isArray;
    // int index;
    ValueUnion value;
} SymbolEntry;
SymbolEntry symbolTable[SYMBOL_TABLE_SIZE];
int symbolTableIndex = 0;

void addToSymbolTable(char *name, char *type, int size, int isArray);
int checkDeclared(char *name);
void markReferenced(char *name);
char* lookupType(char *name);
char* determineExprType(char* op, char* leftType, char* rightType);
void printSymbolTable();

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

#line 123 "y.tab.c"

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
    void dfs(ASTNode* v);

    int evaluateExpr(ASTNode *node);
    void executeAssign(ASTNode* node);
    void executeIf(ASTNode* node);
    void executeFor(ASTNode* node);
    void executeWhile(ASTNode* node);
    void executeRead(ASTNode* node);
    void executeWrite(ASTNode* node);
    void executeProgram(ASTNode* node);
    void executeStmtList(ASTNode* node);
    void executeVarDecl(ASTNode* node);
    void executeVarDeclList(ASTNode* node);
    void executeStmt(ASTNode* node);

#line 187 "y.tab.c"

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
#line 82 "PWS42X5Y.y"

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

#line 329 "y.tab.c"

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
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_NUM = 4,                        /* NUM  */
  YYSYMBOL_REAL_NUM = 5,                   /* REAL_NUM  */
  YYSYMBOL_CHAR_CONST = 6,                 /* CHAR_CONST  */
  YYSYMBOL_STRING = 7,                     /* STRING  */
  YYSYMBOL_PROGRAM = 8,                    /* PROGRAM  */
  YYSYMBOL_VAR = 9,                        /* VAR  */
  YYSYMBOL_INTEGER = 10,                   /* INTEGER  */
  YYSYMBOL_REAL = 11,                      /* REAL  */
  YYSYMBOL_BOOLEAN = 12,                   /* BOOLEAN  */
  YYSYMBOL_CHAR = 13,                      /* CHAR  */
  YYSYMBOL_TO = 14,                        /* TO  */
  YYSYMBOL_DOWNTO = 15,                    /* DOWNTO  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_FOR = 19,                       /* FOR  */
  YYSYMBOL_DO = 20,                        /* DO  */
  YYSYMBOL_ARRAY = 21,                     /* ARRAY  */
  YYSYMBOL_AND = 22,                       /* AND  */
  YYSYMBOL_OR = 23,                        /* OR  */
  YYSYMBOL_NOT = 24,                       /* NOT  */
  YYSYMBOL_START = 25,                     /* START  */
  YYSYMBOL_END = 26,                       /* END  */
  YYSYMBOL_READ = 27,                      /* READ  */
  YYSYMBOL_WRITE = 28,                     /* WRITE  */
  YYSYMBOL_ASSIGN = 29,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 30,                      /* PLUS  */
  YYSYMBOL_MINUS = 31,                     /* MINUS  */
  YYSYMBOL_MUL = 32,                       /* MUL  */
  YYSYMBOL_DIV = 33,                       /* DIV  */
  YYSYMBOL_MOD = 34,                       /* MOD  */
  YYSYMBOL_EQ = 35,                        /* EQ  */
  YYSYMBOL_NEQ = 36,                       /* NEQ  */
  YYSYMBOL_LT = 37,                        /* LT  */
  YYSYMBOL_GT = 38,                        /* GT  */
  YYSYMBOL_LE = 39,                        /* LE  */
  YYSYMBOL_GE = 40,                        /* GE  */
  YYSYMBOL_LPAREN = 41,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 42,                    /* RPAREN  */
  YYSYMBOL_LBRACK = 43,                    /* LBRACK  */
  YYSYMBOL_RBRACK = 44,                    /* RBRACK  */
  YYSYMBOL_COLON = 45,                     /* COLON  */
  YYSYMBOL_SEMICOLON = 46,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 47,                     /* COMMA  */
  YYSYMBOL_PERIOD = 48,                    /* PERIOD  */
  YYSYMBOL_INVALID = 49,                   /* INVALID  */
  YYSYMBOL_OF = 50,                        /* OF  */
  YYSYMBOL_THEN = 51,                      /* THEN  */
  YYSYMBOL_DQUOTE = 52,                    /* DQUOTE  */
  YYSYMBOL_TRUTH = 53,                     /* TRUTH  */
  YYSYMBOL_LIE = 54,                       /* LIE  */
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
#define YYLAST   235

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155

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
       0,   116,   116,   124,   129,   134,   139,   150,   163,   178,
     197,   218,   234,   235,   236,   237,   240,   247,   257,   264,
     265,   266,   267,   268,   269,   272,   286,   304,   310,   319,
     327,   336,   347,   351,   358,   362,   367,   374,   379,   384,
     393,   399,   409,   418,   427,   436,   445,   450,   458,   466,
     474,   480,   486,   501,   507,   515,   523,   531,   539,   547,
     555,   563,   571,   579
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "NUM",
  "REAL_NUM", "CHAR_CONST", "STRING", "PROGRAM", "VAR", "INTEGER", "REAL",
  "BOOLEAN", "CHAR", "TO", "DOWNTO", "IF", "ELSE", "WHILE", "FOR", "DO",
  "ARRAY", "AND", "OR", "NOT", "START", "END", "READ", "WRITE", "ASSIGN",
  "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQ", "NEQ", "LT", "GT", "LE",
  "GE", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "COLON", "SEMICOLON",
  "COMMA", "PERIOD", "INVALID", "OF", "THEN", "DQUOTE", "TRUTH", "LIE",
  "$accept", "program", "var_decl_section", "var_decl_list", "var_decl",
  "ID_list", "type", "begin_end", "stmt_list", "stmt", "assign_stmt",
  "if_stmt", "while_stmt", "for_stmt", "read_stmt", "write_stmt",
  "c_stmt_list", "ifelse_stmt_list", "w_ID_list", "expr", "condn", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-101)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-41)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      16,    39,    44,    15,  -101,    57,    69,    56,   -39,    69,
    -101,    37,   110,    35,   187,    84,  -101,   215,   -24,    49,
      49,    85,    59,    64,    88,  -101,  -101,  -101,  -101,  -101,
    -101,  -101,  -101,  -101,  -101,  -101,  -101,    55,    66,    70,
    -101,    75,    43,    43,    80,  -101,  -101,  -101,    49,    43,
    -101,  -101,   179,     0,    -2,    98,   127,     9,  -101,  -101,
     132,  -101,  -101,   109,    45,    43,  -101,   149,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    49,
      49,   129,   131,    43,   -16,    22,    89,   115,   162,   113,
    -101,   133,   119,  -101,    60,    60,  -101,  -101,  -101,   190,
     190,   190,   190,   190,   190,  -101,   136,   110,  -101,   158,
     110,  -101,    26,   130,    43,   174,   143,   144,   155,   157,
      43,  -101,    92,   131,   106,    43,    43,  -101,   134,   156,
    -101,  -101,  -101,  -101,   198,   114,   160,  -101,   160,   139,
     154,   165,   185,  -101,  -101,   131,   131,   184,   181,  -101,
    -101,  -101,   215,   186,  -101
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
      10,     0,     0,     0,    46,    47,    48,    49,     0,     0,
      50,    51,    63,     0,     0,     0,     0,     0,    16,    17,
       0,     7,     8,     0,     0,     0,    62,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,     0,     0,
      25,     0,     0,    53,    41,    42,    43,    44,    45,    54,
      55,    56,    57,    58,    59,    60,    61,     0,    27,     0,
       0,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    52,     0,     0,     0,     0,     0,    32,     0,    40,
      39,    34,    36,    35,     0,     0,    38,    28,     0,     0,
       0,     0,     0,    26,    37,     0,     0,     0,     0,    30,
      31,    33,     0,     0,     9
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -101,  -101,  -101,  -101,   224,   219,   -17,  -101,  -100,   -23,
    -101,  -101,  -101,  -101,  -101,  -101,   -78,  -101,   120,   -40,
      -9
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     7,     9,    10,    11,    38,    13,    24,    25,
      26,    27,    28,    29,    30,    31,   108,   109,    87,    52,
      53
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,    59,    63,    64,   111,    42,    14,   122,    15,    67,
     124,    54,    85,    45,    46,    47,    86,    88,    82,    43,
      79,    80,    79,    80,     1,    92,   113,   114,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,    66,
     125,   126,     3,   112,     4,   137,    44,    45,    46,    47,
      49,    81,    44,    45,    46,    47,    68,    69,    70,    71,
      72,     5,    50,    51,   -40,    65,     6,   149,   150,   115,
     105,   106,     8,    48,   128,    68,    69,    70,    71,    72,
     135,    12,    17,    32,    49,   139,   140,    39,    55,    91,
      49,    18,    70,    71,    72,    18,    50,    51,    60,    59,
      56,    59,    50,    51,    19,    57,    20,    21,    19,    18,
      20,    21,    61,    18,    58,    22,    23,    15,   136,    22,
      23,    62,    19,    65,    20,    21,    19,    83,    20,    21,
      84,   116,   138,    22,    23,   153,    89,    22,    23,    68,
      69,    70,    71,    72,    68,    69,    70,    71,    72,    68,
      69,    70,    71,    72,   107,    90,   110,   117,    79,   145,
     143,   119,   120,   121,    68,    69,    70,    71,    72,    68,
      69,    70,    71,    72,   146,   123,   127,   129,   141,    68,
      69,    70,    71,    72,    68,    69,    70,    71,    72,   131,
     132,    93,    68,    69,    70,    71,    72,    33,    34,    35,
      36,   133,   142,   115,   118,   134,   144,   147,    37,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      68,    69,    70,    71,    72,    33,    34,    35,    36,   148,
     151,   152,   154,    16,    40,   130
};

static const yytype_uint8 yycheck[] =
{
      17,    24,    42,    43,    82,    29,    45,   107,    47,    49,
     110,    20,     3,     4,     5,     6,     7,    57,    20,    43,
      22,    23,    22,    23,     8,    65,    42,    43,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    48,
      14,    15,     3,    83,     0,   123,     3,     4,     5,     6,
      41,    51,     3,     4,     5,     6,    30,    31,    32,    33,
      34,    46,    53,    54,    42,    43,     9,   145,   146,    47,
      79,    80,     3,    24,   114,    30,    31,    32,    33,    34,
     120,    25,    45,    48,    41,   125,   126,     3,     3,    44,
      41,     3,    32,    33,    34,     3,    53,    54,    43,   122,
      41,   124,    53,    54,    16,    41,    18,    19,    16,     3,
      18,    19,    46,     3,    26,    27,    28,    47,    26,    27,
      28,    46,    16,    43,    18,    19,    16,    29,    18,    19,
       3,    42,    26,    27,    28,   152,     4,    27,    28,    30,
      31,    32,    33,    34,    30,    31,    32,    33,    34,    30,
      31,    32,    33,    34,    25,    46,    25,    42,    22,    20,
      46,    48,    29,    44,    30,    31,    32,    33,    34,    30,
      31,    32,    33,    34,    20,    17,    46,     3,    44,    30,
      31,    32,    33,    34,    30,    31,    32,    33,    34,    46,
      46,    42,    30,    31,    32,    33,    34,    10,    11,    12,
      13,    46,     4,    47,    42,    48,    46,    42,    21,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      30,    31,    32,    33,    34,    10,    11,    12,    13,    44,
      46,    50,    46,     9,    15,   115
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     8,    56,     3,     0,    46,     9,    57,     3,    58,
      59,    60,    25,    62,    45,    47,    59,    45,     3,    16,
      18,    19,    27,    28,    63,    64,    65,    66,    67,    68,
      69,    70,    48,    10,    11,    12,    13,    21,    61,     3,
      60,    61,    29,    43,     3,     4,     5,     6,    24,    41,
      53,    54,    74,    75,    75,     3,    41,    41,    26,    64,
      43,    46,    46,    74,    74,    43,    75,    74,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    22,
      23,    51,    20,    29,     3,     3,     7,    73,    74,     4,
      46,    44,    74,    42,    74,    74,    74,    74,    74,    74,
      74,    74,    74,    74,    74,    75,    75,    25,    71,    72,
      25,    71,    74,    42,    43,    47,    42,    42,    42,    48,
      29,    44,    63,    17,    63,    14,    15,    46,    74,     3,
      73,    46,    46,    46,    48,    74,    26,    71,    26,    74,
      74,    44,     4,    46,    46,    20,    20,    42,    44,    71,
      71,    46,    50,    61,    46
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
      75,    75,    75,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     2,     0,     1,     2,     4,     4,    12,
       3,     1,     1,     1,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     4,     7,     4,     6,     4,
       8,     8,     5,     8,     5,     5,     5,     4,     3,     3,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1
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
#line 116 "PWS42X5Y.y"
                                                                {
    root = (yyval.node) = createNode("program", (yyvsp[-4].id));
    addChildNode((yyval.node), (yyvsp[-2].node));
    addChildNode((yyval.node), (yyvsp[-1].node));
    // executeProgram($$);
}
#line 1501 "y.tab.c"
    break;

  case 3: /* var_decl_section: VAR var_decl_list  */
#line 125 "PWS42X5Y.y"
{
    (yyval.node) = createNode("var_decl_section", NULL);
    addChildNode((yyval.node), (yyvsp[0].node));
    // executeVarDeclList($2);
}
#line 1511 "y.tab.c"
    break;

  case 4: /* var_decl_section: %empty  */
#line 129 "PWS42X5Y.y"
                {
    (yyval.node) = NULL;
}
#line 1519 "y.tab.c"
    break;

  case 5: /* var_decl_list: var_decl  */
#line 134 "PWS42X5Y.y"
                        {
    (yyval.node) = createNode("var_decl_list", NULL);
    addChildNode((yyval.node), (yyvsp[0].node));
    // executeVarDecl($1);
}
#line 1529 "y.tab.c"
    break;

  case 6: /* var_decl_list: var_decl_list var_decl  */
#line 139 "PWS42X5Y.y"
                         {
    if ((yyvsp[-1].node) == NULL) {
        (yyval.node) = (yyvsp[0].node);
    } else {
        addChildNode((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
    // executeVarDecl($2);
}
#line 1543 "y.tab.c"
    break;

  case 7: /* var_decl: ID COLON type SEMICOLON  */
#line 151 "PWS42X5Y.y"
{
    if (checkDeclared((yyvsp[-3].id)) != -1) {
        fprintf(stderr, "Multiple declarations of variable %s\n", (yyvsp[-3].id));
    } else {
        addToSymbolTable((yyvsp[-3].id), (yyvsp[-1].id), 0, 0);
    }
    (yyval.node) = createNode("var_decl", NULL);
    ASTNode *varNode = createNode("variable", (yyvsp[-3].id));
    ASTNode *typeNode = createNode("type", (yyvsp[-1].id));
    addChildNode(varNode, typeNode);
    addChildNode((yyval.node), varNode);
}
#line 1560 "y.tab.c"
    break;

  case 8: /* var_decl: ID_list COLON type SEMICOLON  */
#line 164 "PWS42X5Y.y"
{
    (yyval.node) = createNode("var_decl", NULL);
    ASTNode *typeNode = createNode("type", (yyvsp[-1].id));
    for (int i = 0; i < (yyvsp[-3].id_list).count; i++) {
        ASTNode *varNode = createNode("variable", (yyvsp[-3].id_list).ids[i]);
        addChildNode(varNode, typeNode);
        addChildNode((yyval.node), varNode);
        if (checkDeclared((yyvsp[-3].id_list).ids[i]) != -1) {
            fprintf(stderr, "Multiple declarations of variable %s\n", (yyvsp[-3].id_list).ids[i]);
        } else {
            addToSymbolTable((yyvsp[-3].id_list).ids[i], (yyvsp[-1].id), 0, 0);
        }
    }
}
#line 1579 "y.tab.c"
    break;

  case 9: /* var_decl: ID COLON ARRAY LBRACK NUM PERIOD PERIOD NUM RBRACK OF type SEMICOLON  */
#line 179 "PWS42X5Y.y"
{
    if (checkDeclared((yyvsp[-11].id)) != -1) {
        fprintf(stderr, "Multiple declarations of variable %s\n", (yyvsp[-11].id));
    } else {
        int size = (yyvsp[-4].num) - (yyvsp[-7].num) + 1; // Calculate array size
        addToSymbolTable((yyvsp[-11].id), (yyvsp[-1].id), size, 1); // For arrays, provide size information
    }
    (yyval.node) = createNode("var_decl", NULL);
    ASTNode *arrNode = createNode("array_decl", (yyvsp[-11].id));
    addChildNode((yyval.node), arrNode);
    ASTNode *sizeNode = createNode("size", NULL);
    sizeNode->value = malloc(20);
    sprintf(sizeNode->value, "%d", (yyvsp[-4].num) - (yyvsp[-7].num) + 1);
    addChildNode(arrNode, sizeNode);
    addChildNode(arrNode, createNode("type", (yyvsp[-1].id)));
}
#line 1600 "y.tab.c"
    break;

  case 10: /* ID_list: ID COMMA ID_list  */
#line 198 "PWS42X5Y.y"
{
    if ((yyvsp[0].id_list).ids == NULL) {
        yyerror("Memory allocation failed");
        exit(1);
    }
    (yyval.id_list).ids = (char **) malloc(sizeof(char *) * ((yyvsp[0].id_list).count + 1));
    if ((yyval.id_list).ids == NULL) {
        yyerror("Memory allocation failed");
        exit(1);
    }
    (yyval.id_list).ids[0] = (yyvsp[-2].id);
    if ((yyval.id_list).ids[0] == NULL) {
        yyerror("Memory allocation failed");
        exit(1);
    }
    for (int i = 0; i < (yyvsp[0].id_list).count; i++) {
        (yyval.id_list).ids[i+1] = (yyvsp[0].id_list).ids[i];
    }
    (yyval.id_list).count = (yyvsp[0].id_list).count + 1;
}
#line 1625 "y.tab.c"
    break;

  case 11: /* ID_list: ID  */
#line 219 "PWS42X5Y.y"
{
    (yyval.id_list).ids = (char **) malloc(sizeof(char *));
    if ((yyval.id_list).ids == NULL) {
        yyerror("Memory allocation failed");
        exit(1);
    }
    (yyval.id_list).ids[0] = strdup((yyvsp[0].id));
    if ((yyval.id_list).ids[0] == NULL) {
        yyerror("Memory allocation failed");
        exit(1);
    }
    (yyval.id_list).count = 1;
}
#line 1643 "y.tab.c"
    break;

  case 12: /* type: INTEGER  */
#line 234 "PWS42X5Y.y"
              { (yyval.id) = "int"; }
#line 1649 "y.tab.c"
    break;

  case 13: /* type: REAL  */
#line 235 "PWS42X5Y.y"
           { (yyval.id) = "real"; }
#line 1655 "y.tab.c"
    break;

  case 14: /* type: BOOLEAN  */
#line 236 "PWS42X5Y.y"
              { (yyval.id) = "boolean"; }
#line 1661 "y.tab.c"
    break;

  case 15: /* type: CHAR  */
#line 237 "PWS42X5Y.y"
           { (yyval.id) = "char"; }
#line 1667 "y.tab.c"
    break;

  case 16: /* begin_end: START stmt_list END  */
#line 240 "PWS42X5Y.y"
                               {
    (yyval.node) = createNode("block", NULL);
    addChildNode((yyval.node), (yyvsp[-1].node));
    // executeStmtList($2);
}
#line 1677 "y.tab.c"
    break;

  case 17: /* stmt_list: stmt_list stmt  */
#line 247 "PWS42X5Y.y"
                          {
    if ((yyvsp[-1].node) == NULL) {
        (yyval.node) = createNode("stmt_list", NULL);
        addChildNode((yyval.node), (yyvsp[0].node));
    } else {
        addChildNode((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
    // executeStmt($2);
}
#line 1692 "y.tab.c"
    break;

  case 18: /* stmt_list: stmt  */
#line 257 "PWS42X5Y.y"
       {
    (yyval.node) = createNode("stmt_list", NULL);
    addChildNode((yyval.node), (yyvsp[0].node));
    // executeStmt($1);
}
#line 1702 "y.tab.c"
    break;

  case 19: /* stmt: assign_stmt  */
#line 264 "PWS42X5Y.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1708 "y.tab.c"
    break;

  case 20: /* stmt: if_stmt  */
#line 265 "PWS42X5Y.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1714 "y.tab.c"
    break;

  case 21: /* stmt: while_stmt  */
#line 266 "PWS42X5Y.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1720 "y.tab.c"
    break;

  case 22: /* stmt: for_stmt  */
#line 267 "PWS42X5Y.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1726 "y.tab.c"
    break;

  case 23: /* stmt: read_stmt  */
#line 268 "PWS42X5Y.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1732 "y.tab.c"
    break;

  case 24: /* stmt: write_stmt  */
#line 269 "PWS42X5Y.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1738 "y.tab.c"
    break;

  case 25: /* assign_stmt: ID ASSIGN expr SEMICOLON  */
#line 273 "PWS42X5Y.y"
{
    (yyval.node) = createNode("assign", NULL);
    addChildNode((yyval.node), createNode("id", (yyvsp[-3].id)));
    addChildNode((yyval.node), (yyvsp[-1].node));
    char* idType = lookupType((yyvsp[-3].id));
    char* exprType = (yyvsp[-1].node)->dtype; // Assuming expr nodes carry type as value
    if (strcmp(idType, "undefined") == 0) {
        fprintf(stderr, "Variable is not declared\n");
    } else if (strcmp(idType, exprType) != 0) {
        fprintf(stderr, "Type error: Cannot assign %s to %s\n", exprType, idType);
    }
    // executeAssign($$);
}
#line 1756 "y.tab.c"
    break;

  case 26: /* assign_stmt: ID LBRACK expr RBRACK ASSIGN expr SEMICOLON  */
#line 287 "PWS42X5Y.y"
{
    (yyval.node) = createNode("array_assign", NULL);
    addChildNode((yyval.node), createNode("id", (yyvsp[-6].id)));
    addChildNode((yyval.node), (yyvsp[-4].node)); // index
    addChildNode((yyval.node), (yyvsp[-1].node)); // value
    char* arrayType = lookupType((yyvsp[-6].id));
    char* assignType = (yyvsp[-1].node)->dtype; // Assuming expr nodes carry type as value
    if (arrayType == NULL || strcmp(arrayType, "undefined") == 0) {
        fprintf(stderr, "Error: Undeclared array %s\n", (yyvsp[-6].id));
    }
    else if (strcmp(arrayType, assignType) != 0) {
        fprintf(stderr, "Type mismatch: Cannot assign %s to %s\n", assignType, arrayType);
    }
    // executeAssign($$);
}
#line 1776 "y.tab.c"
    break;

  case 27: /* if_stmt: IF condn THEN c_stmt_list  */
#line 304 "PWS42X5Y.y"
                                   {
    (yyval.node) = createNode("if", NULL);
    addChildNode((yyval.node), (yyvsp[-2].node));
    addChildNode((yyval.node), (yyvsp[0].node));
    // executeIf($$);
}
#line 1787 "y.tab.c"
    break;

  case 28: /* if_stmt: IF condn THEN ifelse_stmt_list ELSE c_stmt_list  */
#line 310 "PWS42X5Y.y"
                                                  {
    (yyval.node) = createNode("if_else", NULL);
    addChildNode((yyval.node), (yyvsp[-4].node));
    addChildNode((yyval.node), (yyvsp[-2].node));
    addChildNode((yyval.node), (yyvsp[0].node));
    // executeIf($$);
}
#line 1799 "y.tab.c"
    break;

  case 29: /* while_stmt: WHILE condn DO c_stmt_list  */
#line 319 "PWS42X5Y.y"
                                       {
    (yyval.node) = createNode("while", NULL);
    addChildNode((yyval.node), (yyvsp[-2].node));
    addChildNode((yyval.node), (yyvsp[0].node));
    // executeWhile($$);
}
#line 1810 "y.tab.c"
    break;

  case 30: /* for_stmt: FOR ID ASSIGN expr TO expr DO c_stmt_list  */
#line 327 "PWS42X5Y.y"
                                                    {
    (yyval.node) = createNode("for", NULL);
    addChildNode((yyval.node), createNode("id", (yyvsp[-6].id)));
    addChildNode((yyval.node), createNode("range_to", NULL));
    addChildNode((yyval.node), (yyvsp[-4].node));  // start expr
    addChildNode((yyval.node), (yyvsp[-2].node));  // end expr
    addChildNode((yyval.node), (yyvsp[0].node));  // statements
    // executeFor($$);
}
#line 1824 "y.tab.c"
    break;

  case 31: /* for_stmt: FOR ID ASSIGN expr DOWNTO expr DO c_stmt_list  */
#line 336 "PWS42X5Y.y"
                                                {
    (yyval.node) = createNode("for_downto", NULL);
    addChildNode((yyval.node), createNode("id", (yyvsp[-6].id)));
    addChildNode((yyval.node), createNode("range_downto", NULL));
    addChildNode((yyval.node), (yyvsp[-4].node));  // start expr
    addChildNode((yyval.node), (yyvsp[-2].node));  // end expr
    addChildNode((yyval.node), (yyvsp[0].node));  // statements
    // executeFor($$);
}
#line 1838 "y.tab.c"
    break;

  case 32: /* read_stmt: READ LPAREN ID RPAREN SEMICOLON  */
#line 347 "PWS42X5Y.y"
                                           {
    (yyval.node) = createNode("read", (yyvsp[-2].id));
    // executeRead($$);
}
#line 1847 "y.tab.c"
    break;

  case 33: /* read_stmt: READ LPAREN ID LBRACK expr RBRACK RPAREN SEMICOLON  */
#line 351 "PWS42X5Y.y"
                                                     {
    (yyval.node) = createNode("array_read", (yyvsp[-5].id));
    addChildNode((yyval.node), (yyvsp[-3].node));
    // executeRead($$);
}
#line 1857 "y.tab.c"
    break;

  case 34: /* write_stmt: WRITE LPAREN STRING RPAREN SEMICOLON  */
#line 358 "PWS42X5Y.y"
                                                 {
    (yyval.node) = createNode("write_string", (yyvsp[-2].str));
    // executeWrite($$);
}
#line 1866 "y.tab.c"
    break;

  case 35: /* write_stmt: WRITE LPAREN expr RPAREN SEMICOLON  */
#line 362 "PWS42X5Y.y"
                                     {
    (yyval.node) = createNode("write_expr", NULL);
    addChildNode((yyval.node), (yyvsp[-2].node));
    // executeWrite($$);
}
#line 1876 "y.tab.c"
    break;

  case 36: /* write_stmt: WRITE LPAREN w_ID_list RPAREN SEMICOLON  */
#line 367 "PWS42X5Y.y"
                                          {
    (yyval.node) = createNode("write_list", NULL);
    addChildNode((yyval.node), (yyvsp[-2].node));
    // executeWrite($$);
}
#line 1886 "y.tab.c"
    break;

  case 37: /* c_stmt_list: START stmt_list END SEMICOLON  */
#line 374 "PWS42X5Y.y"
                                           {
    (yyval.node) = (yyvsp[-2].node);
}
#line 1894 "y.tab.c"
    break;

  case 38: /* ifelse_stmt_list: START stmt_list END  */
#line 379 "PWS42X5Y.y"
                                      {
    (yyval.node) = (yyvsp[-1].node);
}
#line 1902 "y.tab.c"
    break;

  case 39: /* w_ID_list: ID COMMA w_ID_list  */
#line 384 "PWS42X5Y.y"
                              {
    (yyval.node) = createNode("id_list", NULL);
    addChildNode((yyval.node), createNode("id", (yyvsp[-2].id)));
    ASTNode *child = (yyvsp[0].node);
    while (child) {
        addChildNode((yyval.node), createNode("id", child->value));
        child = child->nextSibling;
    }
}
#line 1916 "y.tab.c"
    break;

  case 40: /* w_ID_list: ID  */
#line 393 "PWS42X5Y.y"
     {
    (yyval.node) = createNode("id_list", NULL);
    addChildNode((yyval.node), createNode("id", (yyvsp[0].id)));
}
#line 1925 "y.tab.c"
    break;

  case 41: /* expr: expr PLUS expr  */
#line 400 "PWS42X5Y.y"
{
    (yyval.node) = createNode("plus", NULL);
    addChildNode((yyval.node), (yyvsp[-2].node));
    addChildNode((yyval.node), (yyvsp[0].node));
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineExprType("+", leftType, rightType);
}
#line 1939 "y.tab.c"
    break;

  case 42: /* expr: expr MINUS expr  */
#line 410 "PWS42X5Y.y"
{
    (yyval.node) = createNode("minus", NULL);
    addChildNode((yyval.node), (yyvsp[-2].node));
    addChildNode((yyval.node), (yyvsp[0].node));
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    (yyval.node)->dtype = determineExprType("-", leftType, rightType);
}
#line 1952 "y.tab.c"
    break;

  case 43: /* expr: expr MUL expr  */
#line 419 "PWS42X5Y.y"
{
    (yyval.node) = createNode("mul", NULL);
    addChildNode((yyval.node), (yyvsp[-2].node));
    addChildNode((yyval.node), (yyvsp[0].node));
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    (yyval.node)->dtype = determineExprType("*", leftType, rightType);
}
#line 1965 "y.tab.c"
    break;

  case 44: /* expr: expr DIV expr  */
#line 428 "PWS42X5Y.y"
{
    (yyval.node) = createNode("div", NULL);
    addChildNode((yyval.node), (yyvsp[-2].node));
    addChildNode((yyval.node), (yyvsp[0].node));
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    (yyval.node)->dtype = determineExprType("/", leftType, rightType);
}
#line 1978 "y.tab.c"
    break;

  case 45: /* expr: expr MOD expr  */
#line 437 "PWS42X5Y.y"
{
    (yyval.node) = createNode("mod", NULL);
    addChildNode((yyval.node), (yyvsp[-2].node));
    addChildNode((yyval.node), (yyvsp[0].node));
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    (yyval.node)->dtype = determineExprType("%", leftType, rightType);
}
#line 1991 "y.tab.c"
    break;

  case 46: /* expr: ID  */
#line 446 "PWS42X5Y.y"
{
    (yyval.node) = createNode("id", (yyvsp[0].id));
    (yyval.node)->dtype = lookupType((yyvsp[0].id));
}
#line 2000 "y.tab.c"
    break;

  case 47: /* expr: NUM  */
#line 451 "PWS42X5Y.y"
{
    (yyval.node) = createNode("num", NULL);
    (yyval.node)->value = malloc(20);
    (yyval.node)->dtype = malloc(20);
    sprintf((yyval.node)->value, "%d", (yyvsp[0].num));
    sprintf((yyval.node)->dtype, "%s", "int");
}
#line 2012 "y.tab.c"
    break;

  case 48: /* expr: REAL_NUM  */
#line 459 "PWS42X5Y.y"
{
    (yyval.node) = createNode("real", NULL);
    (yyval.node)->value = malloc(20);
    (yyval.node)->dtype = malloc(20);
    sprintf((yyval.node)->value, "%f", (yyvsp[0].real));
    sprintf((yyval.node)->dtype, "%s", "real");
}
#line 2024 "y.tab.c"
    break;

  case 49: /* expr: CHAR_CONST  */
#line 467 "PWS42X5Y.y"
{
    (yyval.node) = createNode("char", NULL);
    (yyval.node)->value = malloc(2);
    (yyval.node)->dtype = malloc(20);
    sprintf((yyval.node)->value, "%c", (yyvsp[0].ch));
    sprintf((yyval.node)->dtype, "%s", "char");
}
#line 2036 "y.tab.c"
    break;

  case 50: /* expr: TRUTH  */
#line 475 "PWS42X5Y.y"
{
    (yyval.node) = createNode("boolean", "true");
    (yyval.node)->dtype = malloc(20);
    sprintf((yyval.node)->dtype, "%s", "boolean");
}
#line 2046 "y.tab.c"
    break;

  case 51: /* expr: LIE  */
#line 481 "PWS42X5Y.y"
{
    (yyval.node) = createNode("boolean", "false");
    (yyval.node)->dtype = malloc(20);
    sprintf((yyval.node)->dtype, "%s", "boolean");
}
#line 2056 "y.tab.c"
    break;

  case 52: /* expr: ID LBRACK expr RBRACK  */
#line 487 "PWS42X5Y.y"
{
    int index = checkDeclared((yyvsp[-3].id));
    if (index == -1) {
        fprintf(stderr, "Error: Undeclared array %s\n", (yyvsp[-3].id));
        exit(1);
    }
    if (!symbolTable[index].isArray) {
        fprintf(stderr, "Error: %s is not an array\n", (yyvsp[-3].id));
        exit(1);
    }
    (yyval.node) = createNode("array_access", (yyvsp[-3].id));
    addChildNode((yyval.node), (yyvsp[-1].node));
    (yyval.node)->dtype = lookupType((yyvsp[-3].id));
}
#line 2075 "y.tab.c"
    break;

  case 53: /* expr: LPAREN expr RPAREN  */
#line 502 "PWS42X5Y.y"
{
    (yyval.node) = (yyvsp[-1].node);
}
#line 2083 "y.tab.c"
    break;

  case 54: /* condn: expr EQ expr  */
#line 508 "PWS42X5Y.y"
{ 
    (yyval.node) = createNode("eq", NULL); addChildNode((yyval.node), (yyvsp[-2].node)); addChildNode((yyval.node), (yyvsp[0].node));
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineConditionType("=", leftType, rightType); 
}
#line 2095 "y.tab.c"
    break;

  case 55: /* condn: expr NEQ expr  */
#line 516 "PWS42X5Y.y"
{ 
    (yyval.node) = createNode("neq", NULL); addChildNode((yyval.node), (yyvsp[-2].node)); addChildNode((yyval.node), (yyvsp[0].node));
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineConditionType("!=", leftType, rightType);  
}
#line 2107 "y.tab.c"
    break;

  case 56: /* condn: expr LT expr  */
#line 524 "PWS42X5Y.y"
{ 
    (yyval.node) = createNode("lt", NULL); addChildNode((yyval.node), (yyvsp[-2].node)); addChildNode((yyval.node), (yyvsp[0].node)); 
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineConditionType("<", leftType, rightType); 
}
#line 2119 "y.tab.c"
    break;

  case 57: /* condn: expr GT expr  */
#line 532 "PWS42X5Y.y"
{ 
    (yyval.node) = createNode("gt", NULL); addChildNode((yyval.node), (yyvsp[-2].node)); addChildNode((yyval.node), (yyvsp[0].node)); 
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineConditionType(">", leftType, rightType); 
}
#line 2131 "y.tab.c"
    break;

  case 58: /* condn: expr LE expr  */
#line 540 "PWS42X5Y.y"
{ 
    (yyval.node) = createNode("le", NULL); addChildNode((yyval.node), (yyvsp[-2].node)); addChildNode((yyval.node), (yyvsp[0].node)); 
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineConditionType("<=", leftType, rightType); 
}
#line 2143 "y.tab.c"
    break;

  case 59: /* condn: expr GE expr  */
#line 548 "PWS42X5Y.y"
{ 
    (yyval.node) = createNode("ge", NULL); addChildNode((yyval.node), (yyvsp[-2].node)); addChildNode((yyval.node), (yyvsp[0].node)); 
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineConditionType(">=", leftType, rightType); 
}
#line 2155 "y.tab.c"
    break;

  case 60: /* condn: condn AND condn  */
#line 556 "PWS42X5Y.y"
{ 
    (yyval.node) = createNode("and", NULL); addChildNode((yyval.node), (yyvsp[-2].node)); addChildNode((yyval.node), (yyvsp[0].node));
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineConditionType("&", leftType, rightType);  
}
#line 2167 "y.tab.c"
    break;

  case 61: /* condn: condn OR condn  */
#line 564 "PWS42X5Y.y"
{ 
    (yyval.node) = createNode("or", NULL); addChildNode((yyval.node), (yyvsp[-2].node)); addChildNode((yyval.node), (yyvsp[0].node)); 
    char* leftType = (yyvsp[-2].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineConditionType("|", leftType, rightType); 
}
#line 2179 "y.tab.c"
    break;

  case 62: /* condn: NOT condn  */
#line 572 "PWS42X5Y.y"
{ 
    (yyval.node) = createNode("not", NULL); addChildNode((yyval.node), (yyvsp[0].node)); 
    char* leftType = (yyvsp[0].node)->dtype;
    char* rightType = (yyvsp[0].node)->dtype;
    //printf("%s %s\n", leftType, rightType);
    (yyval.node)->dtype = determineConditionType("!", leftType, rightType); 
}
#line 2191 "y.tab.c"
    break;

  case 63: /* condn: expr  */
#line 580 "PWS42X5Y.y"
{ (yyval.node) = (yyvsp[0].node); }
#line 2197 "y.tab.c"
    break;


#line 2201 "y.tab.c"

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

#line 583 "PWS42X5Y.y"


int checkDeclared(char *name) {
    for (int i = 0; i < symbolTableIndex; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return i; // Found
        }
    }
    return -1; // Not found
}

void addToSymbolTable(char *name, char *type, int size, int isArray) {
    /* printf("Adding %s as %s to table\n", name, type); */
    if (symbolTableIndex >= SYMBOL_TABLE_SIZE) {
        fprintf(stderr, "Error: Symbol table is full.\n");
        exit(1);
    }
    symbolTable[symbolTableIndex].name = strdup(name);
    symbolTable[symbolTableIndex].type = strdup(type);
    symbolTable[symbolTableIndex].declared = 1;
    symbolTable[symbolTableIndex].size = size;
    /* symbolTable[symbolTableIndex].index = 0; */
    symbolTable[symbolTableIndex].isArray = isArray;
    symbolTableIndex++;

    if (isArray) {
        if (strcmp(type, "int") == 0) {
            /* printf("HHHHHHHH\n"); */
            symbolTable[symbolTableIndex].value.arrayValue = (int *)malloc(size * sizeof(int));
        } else if (strcmp(type, "real") == 0) {
            symbolTable[symbolTableIndex].value.arrayValue = (int *)malloc(size * sizeof(float));
        } else if (strcmp(type, "char") == 0) {
            symbolTable[symbolTableIndex].value.arrayValue = (int *)malloc(size * sizeof(char));
        } else if (strcmp(type, "boolean") == 0) {
            symbolTable[symbolTableIndex].value.arrayValue = (int *)malloc(size * sizeof(int));
        }
        if (symbolTable[symbolTableIndex].value.arrayValue == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for array %s\n", name);
            exit(1);
        }
    }
    else {
        if (strcmp(type, "int") == 0) {
            symbolTable[symbolTableIndex].value.intValue = 0;
        } else if (strcmp(type, "real") == 0) {
            symbolTable[symbolTableIndex].value.realValue = 0.0;
        } else if (strcmp(type, "char") == 0) {
            symbolTable[symbolTableIndex].value.charValue = '\0';
        } else if (strcmp(type, "boolean") == 0) {
            symbolTable[symbolTableIndex].value.boolValue = 0;
        }
    }
}

char* lookupType(char *name) {
    int index = checkDeclared(name);
    if (index != -1) return symbolTable[index].type;
    return "undefined"; // Default type if not found
}

char* determineExprType(char* op, char* leftType, char* rightType) {
    if (strcmp(leftType, rightType) != 0) {
        if ((strcmp(leftType, "int") == 0 || strcmp(leftType, "real") == 0) &&
            (strcmp(rightType, "int") == 0 || strcmp(rightType, "real") == 0)) {
            return "real"; // Promote int to real in mixed operations
        }
        fprintf(stderr, "Type mismatch: cannot operate between %s and %s\n", leftType, rightType);
        return "error";
    }
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 || strcmp(op, "*") == 0 || strcmp(op, "/") == 0 || strcmp(op,"%")==0) {
        return leftType; // Assume the operation is valid for the same types
    }
    return "error";
}

char* determineConditionType(char* op, char* leftType, char* rightType) {
    if (strcmp(leftType, rightType) != 0) {
        fprintf(stderr, "Type mismatch: cannot compare %s and %s for condn\n", leftType, rightType);
        return "error";
    }
    else if (strcmp(leftType, rightType) == 0) {
        return "boolean"; 
    }
}

ASTNode* createNode(char* type, char* value) {
    ASTNode* node = (ASTNode*) malloc(sizeof(ASTNode));
    node->type = strdup(type);
    node->value = value ? strdup(value) : NULL;
    node->dtype = NULL;
    node->firstChild = NULL;
    node->nextSibling = NULL;
    return node;
}

void addChildNode(ASTNode* parent, ASTNode* child) {
    if (!parent->firstChild) {
        parent->firstChild = child;
    } else {
        ASTNode* temp = parent->firstChild;
        while (temp->nextSibling) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

void printAST(ASTNode *node, int level, FILE *tree) {
    if (node == NULL) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s", node->type);
    if (node->value) printf(": %s", node->value);
    fprintf(tree,"[%s",node->type);
    printf("\n");
    ASTNode* child = node->firstChild;
    while (child) {
        printAST(child, level + 1, tree);
        child = child->nextSibling;
    }
    fprintf(tree,"]");
}

int evaluateExpr(ASTNode* node)
{
    //printf("hello8\n");
    //printf("hey: -%s-\n", node->type);
    if(strcmp("num",node->type)==0)
    {
        /* printf("numvalue: %d\n", atoi(node->value)); */
        return atoi(node->value);
    }
    else if(strcmp(node->type, "real")==0)
        return (int)atof(node->value);
    else if(strcmp(node->type, "char")==0)
        return (int)node->value[0];
    else if(strcmp(node->type, "boolean")==0)
        return (strcmp(node->value, "1") == 0) ? 1 : 0;
    else if(strcmp(node->type, "id")==0)
    {
        //printf("hello8-1=%s\n", node->value);
        int index = checkDeclared(node->value);
        if(index == -1)
        {
            fprintf(stderr, "Error: Undeclared variable %s\n", node->value);
            exit(1);
        }
        if(symbolTable[index].isArray)
        {
            //printf("hello8-2\n");
            ASTNode* indexNode = node->firstChild;
            int arrayIndex = evaluateExpr(indexNode);
            if (arrayIndex < 0 || arrayIndex >= symbolTable[index].size) {
                fprintf(stderr, "Array index out of bounds\n");
                exit(1);
            }
            return symbolTable[index].value.arrayValue[arrayIndex];
        }
        else {
            if (strcmp(symbolTable[index].type, "int") == 0) {
                //printf("hello8-3\n");
                return symbolTable[index].value.intValue;
            } else if (strcmp(symbolTable[index].type, "real") == 0) {
                return (int)symbolTable[index].value.realValue;
            } else if (strcmp(symbolTable[index].type, "char") == 0) {
                return (int)symbolTable[index].value.charValue;
            } else if (strcmp(symbolTable[index].type, "boolean") == 0) {
                return symbolTable[index].value.boolValue;
            }
        }
    }
    else if(strcmp(node->type, "plus")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return evaluateExpr(left) + evaluateExpr(right);
    }
    else if(strcmp(node->type, "minus")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return evaluateExpr(left) - evaluateExpr(right);
    }
    else if(strcmp(node->type, "mul")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return evaluateExpr(left) * evaluateExpr(right);
    }
    else if(strcmp(node->type, "div")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        int rightValue = evaluateExpr(right);
        if (rightValue == 0) {
            fprintf(stderr, "Error: Division by zero\n");
            exit(1);
        }
        return evaluateExpr(left) / rightValue;
    }
    else if(strcmp(node->type, "mod")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return evaluateExpr(left) % evaluateExpr(right);
    }
    else if(strcmp(node->type, "eq")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return (evaluateExpr(left) == evaluateExpr(right)) ? 1 : 0;
    }
    else if(strcmp(node->type, "neq")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return (evaluateExpr(left) != evaluateExpr(right)) ? 1 : 0;
    }
    else if(strcmp(node->type, "lt")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return (evaluateExpr(left) < evaluateExpr(right)) ? 1 : 0;
    }
    else if(strcmp(node->type, "gt")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return (evaluateExpr(left) > evaluateExpr(right)) ? 1 : 0;
    }
    else if(strcmp(node->type, "le")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return (evaluateExpr(left) <= evaluateExpr(right)) ? 1 : 0;
    }
    else if(strcmp(node->type, "ge")==0)
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return (evaluateExpr(left) >= evaluateExpr(right)) ? 1 : 0;
    }
    else if (strcmp(node->type, "and") == 0) 
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return (evaluateExpr(left) && evaluateExpr(right)) ? 1 : 0;
    }
    else if (strcmp(node->type, "or") == 0) 
    {
        ASTNode* left = node->firstChild;
        ASTNode* right = left->nextSibling;
        return (evaluateExpr(left) || evaluateExpr(right)) ? 1 : 0;
    }   
    else if (strcmp(node->type, "not") == 0) 
    {
        ASTNode* child = node->firstChild;
        return (evaluateExpr(child)) ? 0 : 1;
    }
    
    fprintf(stderr, "Unknown expression type: %s\n", node->type);
    exit(1);
}

void executeIf(ASTNode* node) {
    ASTNode* condNode = node->firstChild;
    ASTNode* thenNode = condNode->nextSibling;
    ASTNode* elseNode = thenNode->nextSibling;

    int condition = evaluateExpr(condNode);

    if (condition) {
        executeStmtList(thenNode);
    } else if (elseNode && strcmp(elseNode->type, "if_else") == 0) {
        executeIf(elseNode);
    } else if (elseNode) {
        executeStmtList(elseNode);
    }
}

void executeWhile(ASTNode *node) 
{
    ASTNode *condNode = node->firstChild;
    ASTNode *bodyNode = condNode->nextSibling;
    while (evaluateExpr(condNode)) {
        executeStmtList(bodyNode);
    }
}

void executeFor(ASTNode* node)
{
    //printf("hello6=%s\n", node->type);
    ASTNode* idNode = node->firstChild;
    //printf("hello6-2=%s\n", idNode->type);
    ASTNode* rangeNode = idNode->nextSibling;
    //printf("hello6-3=%s\n", rangeNode->type);
    if (rangeNode == NULL) {
    fprintf(stderr, "Error: Missing range node in for statement\n");
    exit(1);
    }
    ASTNode* startNode = rangeNode->nextSibling;
    /* printf("hi%s\n", startNode->type); */
    //printf("hello6-5\n");
    ASTNode* endNode = startNode->nextSibling;
    //printf("hello6-6\n");
    ASTNode* stmtListNode = endNode->nextSibling;
    //printf("hello6-7\n");
    int index = checkDeclared(idNode->value);
    if(index == -1)
    {
        fprintf(stderr, "Error: Undeclared variable %s\n", idNode->value);
        exit(1);
    }
    int start = evaluateExpr(startNode);
    int end = evaluateExpr(endNode);
    int step = (strcmp(rangeNode->type, "range_to") == 0) ? 1 : -1;

    symbolTable[index].value.intValue = start;

    for (int i = start; step > 0 ? i <= end : i >= end; i += step)
    {
        symbolTable[index].value.intValue = i;
        executeStmtList(stmtListNode);
    }
}

void executeAssign(ASTNode *node) {
    //printf("hello9\n");
ASTNode *idNode = node->firstChild;
ASTNode *exprNode = idNode->nextSibling;
int index = checkDeclared(idNode->value);
if (index == -1) {
    fprintf(stderr, "Error: Variable %s is not declared.\n", idNode->value);
    return;
}

char *type = symbolTable[index].type;
if (strcmp(type, "int") == 0) {
    symbolTable[index].value.intValue = evaluateExpr(exprNode);
} else if (strcmp(type, "real") == 0) {
    symbolTable[index].value.realValue = evaluateExpr(exprNode);
} else if (strcmp(type, "char") == 0) {
    symbolTable[index].value.charValue = evaluateExpr(exprNode);
} else if (strcmp(type, "boolean") == 0) {
    symbolTable[index].value.boolValue = evaluateExpr(exprNode);
} else if (symbolTable[index].isArray)
{
    ASTNode *indexNode = idNode->nextSibling;
    ASTNode *valueNode = indexNode->nextSibling;
    int arrayIndex = evaluateExpr(indexNode);
    if (arrayIndex < 0 || arrayIndex >= symbolTable[index].size) {
        fprintf(stderr, "Array index out of bounds\n");
        exit(1);
    }
    symbolTable[index].value.arrayValue[arrayIndex] = evaluateExpr(valueNode);
} else {
    fprintf(stderr, "Error: Unsupported data type for variable %s\n", idNode->value);
}
/* symbolTable[index].index++; */
}

void executeRead(ASTNode *node)
{
    /* printf(" \n"); */
char *varName = node->value;
//printf("array name:%s\n", varName);
int index = checkDeclared(varName);
if (index == -1) {
    fprintf(stderr, "Error: Undeclared variable %s\n", varName);
    exit(1);
}
if (symbolTable[index].isArray) {
        ASTNode *indexNode = node->firstChild;
        int arrayIndex = evaluateExpr(indexNode);
        if (arrayIndex < 0 || arrayIndex >= symbolTable[index].size) {
            fprintf(stderr, "Array index out of bounds\n");
            exit(1);
        }
        if (strcmp(symbolTable[index].type, "int") == 0) {
            int val;
            //printf("hello7-2-1\n");
            /* printf("Enter value for %s[%d]: ", varName, arrayIndex); */
            scanf("%d", &val);
            //printf("hello7-2-2=%s\n", symbolTable[index].name);
            symbolTable[index].value.arrayValue[arrayIndex-1] = val;
            //printf("hello7-2-3\n");
        } else if (strcmp(symbolTable[index].type, "real") == 0) {
            float val;
            /* printf("Enter value for %s[%d]: ", varName, arrayIndex); */
            scanf("%f", &val);
            ((float *)symbolTable[index].value.arrayValue)[arrayIndex] = val;
        } else if (strcmp(symbolTable[index].type, "char") == 0) {
            char val;
            /* printf("Enter value for %s[%d]: ", varName, arrayIndex); */
            scanf(" %c", &val);
            ((char *)symbolTable[index].value.arrayValue)[arrayIndex] = val;
        } else if (strcmp(symbolTable[index].type, "boolean") == 0) {
            int val;
            /* printf("Enter value for %s[%d] (0 for false, 1 for true): ", varName, arrayIndex); */
            scanf("%d", &val);
            if (val != 0 && val != 1) {
                fprintf(stderr, "Error: Invalid boolean value for %s[%d]\n", varName, arrayIndex);
                exit(1);
            }
            ((int *)symbolTable[index].value.arrayValue)[arrayIndex] = val;
        }
        /* symbolTable[index].index++; */
    }
else if (strcmp(symbolTable[index].type, "int") == 0) {
    int val;
    /* printf("Enter value for %s: ", varName); */
    scanf("%d", &val);
    symbolTable[index].value.intValue = val;
} else if (strcmp(symbolTable[index].type, "real") == 0) {
    float val;
    /* printf("Enter value for %s: ", varName); */
    scanf("%f", &val);
    symbolTable[index].value.realValue = val;
} else if (strcmp(symbolTable[index].type, "char") == 0) {
    char val;
    /* printf("Enter value for %s: ", varName); */
    scanf(" %c", &val);
    symbolTable[index].value.charValue = val;
} else if (strcmp(symbolTable[index].type, "boolean") == 0) {
    int val;
    /* printf("Enter value for %s (0 for false, 1 for true): ", varName); */
    scanf("%d", &val);
    if (val != 0 && val != 1) {
        fprintf(stderr, "Error: Invalid boolean value for %s\n", varName);
        exit(1);
    }
    symbolTable[index].value.boolValue = val;
} else {
    fprintf(stderr, "Error: Unsupported data type for read statement\n");
    exit(1);
}
}

void executeWrite(ASTNode* node) {
if (strcmp(node->type, "write_string") == 0) {
    printf("%s\n", node->value);
} else if (strcmp(node->type, "write_expr") == 0) {
        ASTNode *exprNode = node->firstChild;
        char *exprType = exprNode->dtype;
        if (strcmp(exprType, "int") == 0) {
            int value = evaluateExpr(exprNode);
            printf("%d", value);
        } else if (strcmp(exprType, "real") == 0) {
            float value = evaluateExpr(exprNode);
            printf("%f", value);
        } else if (strcmp(exprType, "char") == 0) {
            char value = evaluateExpr(exprNode);
            printf("%c", value);
        } else if (strcmp(exprType, "boolean") == 0) {
            int value = evaluateExpr(exprNode);
            printf("%s", value ? "true" : "false");
        }
    } else if (strcmp(node->type, "write_list") == 0) {
    ASTNode *idNode = node->firstChild->firstChild;
    while (idNode != NULL) {
        int index = checkDeclared(idNode->value);
        if (index == -1) {
            fprintf(stderr, "Error: Undeclared variable %s\n", idNode->value);
            exit(1);
        }
        if (symbolTable[index].isArray) {
            for (int i = 0; i < symbolTable[index].size; i++) {
                printf("%d ", symbolTable[index].value.arrayValue[i]);
            }
        } else {
            if (strcmp(symbolTable[index].type, "int") == 0) {
                printf("%d ", symbolTable[index].value.intValue);
            } else if (strcmp(symbolTable[index].type, "real") == 0) {
                printf("%f ", symbolTable[index].value.realValue);
            } else if (strcmp(symbolTable[index].type, "char") == 0) {
                printf("%c ", symbolTable[index].value.charValue);
            } else if (strcmp(symbolTable[index].type, "boolean") == 0) {
                printf("%s ", symbolTable[index].value.boolValue ? "true" : "false");
            }
        }
        idNode = idNode->nextSibling;
    }
    printf("\n");
}
}

void executeProgram(ASTNode* node) {
if (node == NULL) {
    return;
}
//printf("hello1\n");
if (strcmp(node->type, "program") == 0) {
    ASTNode* varDeclSec = node->firstChild;
    ASTNode* block = varDeclSec->nextSibling;

    // Process variable declarations
    executeVarDeclList(varDeclSec->firstChild);

    // Execute statement list
    executeStmtList(block->firstChild);
} else {
    fprintf(stderr, "Error: Expected 'program' node, but found '%s'\n", node->type);
    return;
}
}

void executeVarDeclList(ASTNode* node) {
if (node == NULL) {
    return;
}
//printf("hello2\n");
if (strcmp(node->type, "var_decl_list") == 0) {
    ASTNode* varDecl = node->firstChild;
    while (varDecl) {
        executeVarDecl(varDecl);
        varDecl = varDecl->nextSibling;
    }
} 
/* else if (strcmp(node->type, "var_decl_section") == 0) {
    ASTNode* varDeclList = node->firstChild;
    if (varDeclList) {
        executeVarDeclList(varDeclList);
    }
} */
else {
    fprintf(stderr, "Error: Expected 'var_decl_list' or 'var_decl_section' node, but found '%s'\n", node->type);
}
}

void executeVarDecl(ASTNode* node) {
if (node == NULL) {
    return;
}
/* printf("hello3=%s\n", node->type); */
if (strcmp(node->firstChild->type, "array_decl") == 0) {
        /* ASTNode* idNode = node->firstChild; */
        ASTNode* sizeNode = node->firstChild->firstChild;
        ASTNode* typeNode = sizeNode->nextSibling;
        /* printf("hello3-1=%s\n", node->firstChild->firstChild->nextSibling->value); */
        char *endptr;
        long size = strtol(sizeNode->value, &endptr, 10);
        /* printf("AAAAA%ld\n", size); */
        if (endptr == sizeNode->value || *endptr != '\0' || size <= 0) {
            fprintf(stderr, "Error: Invalid array size: %s\n", sizeNode->value);
            exit(1);
        }
        /* addToSymbolTable(node->firstChild->value, typeNode->value, (int)size, 1); */
    }
    else if (strcmp(node->type, "var_decl") == 0) {
    /* ASTNode* idNode = node->firstChild; */
    ASTNode* typeNode = node->firstChild->firstChild;
    /* printf("hello3-2=%s\n", typeNode->value); */
  //  addToSymbolTable(idNode->value, typeNode->value, 0, 0);
    }
    else {
    fprintf(stderr, "Error: Expected 'var_decl' or 'array_decl' node, but found '%s'\n", node->type);
}
}

void executeStmtList(ASTNode* node) {
if (node == NULL) {
    return;
}
/* printf("hello4\n"); */
if (strcmp(node->type, "stmt_list") == 0) {
    ASTNode* stmt = node->firstChild;
    while (stmt) {
        executeStmt(stmt);
        stmt = stmt->nextSibling;
    }
}
else if (strcmp(node->type, "block") == 0) {
    ASTNode* stmtList = node->firstChild;
    if (stmtList) {
        executeStmtList(stmtList);
    }
} else {
    fprintf(stderr, "Error: Expected 'stmt_list' or 'block' node, but found '%s'\n", node->type);
}
}

void executeStmt(ASTNode* node) {
if (node == NULL) {
    return;
}
/* printf("hello5\n"); */
if (strcmp(node->type, "assign") == 0) {
    executeAssign(node);
} else if (strcmp(node->type, "if") == 0 || strcmp(node->type, "if_else") == 0) {
    executeIf(node);
} else if (strcmp(node->type, "while") == 0) {
    executeWhile(node);
} else if (strcmp(node->type, "for") == 0 || strcmp(node->type, "for_downto") == 0) {
    executeFor(node);
} else if (strcmp(node->type, "read") == 0 || strcmp(node->type, "array_read") == 0) {
    executeRead(node);
} else if (strcmp(node->type, "write_string") == 0 || strcmp(node->type, "write_expr") == 0 || strcmp(node->type, "write_list") == 0) {
    executeWrite(node);
} else {
    fprintf(stderr, "Error: Unknown statement type: %s\n", node->type);
}
}

void printSymbolTable() {
/* printf("Symbol Table:\n"); */
printf("Variable\tType\tValue\tSize\n");
for (int i = 0; i < symbolTableIndex; i++) {
    printf("%s\t\t%s\t", symbolTable[i].name, symbolTable[i].type);
    if (symbolTable[i].isArray) {
        printf("Array\t%d\n", symbolTable[i].size);
    } else {
        if (strcmp(symbolTable[i].type, "int") == 0) {
            printf("%d\t0\n", symbolTable[i].value.intValue);
        } else if (strcmp(symbolTable[i].type, "real") == 0) {
            printf("%f\t0\n", symbolTable[i].value.realValue);
        } else if (strcmp(symbolTable[i].type, "char") == 0) {
            printf("%c\t0\n", symbolTable[i].value.charValue);
        } else if (strcmp(symbolTable[i].type, "boolean") == 0) {
            printf("%s\t0\n", symbolTable[i].value.boolValue ? "true" : "false");
        }
    }
}
}

void freeASTNode(ASTNode* node) {
    if (node == NULL) return;

    free(node->type);
    free(node->value);
    free(node->dtype);

    ASTNode* child = node->firstChild;
    while (child) {
        ASTNode* next = child->nextSibling;
        freeASTNode(child);
        child = next;
    }

    free(node);
}

void freeSymbolTable() {
    for (int i = 0; i < symbolTableIndex; i++) {
        free(symbolTable[i].name);
        free(symbolTable[i].type);
        if (symbolTable[i].isArray) {
            free(symbolTable[i].value.arrayValue);
        }
    }
}

int main(int argc, char *argv[]) {
if (argc != 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
}

FILE *file = fopen(argv[1], "r");
if (file == NULL) {
    fprintf(stderr, "Error: Failed to open input file %s\n", argv[1]);
    return 1;
}

yyin = file;

if (!yyparse()) {
    printf("Parsing Done\n");

    /* printAST(root, 0); */
    printf("\nExecuting program...\n");
    /* printf("%s", root->type); */
    executeProgram(root);
    printf("\nSymbol Table:\n");
    printSymbolTable();
    /* printSymbolTable(); */
} else {
    printf("Parsing Failed\n");
}
/* freeSymbolTable(); */
fclose(file);
return 0;
}
