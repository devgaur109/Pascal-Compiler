%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_TABLE_SIZE 1000

int yylex();
extern FILE *yyin;
// extern FILE *tree;

// typedef struct ASTNode {
//     char *type;
//     char *value;
//     struct ASTNode *firstChild;
//     struct ASTNode *nextSibling;
// } ASTNode;
typedef struct ASTNodeCopy {
        char *type;
        char *value;
        char *dtype;
        struct ASTNodeCopy *firstChild;
        struct ASTNodeCopy *nextSibling;
    } ASTNodeCopy;
    ASTNodeCopy* root;
typedef struct {
    char *name;
    char *type;
    int declared;
    int referenced;
    int size;
    int isArray;
} SymbolEntry;
SymbolEntry symbolTable[SYMBOL_TABLE_SIZE];
int symbolTableIndex = 0;

void addToSymbolTable(char *name, char *type, int size, int isArray);
int checkDeclared(char *name);
void markReferenced(char *name);
char* lookupType(char *name);
char* determineExprType(char* op, char* leftType, char* rightType);
void printSymbolTable();
// ASTNode* createNode(char* type, char* value);
// void addChildNode(ASTNode* parent, ASTNode* child);
// void printAST(ASTNode *node, int level);

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
%}


%code requires {
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
}

%union {
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
}

%token <id> ID
%token <num> NUM
%token <real> REAL_NUM
%token <ch> CHAR_CONST
%token <str> STRING
%token PROGRAM VAR INTEGER REAL BOOLEAN CHAR TO DOWNTO IF ELSE WHILE FOR DO ARRAY AND OR NOT START END READ WRITE ASSIGN PLUS MINUS MUL DIV MOD EQ NEQ LT GT LE GE LPAREN RPAREN LBRACK RBRACK COLON SEMICOLON COMMA PERIOD INVALID OF THEN DQUOTE TRUTH LIE

%left ASSIGN
%left OR
%left AND
%left NOT
%left PLUS MINUS
%left MUL DIV MOD

%type <id> type
%type <id_list> ID_list
%type <node> expr
%type <node> program var_decl_section var_decl_list var_decl begin_end stmt_list stmt assign_stmt if_stmt while_stmt for_stmt read_stmt write_stmt c_stmt_list ifelse_stmt_list w_ID_list condn



%%
program: PROGRAM ID SEMICOLON var_decl_section begin_end PERIOD {
    root = $$ = createNode("program", $2);
    addChildNode($$, $4);
    addChildNode($$, $5);
}
;

var_decl_section: VAR var_decl_list
{
	$$ = createNode("var_decl_section", NULL);
    	addChildNode($$, $2);
} | /* empty */ {
	$$ = NULL;
}
                ;

var_decl_list: var_decl {
    $$ = createNode("var_decl_list", NULL);
    addChildNode($$, $1);
} 
|var_decl_list var_decl {
    if ($1 == NULL) {
        $$ = $2;
    } else {
        addChildNode($1, $2);
        $$ = $1;
    }
}
             ;

var_decl:ID COLON type SEMICOLON //claude
    {
        if (checkDeclared($1) != -1) {
            fprintf(stderr, "Multiple declarations of variable %s\n", $1);
        } else {
            addToSymbolTable($1, $3, 0, 0);
        }
            $$ = createNode("var_decl", NULL);
            ASTNode *varNode = createNode("variable", $1);
            ASTNode *typeNode = createNode("type", $3);
            addChildNode(varNode, typeNode);
            addChildNode($$, varNode);
    }
        | ID_list COLON type SEMICOLON
        {
            $$ = createNode("var_decl", NULL);
            for (int i = 0; i < $1.count; i++) {
                ASTNode *typeNode = createNode("type", $3);
                ASTNode *varNode = createNode("variable", $1.ids[i]);
                addChildNode(varNode, typeNode);
                addChildNode($$, varNode);
                if (checkDeclared($1.ids[i]) != -1) {
                    fprintf(stderr, "Multiple declarations of variable %s\n", $1.ids[i]);
                } else {
        
                    addToSymbolTable($1.ids[i], $3, 0, 0);
                }
            }
        }
        | ID COLON ARRAY LBRACK NUM PERIOD PERIOD NUM RBRACK OF type SEMICOLON
        {
            if (checkDeclared($1) != -1) {
                fprintf(stderr, "Multiple declarations of variable %s\n", $1);
            } else {
                int size = $8 - $5 + 1; // Calculate array size
                addToSymbolTable($1, $11, size,1); // For arrays, provide size information
            }
            $$ = createNode("var_decl", NULL);
            ASTNode *arrNode = createNode("array_decl", $1);
            addChildNode($$, arrNode);
            ASTNode *sizeNode = createNode("size", NULL);
            sizeNode->value = malloc(20);
            sprintf(sizeNode->value, "%d", $8 - $5 + 1);
            addChildNode(arrNode, sizeNode);
            addChildNode(arrNode, createNode("type", $11));
        }
        ;

