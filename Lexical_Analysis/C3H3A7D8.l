%{

#include "y.tab.h"
#include <stdio.h>
int lineno=1;
%}


%%

\n                          { ++lineno; }

[ \t]+                      { /* Skip whitespace. */ }

"//".*                      { /* Skip single-line comments. */ }

[pP][rR][oO][gG][rR][aA][mM]                  { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return PROGRAM; }
[vV][aA][rR]                                   { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return VAR; }
[iI][nN][tT][eE][gG][eE][rR]|[rR][eE][aA][lL]|[bB][oO][oO][lL][eE][aA][nN]|[cC][hH][aA][rR] { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return TYPE; }
[bB][eE][gG][iI][nN]                           { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return START_BLOCK; }
[eE][nN][dD]                                   { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return END; }
[iI][fF]                                       { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return IF; }
[tT][hH][eE][nN]                               { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return THEN; }
[eE][lL][sS][eE]                               { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return ELSE; }
[wW][hH][iI][lL][eE]                           { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return WHILE; }
[fF][oO][rR]                                   { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return FOR; }
[tT][oO]                                       { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return TO; }
[dD][oO][wW][nN][tT][oO]                       { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return DOWNTO; }
[dD][oO]                                       { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return DO; }
[rR][eE][aA][dD]|[rR][eE][aA][dD][lL][nN]                              { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return READ; }
[wW][rR][iI][tT][eE]|[wW][rR][iI][tT][eE][lL][nN]                           { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return WRITE; }
[aA][rR][rR][aA][yY]                           { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return ARRAY; }
[aA][nN][dD]                                   { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return AND; }
[oO][rR]                                       { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return OR; }
[nN][oO][tT]                                   { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return NOT; }
[oO][fF]                                       { printf("%d\t%s\t%s\n", lineno, yytext, "KEYWORD"); return OF; }

[a-zA-Z][a-zA-Z0-9_]*                          { printf("%d\t%s\t%s\n", lineno, yytext, "IDENTIFIER"); return IDENTIFIER; }
[0-9]+                                         { printf("%d\t%s\t%s\n", lineno, yytext, "NUMBER"); return INTEGER; }
[0-9]+"."[0-9]+                                { printf("%d\t%s\t%s\n", lineno, yytext, "NUMBER"); return REAL; }

"+"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "ARITHMETIC OPERATOR"); return PLUS; }
"-"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "ARITHMETIC OPERATOR"); return MINUS; }
"*"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "ARITHMETIC OPERATOR"); return MULT; }
"/"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "ARITHMETIC OPERATOR"); return DIV; }
"%"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "ARITHMETIC OPERATOR"); return MOD; }
":="                                           { printf("%d\t%s\t%s\n", lineno, yytext, "ASSIGNMENT OPERATOR"); return ASSIGN; }
"="                                            { printf("%d\t%s\t%s\n", lineno, yytext, "RELATIONAL OPERATOR"); return EQ; }
"<>"                                           { printf("%d\t%s\t%s\n", lineno, yytext, "RELATIONAL OPERATOR"); return NEQ; }
"<"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "RELATIONAL OPERATOR"); return LT; }
">"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "RELATIONAL OPERATOR"); return GT; }
"<="                                           { printf("%d\t%s\t%s\n", lineno, yytext, "RELATIONAL OPERATOR"); return LTE; }
">="                                           { printf("%d\t%s\t%s\n", lineno, yytext, "RELATIONAL OPERATOR"); return GTE; }

";"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "PUNCTUATOR"); return SEMICOLON; }
":"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "PUNCTUATOR"); return COLON; }
","                                            { printf("%d\t%s\t%s\n", lineno, yytext, "PUNCTUATOR"); return COMMA; }
"."                                            { printf("%d\t%s\t%s\n", lineno, yytext, "PUNCTUATOR"); return DOT; }
"("                                            { printf("%d\t%s\t%s\n", lineno, yytext, "PUNCTUATOR"); return LPAREN; }
")"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "PUNCTUATOR"); return RPAREN; }
"["                                            { printf("%d\t%s\t%s\n", lineno, yytext, "PUNCTUATOR"); return LSQB; }
"]"                                            { printf("%d\t%s\t%s\n", lineno, yytext, "PUNCTUATOR"); return RSQB; }
\"([^"\\]|\\.)*\" {
    printf("%d\t%s\t%s\n", lineno, yytext,"STRING LITERAL");
    return STRING_LITERAL;
}
%%

int yywrap() {
    return 1;
}
