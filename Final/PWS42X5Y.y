%{
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
    // executeProgram($$);
}
;

var_decl_section: VAR var_decl_list
{
    $$ = createNode("var_decl_section", NULL);
    addChildNode($$, $2);
    // executeVarDeclList($2);
} | /* empty */ {
    $$ = NULL;
}
;

var_decl_list: var_decl {
    $$ = createNode("var_decl_list", NULL);
    addChildNode($$, $1);
    // executeVarDecl($1);
} 
| var_decl_list var_decl {
    if ($1 == NULL) {
        $$ = $2;
    } else {
        addChildNode($1, $2);
        $$ = $1;
    }
    // executeVarDecl($2);
}
;

var_decl: ID COLON type SEMICOLON
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
    ASTNode *typeNode = createNode("type", $3);
    for (int i = 0; i < $1.count; i++) {
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
        addToSymbolTable($1, $11, size, 1); // For arrays, provide size information
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
    // executeStmtList($2);
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
    // executeStmt($2);
}
| stmt {
    $$ = createNode("stmt_list", NULL);
    addChildNode($$, $1);
    // executeStmt($1);
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
    // executeAssign($$);
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
    // executeAssign($$);
}
;

if_stmt: IF condn THEN c_stmt_list {
    $$ = createNode("if", NULL);
    addChildNode($$, $2);
    addChildNode($$, $4);
    // executeIf($$);
}
| IF condn THEN ifelse_stmt_list ELSE c_stmt_list {
    $$ = createNode("if_else", NULL);
    addChildNode($$, $2);
    addChildNode($$, $4);
    addChildNode($$, $6);
    // executeIf($$);
}
;

while_stmt: WHILE condn DO c_stmt_list {
    $$ = createNode("while", NULL);
    addChildNode($$, $2);
    addChildNode($$, $4);
    // executeWhile($$);
}
;

for_stmt: FOR ID ASSIGN expr TO expr DO c_stmt_list {
    $$ = createNode("for", NULL);
    addChildNode($$, createNode("id", $2));
    addChildNode($$, createNode("range_to", NULL));
    addChildNode($$, $4);  // start expr
    addChildNode($$, $6);  // end expr
    addChildNode($$, $8);  // statements
    // executeFor($$);
}
| FOR ID ASSIGN expr DOWNTO expr DO c_stmt_list {
    $$ = createNode("for_downto", NULL);
    addChildNode($$, createNode("id", $2));
    addChildNode($$, createNode("range_downto", NULL));
    addChildNode($$, $4);  // start expr
    addChildNode($$, $6);  // end expr
    addChildNode($$, $8);  // statements
    // executeFor($$);
}
;

read_stmt: READ LPAREN ID RPAREN SEMICOLON {
    $$ = createNode("read", $3);
    // executeRead($$);
}
| READ LPAREN ID LBRACK expr RBRACK RPAREN SEMICOLON {
    $$ = createNode("array_read", $3);
    addChildNode($$, $5);
    // executeRead($$);
}
;

write_stmt: WRITE LPAREN STRING RPAREN SEMICOLON {
    $$ = createNode("write_string", $3);
    // executeWrite($$);
}
| WRITE LPAREN expr RPAREN SEMICOLON {
    $$ = createNode("write_expr", NULL);
    addChildNode($$, $3);
    // executeWrite($$);
}
| WRITE LPAREN w_ID_list RPAREN SEMICOLON {
    $$ = createNode("write_list", NULL);
    addChildNode($$, $3);
    // executeWrite($$);
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
{
    $$ = createNode("plus", NULL);
    addChildNode($$, $1);
    addChildNode($$, $3);
    char* leftType = $1->dtype;
    char* rightType = $3->dtype;
    //printf("%s %s\n", leftType, rightType);
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
    $$->dtype = lookupType($1);
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
    //printf("%s %s\n", leftType, rightType);
    $$->dtype = determineConditionType("=", leftType, rightType); 
}
| expr NEQ expr   
{ 
    $$ = createNode("neq", NULL); addChildNode($$, $1); addChildNode($$, $3);
    char* leftType = $1->dtype;
    char* rightType = $3->dtype;
    //printf("%s %s\n", leftType, rightType);
    $$->dtype = determineConditionType("!=", leftType, rightType);  
}
| expr LT expr    
{ 
    $$ = createNode("lt", NULL); addChildNode($$, $1); addChildNode($$, $3); 
    char* leftType = $1->dtype;
    char* rightType = $3->dtype;
    //printf("%s %s\n", leftType, rightType);
    $$->dtype = determineConditionType("<", leftType, rightType); 
}
| expr GT expr    
{ 
    $$ = createNode("gt", NULL); addChildNode($$, $1); addChildNode($$, $3); 
    char* leftType = $1->dtype;
    char* rightType = $3->dtype;
    //printf("%s %s\n", leftType, rightType);
    $$->dtype = determineConditionType(">", leftType, rightType); 
}
| expr LE expr    
{ 
    $$ = createNode("le", NULL); addChildNode($$, $1); addChildNode($$, $3); 
    char* leftType = $1->dtype;
    char* rightType = $3->dtype;
    //printf("%s %s\n", leftType, rightType);
    $$->dtype = determineConditionType("<=", leftType, rightType); 
}
| expr GE expr    
{ 
    $$ = createNode("ge", NULL); addChildNode($$, $1); addChildNode($$, $3); 
    char* leftType = $1->dtype;
    char* rightType = $3->dtype;
    //printf("%s %s\n", leftType, rightType);
    $$->dtype = determineConditionType(">=", leftType, rightType); 
}
| condn AND condn 
{ 
    $$ = createNode("and", NULL); addChildNode($$, $1); addChildNode($$, $3);
    char* leftType = $1->dtype;
    char* rightType = $3->dtype;
    //printf("%s %s\n", leftType, rightType);
    $$->dtype = determineConditionType("&", leftType, rightType);  
}
| condn OR condn  
{ 
    $$ = createNode("or", NULL); addChildNode($$, $1); addChildNode($$, $3); 
    char* leftType = $1->dtype;
    char* rightType = $3->dtype;
    //printf("%s %s\n", leftType, rightType);
    $$->dtype = determineConditionType("|", leftType, rightType); 
}
| NOT condn       
{ 
    $$ = createNode("not", NULL); addChildNode($$, $2); 
    char* leftType = $2->dtype;
    char* rightType = $2->dtype;
    //printf("%s %s\n", leftType, rightType);
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