ID_list: ID COMMA ID_list
        {
            if ($3.ids == NULL) {
                yyerror("Memory allocation failed");
                exit(1);
            }
            $$.ids = (char **) malloc(sizeof(char *) * ($3.count + 1));
            if ($$.ids == NULL) {
                yyerror("Memory allocation failed");
                exit(1);
            }
            $$.ids[0] = $1;
            if ($$.ids[0] == NULL) {
                yyerror("Memory allocation failed");
                exit(1);
            }
            for (int i = 0; i < $3.count; i++) {
                $$.ids[i+1] = $3.ids[i];
            }
            $$.count = $3.count + 1;
        }
       | ID
        {
            $$.ids = (char **) malloc(sizeof(char *));
            if ($$.ids == NULL) {
                yyerror("Memory allocation failed");
                exit(1);
            }
            $$.ids[0] = strdup($1);
            if ($$.ids[0] == NULL) {
                yyerror("Memory allocation failed");
                exit(1);
            }
            $$.count = 1;
        }
       ;


type: INTEGER { $$ = "int"; }
    | REAL { $$ = "real"; }
    | BOOLEAN { $$ = "boolean"; }
    | CHAR { $$ = "char"; }
    ;
begin_end: START stmt_list END {
    $$ = createNode("block", NULL);
    addChildNode($$, $2);
}
;

stmt_list: stmt_list stmt {
    if ($1 == NULL) {
        $$ = createNode("stmt_list", NULL);
        addChildNode($$, $2);
    } else {
        addChildNode($1, $2);
        $$ = $1;
    }
}
| stmt {
    $$ = createNode("stmt_list", NULL);
    addChildNode($$, $1);
}

         ;

stmt: assign_stmt { $$ = $1; }
    | if_stmt { $$ = $1; }
    | while_stmt { $$ = $1; }
    | for_stmt { $$ = $1; }
    | read_stmt { $$ = $1; }
    | write_stmt { $$ = $1; }
    ;

assign_stmt: ID ASSIGN expr SEMICOLON
            {
                $$ = createNode("assign", NULL);
                addChildNode($$, createNode("id", $1));
                addChildNode($$, $3);
                char* idType = lookupType($1);
                char* exprType = $3->dtype; // Assuming expr nodes carry type as value
                if (strcmp(idType, "undefined") == 0) {
                    fprintf(stderr, "Variable is not declared\n");
                } else if (strcmp(idType, exprType) != 0) {
                    fprintf(stderr, "Type error: Cannot assign %s to %s\n", exprType, idType);
                }
            }
            | ID LBRACK expr RBRACK ASSIGN expr SEMICOLON
            {
            	$$ = createNode("array_assign", NULL);
    addChildNode($$, createNode("id", $1));
    addChildNode($$, $3); // index
    addChildNode($$, $6); // value
    char* arrayType = lookupType($1);
    char* assignType = $6->dtype; // Assuming expr nodes carry type as value
    if (arrayType == NULL || strcmp(arrayType, "undefined") == 0) {
        fprintf(stderr, "Error: Undeclared array %s\n", $1);
    }
    else if (strcmp(arrayType, assignType) != 0) {
        fprintf(stderr, "Type mismatch: Cannot assign %s to %s\n", assignType, arrayType);
    }
            }
           ;

if_stmt: IF condn THEN c_stmt_list {
    $$ = createNode("if", NULL);
    addChildNode($$, $2);
    addChildNode($$, $4);
}
| IF condn THEN ifelse_stmt_list ELSE c_stmt_list {
    $$ = createNode("if_else", NULL);
    addChildNode($$, $2);
    addChildNode($$, $4);
    addChildNode($$, $6);
}
;

while_stmt: WHILE condn DO c_stmt_list {
    $$ = createNode("while", NULL);
    addChildNode($$, $2);
    addChildNode($$, $4);
}
;

