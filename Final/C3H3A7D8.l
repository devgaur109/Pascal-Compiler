%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
//using START for BEGIN, TRUTH for true, FALSE for LIE

int lineCount=1;
%}

%%
[Pp][Rr][Oo][Gg][Rr][Aa][Mm]  {/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return PROGRAM;}
[Ii][Nn][Tt][Ee][Gg][Ee][Rr]  {/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return INTEGER;}
[Rr][Ee][Aa][Ll]           	{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return REAL;}
[Bb][Oo][Oo][Ll][Ee][Aa][Nn]  {/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return BOOLEAN;}
[Cc][Hh][Aa][Rr]           	{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return CHAR;}
[Vv][Aa][Rr]              	{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return VAR;}
[Tt][Oo]            		{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return TO;}
[Dd][Oo][Ww][Nn][Tt][Oo]      {/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return DOWNTO;}
[Ii][Ff]             		{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return IF;}
[Ee][Ll][Ss][Ee]           	{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return ELSE;}
[Tt][Hh][Ee][Nn]			{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return THEN;}
[Ww][Hh][Ii][Ll][Ee]          {/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return WHILE;}
[Ff][Oo][Rr]            	{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return FOR;}
[Dd][Oo]              		{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return DO;}
[Aa][Rr][Rr][Aa][Yy]          {/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return ARRAY;}
[Aa][Nn][Dd]            	{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return AND;}
[Oo][Rr]            		{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return OR;}
[Nn][Oo][Tt]           		{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return NOT;}
[Bb][Ee][Gg][Ii][Nn]          {/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return START;}
[Ee][Nn][Dd]            	{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return END;}
[Rr][Ee][Aa][Dd]            	{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return READ;}
[Ww][Rr][Ii][Tt][Ee]          {/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return WRITE;}
[Oo][Ff] 				{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext); */return OF;}
[Tt][Rr][Uu][Ee]			{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return TRUTH;}
[Ff][Aa][Ll][Ss][Ee]		{/*printf("%d\t%s\tKEYWORD\n", lineCount, yytext);*/ return LIE;}

[a-zA-Z_][a-zA-Z0-9_]*    {/*printf("%d\t%s\tIDENTIFIER\n", lineCount, yytext);*/ yylval.id = strdup(yytext); return ID;}
[-]?[0-9]+                    {/*printf("%d\t%s\tNUMBERS\n", lineCount, yytext);*/ yylval.num = atoi(yytext); return NUM;}
[-]?[0-9]+\.[0-9]+            {/*printf("%d\t%s\tNUMBERS\n", lineCount, yytext);*/ yylval.real = atof(yytext); return REAL;}







\"[^\"\n]*\" 		  {	/*printf("%d\t\"\tPUNCTUATOR\n", lineCount);*/
					char string_lexeme[1000];
					int len = strlen(yytext);
    
					    // Check if the source string has at least 2 characters
					    if (len >= 2) {
						  // Copy the substring, excluding the first and last characters
						  strncpy(string_lexeme, yytext + 1, len - 2);
						  string_lexeme[len - 2] = '\0'; // Add null terminator
					    } else {
						  // If the source string has fewer than 2 characters, copy an empty string
						  string_lexeme[0] = '\0';
					    }
					/*printf("%d\t%s\tSTRING\n", lineCount, string_lexeme);*/
					/*printf("%d\t\"\tPUNCTUATOR\n", lineCount); */
					yylval.id = strdup(yytext); 
					return STRING;
					
					}







\'[^\']\'                 {/*printf("%d\t%s\tCHARACTER\n", lineCount, yytext); yylval.ch = yytext[1];*/ return CHAR_CONST;}
":="                      {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return ASSIGN;}
"+"                       {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return PLUS;}
"-"                       {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return MINUS;}
"*"                       {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return MUL;}
"/"                       {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return DIV;}
"%"                       {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return MOD;} 
"="                       {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return EQ;}
"<>"                      {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return NEQ;}
"<"                       {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return LT;}
">"                       {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return GT;}
"<="                      {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return LE;}
">="                      {/*printf("%d\t%s\tOPERATOR\n", lineCount, yytext);*/ return GE;}
"("                       {/*printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext);*/ return LPAREN;}
")"                       {/*printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext);*/ return RPAREN;}
"["                       {/*printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext);*/ return LBRACK;}
"]"                       {/*printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext);*/ return RBRACK;}
":"                       {/*printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext);*/ return COLON;}
";"                       {/*printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext);*/ return SEMICOLON;}
","                       {/*printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext);*/ return COMMA;}
"."                       {/*printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext);*/ return PERIOD;}
\"				  {/*printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext);*/ return DQUOTE;}
\n 				  { lineCount++; }
"//".*                    { }  /* ignore comments check issue */
[ \t]+                  /* ignore whitespace */
.                         {printf("Invalid character: %s\n", yytext); return INVALID;}
%%
