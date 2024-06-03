
%{
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

%} 



%union {
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
};

/*
%token <id> ID
%token <num> NUM
%token <real> REAL_NUM
%token <ch> CHAR_CONST */


%token PROGRAM VAR INTEGER REAL BOOLEAN CHAR TO DOWNTO IF ELSE WHILE FOR DO ARRAY AND OR NOT START END READ WRITE ASSIGN PLUS MINUS MUL DIV MOD EQ NEQ LT GT LE GE LPAREN RPAREN LBRACK RBRACK COLON SEMICOLON COMMA PERIOD INVALID OF THEN DQUOTE STRING TRUTH LIE

%token <strval> ID NUM REAL_NUM CHAR_CONST

%left OR
%left AND
%left NOT
%left PLUS MINUS
%left MUL DIV MOD

%type <id> type
%type <id_list> ID_list
//%type <exprt> expr

%type <intval> var_decl_list var_decl stmt_list assign_stmt if_stmt while_stmt for_stmt read_stmt write_stmt c_stmt_list ifelse_stmt_list w_ID_list condn expr stmt begin_end


%%
program: PROGRAM ID SEMICOLON var_decl_section begin_end PERIOD { 

        return 0;
	}
       ;

var_decl_section: VAR var_decl_list | /* empty */
                ;

var_decl_list: var_decl |var_decl_list var_decl 
             ;

var_decl: ID COLON type SEMICOLON
        {
        
        }
	| ID_list COLON type SEMICOLON
        {
        	
        
        }
        | ID COLON ARRAY LBRACK NUM PERIOD PERIOD NUM RBRACK OF type SEMICOLON
        {
            
        }
        ;
        
ID_list: ID COMMA ID_list
        {
      
        }
       | ID
        {
        }
       ;

type: INTEGER {  }
    | REAL {  }
    | BOOLEAN {  }
    | CHAR {  }
    ;

begin_end: START stmt_list END {$$ = $2;}
         ;

stmt_list:  stmt stmt_list{$$ = $1 + $2;}| stmt{$$=$1;}
         ;

stmt: assign_stmt {$$=$1;}
| if_stmt {$$=$1;}
| while_stmt {$$=$1;}
| for_stmt {$$=$1;}
| read_stmt {$$=$1;}
| write_stmt{$$=$1;}
    ;

assign_stmt: ID ASSIGN expr SEMICOLON
            {
		struct TempVar var1 = popFromTempStack();

	    AddCode(OP_ASSIGN, var1.name, NULL, strdup($1));
	    $$ = 1 + $3;
            }
            
            | ID LBRACK expr RBRACK ASSIGN expr SEMICOLON
            {
            	struct TempVar rval2 = popFromTempStack();
	    struct TempVar rval1 = popFromTempStack();

	    char* res = NewTempVar();
	    AddCode(OP_ASSIGN_ADDR, strdup($1), NULL, res);

	    char* res2 = NewTempVar();
	    AddCode(OP_MUL, "4", rval1.name, res2);

	    char* res1 = NewTempVar();
	    AddCode(OP_PLUS, res2, res, res1);
	    AddCode(OP_PTR_ASSIGN, rval2.name, NULL, res1);

	    $$ = $6 + $3 + 4;
            }
           ;