for_stmt: FOR ID ASSIGN expr TO expr DO c_stmt_list {
    $$ = createNode("for", NULL);
    addChildNode($$, createNode("id", $2));
    addChildNode($$, createNode("range_to", NULL));
    addChildNode($$, $4);  // start expr
    addChildNode($$, $6);  // end expr
    addChildNode($$, $8);  // statements
}
| FOR ID ASSIGN expr DOWNTO expr DO c_stmt_list {
    $$ = createNode("for_downto", NULL);
    addChildNode($$, createNode("id", $2));
    addChildNode($$, createNode("range_downto", NULL));
    addChildNode($$, $4);  // start expr
    addChildNode($$, $6);  // end expr
    addChildNode($$, $8);  // statements
}
;

read_stmt: READ LPAREN ID RPAREN SEMICOLON {
    $$ = createNode("read", $3);
}
| READ LPAREN ID LBRACK expr RBRACK RPAREN SEMICOLON {
    $$ = createNode("array_read", $3);
    addChildNode($$, $5);
}
;

write_stmt: WRITE LPAREN STRING RPAREN SEMICOLON {
    $$ = createNode("write_string", $3);
}
| WRITE LPAREN expr RPAREN SEMICOLON {
    $$ = createNode("write_expr", NULL);
    addChildNode($$, $3);
}
| WRITE LPAREN w_ID_list RPAREN SEMICOLON {
    $$ = createNode("write_list", NULL);
    addChildNode($$, $3);
}
;

c_stmt_list: START stmt_list END SEMICOLON {
    $$ = $2;
}
;

ifelse_stmt_list: START stmt_list END {
    $$ = $2;
}
;

w_ID_list: ID COMMA w_ID_list {
    $$ = createNode("id_list", NULL);
    addChildNode($$, createNode("id", $1));
    ASTNode *child = $3;
    while (child) {
        addChildNode($$, createNode("id", child->value));
        child = child->nextSibling;
    }
}
| ID {
    $$ = createNode("id_list", NULL);
    addChildNode($$, createNode("id", $1));
}
;

expr: expr PLUS expr
    {//
        $$ = createNode("plus", NULL);
    	addChildNode($$, $1);
    	addChildNode($$, $3);
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineExprType("+", leftType, rightType);
    }
    | expr MINUS expr
    {
        $$ = createNode("minus", NULL);
    	addChildNode($$, $1);
    	addChildNode($$, $3);
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        $$->dtype = determineExprType("-", leftType, rightType);
    }
    | expr MUL expr
    {
        $$ = createNode("mul", NULL);
    	addChildNode($$, $1);
    	addChildNode($$, $3);
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        $$->dtype = determineExprType("*", leftType, rightType);
    }
    | expr DIV expr
    {
        $$ = createNode("div", NULL);
    	addChildNode($$, $1);
    	addChildNode($$, $3);
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        $$->dtype = determineExprType("/", leftType, rightType);
    }
    | expr MOD expr
    {
    	$$ = createNode("mod", NULL);
    	addChildNode($$, $1);
    	addChildNode($$, $3);
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        $$->dtype = determineExprType("%", leftType, rightType);
    }
    | ID
    {
        $$ = createNode("id", $1);
        $$->dtype = lookupType($1); //changed to value
    }
    | NUM
    {
        $$ = createNode("num", NULL);
        $$->value = malloc(20);
        $$->dtype = malloc(20);
        sprintf($$->value, "%d", $1);
        sprintf($$->dtype, "%s", "int");
    }
    | REAL_NUM
    {
        $$ = createNode("real", NULL);
        $$->value = malloc(20);
        $$->dtype = malloc(20);
        sprintf($$->value, "%f", $1);
        sprintf($$->dtype, "%s", "real");
    }
    | CHAR_CONST
    {
    	$$ = createNode("char", NULL);
        $$->value = malloc(2);
        $$->dtype = malloc(20);
        sprintf($$->value, "%c", $1);
        sprintf($$->dtype, "%s", "char");
    }
    | TRUTH
    {
    	$$ = createNode("boolean", "true");
        $$->dtype = malloc(20);
        sprintf($$->dtype, "%s", "boolean");
    }
    | LIE
    {
    	$$ = createNode("boolean", "false");
        $$->dtype = malloc(20);
        sprintf($$->dtype, "%s", "boolean");
    }
    | ID LBRACK expr RBRACK
    {
    	int index = checkDeclared($1);
    	if (index == -1) {
            fprintf(stderr, "Error: Undeclared array %s\n", $1);
            exit(1);
        }
        if (!symbolTable[index].isArray) {
            fprintf(stderr, "Error: %s is not an array\n", $1);
            exit(1);
        }
        $$ = createNode("array_access", $1);
        addChildNode($$, $3);
        $$->dtype = lookupType($1);
    }
    | LPAREN expr RPAREN
    {
    	$$ = $2;
    }  
    ;

