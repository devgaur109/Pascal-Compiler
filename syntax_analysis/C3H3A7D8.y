%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_TABLE_SIZE 100
extern FILE *yyin;
typedef struct {
    char *name;
    char *type;
    int value;
    int size;
} SymbolEntry;

SymbolEntry symbolTable[SYMBOL_TABLE_SIZE];
int symbolTableIndex = 0;

void addToSymbolTable(char *name, char *type, int value, int size);
void printSymbolTable();
%}

%union {
    int num;
    float real;
    char ch;
    char *id;
}

%token <id> ID
%token <num> NUM
%token <real> REAL_NUM
%token <ch> CHAR_CONST
%token PROGRAM VAR INTEGER REAL BOOLEAN CHAR TO DOWNTO IF ELSE WHILE FOR DO ARRAY AND OR NOT START END READ WRITE ASSIGN PLUS MINUS MUL DIV MOD EQ NEQ LT GT LE GE LPAREN RPAREN LBRACK RBRACK COLON SEMICOLON COMMA PERIOD INVALID OF THEN DQUOTE STRING TRUTH LIE

%left OR
%left AND
%left NOT
%left PLUS MINUS
%left MUL DIV MOD

%type <id> type
//%nonassoc IFX

%%
program: PROGRAM ID SEMICOLON var_decl_section begin_end PERIOD { printf("valid input\n"); return 0;}
       ;

var_decl_section: VAR var_decl_list {/*printf("var_decl_section\n");*/}
		    | /* empty */
                ;

var_decl_list: var_decl_list var_decl {/*printf("var_decl_list1\n");*/}
		 | var_decl               {/*printf("var_decl_list2\n");*/}
             ;

var_decl: ID_list COLON type SEMICOLON {/*printf("var_decl 1\n");*/}
	  | ID COLON type SEMICOLON     {/*printf("var_decl 2\n");*/ addToSymbolTable($1, "", 0, 1);}
        | ID COLON ARRAY LBRACK NUM PERIOD PERIOD NUM RBRACK OF type SEMICOLON
        {
        	/*printf("var_decl 3\n");*/
            
        }
        ;

ID_list: ID COMMA ID_list {/*printf("ID_list 1\n");*/ addToSymbolTable($1, "", 0, 1);}
       | ID                {/*printf("ID_list 2\n");*/ addToSymbolTable($1, "", 0, 1);}
       ;

type: INTEGER {$$ = "integer";}
    | REAL {$$ = "real";}
    | BOOLEAN {$$ = "boolean";}
    | CHAR {$$ = "char";}
    ;

begin_end: START stmt_list END {/*printf("begin_end 1\n");*/} //block
	   |
         ;

stmt_list: stmt_list stmt {/*printf("stmt_list_1\n");*/}
	   | stmt           {/*printf("stmt_list_2\n");*/}
         ;


stmt: assign_stmt {/*printf("stmt1\n");*/}
    | if_stmt     {/*printf("stmt2\n");*/}
    | while_stmt  {/*printf("stmt3\n");*/}
    | for_stmt    {/*printf("stmt4\n");*/}
    | read_stmt   {/*printf("stmt5\n");*/}
    | write_stmt   {/*printf("stmt6\n");*/}
    ;

assign_stmt: ID ASSIGN expr SEMICOLON {/*printf("assign_stmt1\n");*/}
           | ID LBRACK expr RBRACK ASSIGN expr SEMICOLON {/*printf("assign_stmt2\n");*/}
           ;


if_stmt: IF condn THEN c_stmt_list  {/*printf("if_stmt1\n");*/}
       | IF condn THEN ifelse_stmt_list ELSE c_stmt_list {/*printf("if_stmt2\n");*/}
       ; 


while_stmt: WHILE condn DO c_stmt_list {/*printf("while_stmt\n");*/}
          ;

for_stmt: FOR ID ASSIGN expr TO expr DO c_stmt_list {/*printf("for_stmt1\n");*/}
        | FOR ID ASSIGN expr DOWNTO expr DO c_stmt_list {/*printf("for_stmt2\n");*/}
        ;

read_stmt: READ LPAREN ID RPAREN SEMICOLON {/*printf("read_stmt1\n");*/}
         | READ LPAREN ID LBRACK expr RBRACK RPAREN SEMICOLON {/*printf("read_stmt2\n");*/}
         ;

write_stmt: WRITE LPAREN STRING RPAREN SEMICOLON {/*printf("write_stmt1\n");*/}
          | WRITE LPAREN expr RPAREN SEMICOLON  {/*printf("write_stmt2\n");*/}
          | WRITE LPAREN w_ID_list RPAREN SEMICOLON  {/*printf("write_stmt3\n");*/}
          ;

c_stmt_list: START stmt_list END SEMICOLON {/*printf("c_stmt_list\n");*/}
           ;
           
ifelse_stmt_list: START stmt_list END {/*printf("c_stmt_list\n");*/}
		    ;
w_ID_list: ID COMMA w_ID_list {/*printf("ID_list 1\n");*/ addToSymbolTable($1, "", 0, 1);}
       | ID COMMA ID           {/*printf("ID_list 2\n");*/ addToSymbolTable($1, "", 0, 1);}
       ;
expr: expr PLUS expr {/*printf("expr1\n");*/}
    | expr MINUS expr {/*printf("expr2\n");*/}
    | expr MUL expr {/*printf("expr3\n");*/}
    | expr DIV expr {/*printf("expr4\n");*/}
    | expr MOD expr  {/*printf("exp5\n");*/}
    | factor {/*printf("expr6\n");*/}
    ; 
    

     
condn: expr EQ expr {/*printf("expr3\n");*/}
     | expr NEQ expr {/*printf("expr4\n");*/}
     | expr LT expr {/*printf("expr5\n");*/}
     | expr GT expr {/*printf("expr6\n");*/}
     | expr LE expr {/*printf("expr7\n");*/}
     | expr GE expr {/*printf("expr8\n");*/}
     | LPAREN condn RPAREN { }
     | condn AND condn
     | condn OR condn
     | NOT condn
     | expr
     ;


factor: NUM   {/*printf("factor1\n");*/}
	| REAL_NUM   {/*printf("factor2\n");*/}
	| CHAR_CONST { }
	| TRUTH { }
	| LIE { }
	| ID     {/*printf("factor3\n");*/}
	| ID LBRACK expr RBRACK    {/*printf("factor4\n");*/}
	| LPAREN expr RPAREN    {/*printf("factor5\n");*/}
      ;

%%

void addToSymbolTable(char *name, char *type, int value, int size) {
    if (symbolTableIndex >= SYMBOL_TABLE_SIZE) {
        printf("Error: Symbol table is full.\n");
        exit(1);
    }
    symbolTable[symbolTableIndex].name = strdup(name);
    symbolTable[symbolTableIndex].type = strdup(type);
    symbolTable[symbolTableIndex].value = value;
    symbolTable[symbolTableIndex].size = size;
    symbolTableIndex++;
}

void printSymbolTable() {
    printf("Symbol Table:\n");
    printf("Variable\tType\tValue\tSize\n");
    for (int i = 0; i < symbolTableIndex; i++) {
        printf("%s\t\t%s\t%d\t%d\n", symbolTable[i].name, symbolTable[i].type, symbolTable[i].value, symbolTable[i].size);
    }
}


int main(int argc, char *argv[]) {
	FILE *file = fopen(argv[1], "r");
	yyin = file;
	if(!yyparse())
	{
		printf("Parsing Done\n");
	}
	else 
		printf("Failed\n");
    	printSymbolTable();
    	fclose(yyin);
    	return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