if_stmt: IF condn THEN c_stmt_list {
	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack

    	char* endLabel = NewLabel(nCode-$4+1);
        char* offsetBack = NewLabel(nCode);
        char* goBack = NewLabel(-$4-2);
        AddCodeBefore($4, OP_IF, condResult.name, endLabel, NULL);  // Place conditional jump
        AddCodeBefore($4, OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump
        
        $$ = 2 + $4 ;
} 

| IF condn THEN ifelse_stmt_list ELSE c_stmt_list{
	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack

    	char* endLabel = NewLabel(nCode-$4-$6+1);
        char* offsetBack = NewLabel(nCode-$6);
        char* goBack = NewLabel(-$4-2);
        AddCodeBefore($4+$6, OP_IF, condResult.name, endLabel, NULL);  // Place conditional jump
        AddCodeBefore($4+$6, OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump
        
        $$ = 2 + $4 + $6;
}
       ;

while_stmt: WHILE condn DO c_stmt_list
    {
	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack

    	char* endLabel = NewLabel(nCode-$4+1);
        char* offsetBack = NewLabel(nCode+1);
        char* goBack = NewLabel(-$4-2);
        AddCodeBefore($4, OP_IF, condResult.name, endLabel, NULL);  // Place conditional jump
        AddCodeBefore($4, OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump

        AddCode(OP_GOTO, goBack, NULL, NULL);  // Jump back to the start of the loop
        
        $$ = 3 + $4;
    }
;




for_stmt: FOR ID ASSIGN expr TO expr DO c_stmt_list {
    	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack
    	struct TempVar condResult1 = popFromTempStack();
    	struct TempVar condResult2 = popFromTempStack();
    	//printf("s", condResult.name);

	char* endLabel = NewLabel(nCode-$8+1);
        char* offsetBack = NewLabel(nCode+1);
        char* goBack = NewLabel(-$8-2);

	AddCodeBefore($8, OP_ASSIGN, condResult1.name, NULL, strdup($2));
	
    	
        
        char* res = (char *)malloc(30*sizeof(char));
    	sprintf(res, "%s < %s", strdup($2), condResult.name);
        
        AddCodeBefore($8, OP_IF, res, endLabel, NULL);  // Place conditional jump
        AddCodeBefore($8, OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump
        

        AddCode(OP_GOTO, goBack, NULL, NULL);  // Jump back to the start of the loop
        
        $$ = 3 + $8;
}

 | FOR ID ASSIGN expr DOWNTO expr DO c_stmt_list{
	struct TempVar condResult = popFromTempStack();  // Pop the condition result from the stack
    	struct TempVar condResult1 = popFromTempStack();
	struct TempVar condResult2 = popFromTempStack();
	
    	char* endLabel = NewLabel(nCode-$8+1);
        char* offsetBack = NewLabel(nCode+1);
        char* goBack = NewLabel(-$8-2);
        
        AddCodeBefore($8, OP_ASSIGN, condResult1.name, NULL, strdup($2));
        
        char* res = (char *)malloc(30*sizeof(char));
    	sprintf(res, "%s > %s", strdup($2), condResult.name);
    	
        AddCodeBefore($8, OP_IF, res, endLabel, NULL);  // Place conditional jump
        AddCodeBefore($8, OP_GOTO, offsetBack, NULL, NULL);  // Place conditional jump

        AddCode(OP_GOTO, goBack, NULL, NULL);  // Jump back to the start of the loop
        
        $$ = 3 + $8;
}
        ;

//done
read_stmt: READ LPAREN ID RPAREN SEMICOLON {$$=0;}| READ LPAREN ID LBRACK expr RBRACK RPAREN SEMICOLON {$$=0;}
         ;
//done
write_stmt: WRITE LPAREN STRING RPAREN SEMICOLON {$$=0;}| WRITE LPAREN expr RPAREN SEMICOLON {$$=0;}| WRITE LPAREN w_ID_list RPAREN SEMICOLON{$$=0;}
          ;

c_stmt_list: START stmt_list END SEMICOLON {$$=$2;}
           ;
           
ifelse_stmt_list: START stmt_list END {$$=$2;}
		    ;

w_ID_list: ID COMMA w_ID_list {} | ID COMMA ID {}
       ;


expr: expr PLUS expr {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_PLUS, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
}
| expr MINUS expr {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_MINUS, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
}
| expr MUL expr {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_MUL, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
}
| expr DIV expr {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_DIV, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
}
| expr MOD expr {
    char* res = NewTempVar();
    struct TempVar var1 = popFromTempStack();
    struct TempVar var2 = popFromTempStack();
    AddCode(OP_MOD, var2.name, var1.name, res);
	
    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
}
| NUM {
    pushToTempStack(strdup($1), INT_CONST_TYPE);
    $$ = 0;
}
| ID {
    pushToTempStack(strdup($1), UK_VAR_TYPE);
    $$ = 0;
}
    | REAL_NUM
    {
       pushToTempStack(strdup($1), FLOAT_CONST_TYPE);
    	$$ = 0;
    }
    | CHAR_CONST
    {
    	pushToTempStack(strdup($1), CHAR_CONST_TYPE);
    	$$ = 0;
    }
    | TRUTH
    {
    	
    }
    | LIE
    {

    }
    | ID LBRACK expr RBRACK
    {
    	struct TempVar rval = popFromTempStack();
	    char* res = NewTempVar();
	    AddCode(OP_ASSIGN_ADDR, strdup($1), NULL, res);

	    char* res2 = NewTempVar();
	    AddCode(OP_MUL, "4", rval.name, res2);

	    char* res1 = NewTempVar();
	    AddCode(OP_PLUS, res2, res, res1);
	    // AddCode(OP_PTR_ASSIGN, rval.name, NULL, res1);

	    char temp[10] = "*";
	    strcat(temp, strdup(res1));

	    pushToTempStack(strdup(temp), FLOAT_TYPE);

	    $$ = $3 + 3;
    }
    | LPAREN expr RPAREN
    {
    	$$ = $2;
    }  
    ;

condn: expr EQ expr{
	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s == %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
	}
	
 | expr NEQ expr {
 	//char* res = NewTempVar();
    struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s <> %s", var1.name, var2.name);
    //AddCode(OP_NEQ, var2.name, var1.name, res);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
 	}
 	
 | expr LT expr {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s < %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
 	}
 	
 | expr GT expr {
 	printf("YYY");
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s > %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
 	}
 | expr LE expr {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s <= %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
 	}
 	
 | expr GE expr {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s >= %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
 	}
 	
 | LPAREN condn RPAREN {
 	$$ = $2;
 }
 
 | condn AND condn {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s <> %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
 	}
 	
 | condn OR condn {
 	struct TempVar var2 = popFromTempStack();
    struct TempVar var1 = popFromTempStack();
    char* res = (char *)malloc(30*sizeof(char));
    sprintf(res, "%s <> %s", var1.name, var2.name);

    pushToTempStack(res, var1.type > var2.type ? var1.type : var2.type);
    $$ = 1 + $1 + $3;
 	}
 	
 | NOT condn {
 	struct TempVar un = popFromTempStack();
    char* var = NewTempVar();
    AddCode(OP_NOT, un.name, NULL, var);

    pushToTempStack(var, un.type);
    $$ = 1 + $2;
 	}
 | expr{
 	$$ = $1;
 }
     ;


%%


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