condn: expr EQ expr    
    { 
        $$ = createNode("eq", NULL); addChildNode($$, $1); addChildNode($$, $3);
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineConditionType("=", leftType, rightType); 
    }
    | expr NEQ expr   
    { 
        $$ = createNode("neq", NULL); addChildNode($$, $1); addChildNode($$, $3);
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineConditionType("!=", leftType, rightType);  
    }
    | expr LT expr    
    { 
        $$ = createNode("lt", NULL); addChildNode($$, $1); addChildNode($$, $3); 
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineConditionType("<", leftType, rightType); 
    }
    | expr GT expr    
    { 
        $$ = createNode("gt", NULL); addChildNode($$, $1); addChildNode($$, $3); 
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineConditionType(">", leftType, rightType); 
    }
    | expr LE expr    
    { 
        $$ = createNode("le", NULL); addChildNode($$, $1); addChildNode($$, $3); 
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineConditionType("<=", leftType, rightType); 
    }
    | expr GE expr    
    { 
        $$ = createNode("ge", NULL); addChildNode($$, $1); addChildNode($$, $3); 
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineConditionType(">=", leftType, rightType); 
    }
//     | LPAREN condn RPAREN { $$ = $2; }
    | condn AND condn 
    { 
        $$ = createNode("and", NULL); addChildNode($$, $1); addChildNode($$, $3);
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineConditionType("&", leftType, rightType);  
    }
    | condn OR condn  
    { 
        $$ = createNode("or", NULL); addChildNode($$, $1); addChildNode($$, $3); 
        char* leftType = $1->dtype;
        char* rightType = $3->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineConditionType("|", leftType, rightType); 
    }
    | NOT condn       
    { 
        $$ = createNode("not", NULL); addChildNode($$, $2); 
        char* leftType = $2->dtype;
        char* rightType = $2->dtype;
        printf("%s %s\n", leftType, rightType);
        $$->dtype = determineConditionType("!", leftType, rightType); 
    }
    | expr      
    { $$ = $1; }
    ;


%%

int checkDeclared(char *name) {
    for (int i = 0; i < symbolTableIndex; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            return i; // Found
        }
    }
    return -1; // Not found
}

void addToSymbolTable(char *name, char *type, int size, int isArray) {
	printf("Adding %s as %s to table\n", name, type);
    if (symbolTableIndex >= SYMBOL_TABLE_SIZE) {
        fprintf(stderr, "Error: Symbol table is full.\n");
        exit(1);
    }
    symbolTable[symbolTableIndex].name = strdup(name);
    symbolTable[symbolTableIndex].type = strdup(type);
    symbolTable[symbolTableIndex].declared = 1;
    symbolTable[symbolTableIndex].size = size;
    symbolTable[symbolTableIndex].isArray = isArray;
    symbolTableIndex++;
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
    fprintf(tree, "[%s", node->type);
    printf("\n");

    ASTNode* child = node->firstChild;
    if (child) {
        while (child) {
            printAST(child, level + 1, tree);
            child = child->nextSibling;
        }
    } else {
        if (node->value) fprintf(tree, "[%s]", node->value);
    }

    fprintf(tree, "]");
}

void freeAST(ASTNode *node) {
    if (node == NULL) return;

    // Free the memory of child nodes recursively
    ASTNode *child = node->firstChild;
    while (child) {
        ASTNode *next = child->nextSibling;
        freeAST(child);
        child = next;
    }

    // Free the memory of the current node
    if (node->type) free(node->type);
    if (node->value) free(node->value);
    free(node);
}


void printSymbolTable() {
    printf("Symbol Table:\n");
    printf("Variable\tType\tValue\tSize\n");
    for (int i = 0; i < symbolTableIndex; i++) {
        printf("%s\t\t%s\t%d\n", symbolTable[i].name, symbolTable[i].type, symbolTable[i].size);
    }
}
int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");
    yyin = file;
    /* ASTNode *root = NULL; */
    FILE *tree=fopen("parse.txt", "w+");
    if (!yyparse()) {
        printf("Parsing Done\n");
        printf("Abstract Syntax Tree:\n");
        /* printf("AAAAAAAAA"); */
        printAST(root, 0, tree);
        printf("\n\n\n");
        /* dfs(root); */
        /* freeAST(root); */
        /* printSymbolTable(); */
    } else {
        printf("Parsing Failed\n");
    }
    fclose(yyin);
    fclose(tree);
    
    return 0;
}
