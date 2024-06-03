%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern FILE *yyin;

void yyerror(const char *s);

#define TABLE_SIZE 100

typedef struct Symbol {
    char *identifier;
    struct Symbol *next;
} Symbol;

Symbol* symbolTable[TABLE_SIZE];

unsigned int hash(char *id) {
    unsigned int value = 0;
    for (; *id; ++id) value = value * 65537 + *id;
    return value % TABLE_SIZE;
}

void insertSymbol(char *id) {
    unsigned int index = hash(id);
    Symbol *s = malloc(sizeof(Symbol));
    s->identifier = strdup(id);
    s->next = symbolTable[index];
    symbolTable[index] = s;
}

Symbol* findSymbol(char *id) {
    unsigned int index = hash(id);
    for (Symbol *s = symbolTable[index]; s; s = s->next) {
        if (strcmp(s->identifier, id) == 0) return s;
    }
    return NULL;
}

%}

%token PROGRAM VAR TYPE START_BLOCK END IF THEN ELSE WHILE FOR TO DOWNTO DO READ WRITE ARRAY AND OR NOT OF
%token IDENTIFIER INTEGER REAL PLUS MINUS MULT DIV MOD EQ NEQ LT GT LTE GTE LSQB RSQB
%token SEMICOLON COLON COMMA DOT LPAREN RPAREN ASSIGN STRING_LITERAL

%left PLUS MINUS
%left MULT DIV MOD
%left EQ NEQ LT GT LTE GTE
%right ASSIGN

%%

program
    : PROGRAM IDENTIFIER SEMICOLON declarations START_BLOCK statements END DOT
      { printf("Valid input\n"); }
    ;

declarations
    : VAR declaration_list/* empty */
    ;
    
declaration_list
	: 
	| declaration
	| declaration_list declaration
	;
	
declaration
	: identifier_list COLON TYPE SEMICOLON
	| IDENTIFIER COLON TYPE SEMICOLON
	| IDENTIFIER COLON ARRAY LSQB INTEGER DOT DOT INTEGER RSQB OF TYPE SEMICOLON
	;

identifier_list
    : IDENTIFIER
    | identifier_list COMMA IDENTIFIER
    ;

statements
    : /* empty */
    | statements statement
    ;

statement
    : assignment_statement
    | conditional_statement
    | loop_statement
    | io_statement
    ;

assignment_statement
    : IDENTIFIER ASSIGN expression SEMICOLON
    ;

expression
    : INTEGER
    | REAL
    | IDENTIFIER
    | expression1
    | expression PLUS expression
    | expression MINUS expression
    | expression MULT expression
    | expression DIV expression
    | expression MOD expression
    | expression EQ expression
    | expression NEQ expression
    | expression LT expression
    | expression GT expression
    | expression LTE expression
    | expression GTE expression
    | LPAREN expression RPAREN 
    ;
    
expression1
	: IDENTIFIER
	| IDENTIFIER LSQB expression2 RSQB
	| IDENTIFIER LSQB INTEGER RSQB
	;
	
expression2
	:IDENTIFIER
	|INTEGER
	| IDENTIFIER LSQB expression2 RSQB
	| IDENTIFIER LSQB INTEGER RSQB
	| expression2 PLUS expression2
    | expression2 MINUS expression2
    | expression2 MULT expression2
    | expression2 DIV expression2
    | expression2 MOD expression2
    | LPAREN expression2 RPAREN 
    ;
	
expressionloop
	: IDENTIFIER
	| expression2 EQ expression2
    | expression2 NEQ expression2
    | expression2 LT expression2
    | expression2 GT expression2
    | expression2 LTE expression2
    | expression2 GTE expression2
    | LPAREN expressionloop RPAREN 
    | NOT expressionloop
    | expressionloop AND expressionloop
    | expressionloop OR expressionloop
    ;

conditional_statement
    : IF expressionloop THEN START_BLOCK statements END SEMICOLON
    | IF expressionloop THEN START_BLOCK statements END ELSE START_BLOCK statements END SEMICOLON
    ;

loop_statement
    : WHILE expressionloop DO START_BLOCK statements END SEMICOLON
    | FOR IDENTIFIER ASSIGN expression TO expression DO START_BLOCK statements END SEMICOLON
    | FOR IDENTIFIER ASSIGN expression DOWNTO expression DO START_BLOCK statements END SEMICOLON
    ;

io_statement
    : READ LPAREN expression1 RPAREN SEMICOLON
    | WRITE LPAREN output_list RPAREN SEMICOLON
    | WRITE LPAREN STRING_LITERAL RPAREN SEMICOLON
    ;

output_list
    : expression
    | output_list COMMA expression
    ;

%%

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Could not open file: %s\n", argv[1]);
            return 1;
        }
        yyin = file; // Set the input for the scanner to the file
    } else {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    yyparse();
    fclose(yyin); // Close the file
    return 0;
}


void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}


