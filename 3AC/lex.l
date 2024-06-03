%{
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
//using START for BEGIN, TRUTH for true, FALSE for LIE

int lineCount=1;
%}

%%
[Pp][Rr][Oo][Gg][Rr][Aa][Mm]  {return PROGRAM;}
[Ii][Nn][Tt][Ee][Gg][Ee][Rr]  { return INTEGER;}
[Rr][Ee][Aa][Ll]           	{ return REAL;}
[Bb][Oo][Oo][Ll][Ee][Aa][Nn]  { return BOOLEAN;}
[Cc][Hh][Aa][Rr]           	{ return CHAR;}
[Vv][Aa][Rr]              	{return VAR;}
[Tt][Oo]            		{ return TO;}
[Dd][Oo][Ww][Nn][Tt][Oo]      {return DOWNTO;}
[Ii][Ff]             		{ return IF;}
[Ee][Ll][Ss][Ee]           	{ return ELSE;}
[Tt][Hh][Ee][Nn]			{ return THEN;}
[Ww][Hh][Ii][Ll][Ee]          {return WHILE;}
[Ff][Oo][Rr]            	{return FOR;}
[Dd][Oo]              		{return DO;}
[Aa][Rr][Rr][Aa][Yy]          {return ARRAY;}
[Aa][Nn][Dd]            	{return AND;}
[Oo][Rr]            		{return OR;}
[Nn][Oo][Tt]           		{return NOT;}
[Bb][Ee][Gg][Ii][Nn]          {return START;}
[Ee][Nn][Dd]            	{return END;}
[Rr][Ee][Aa][Dd]            	{return READ;}
[Ww][Rr][Ii][Tt][Ee]          {return WRITE;}
[Oo][Ff] 				{return OF;}
[Tt][Rr][Uu][Ee]			{return TRUTH;}
[Ff][Aa][Ll][Ss][Ee]		{return LIE;}

[a-zA-Z_][a-zA-Z0-9_]*    {yylval.strval = strdup(yytext); return ID;}
[-]?[0-9]+                    {yylval.strval = strdup(yytext); return NUM;}
[-]?[0-9]+\.[0-9]+            {yylval.strval = strdup(yytext); return REAL_NUM;}







\"[^\"\n]*\" 		  {
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
				
					yylval.strval = strdup(yytext); 
					return STRING;
					
					}







\'[^\']\'                 { yylval.strval = yytext[1]; return CHAR_CONST;}
":="                      { return ASSIGN;}
"+"                       { return PLUS;}
"-"                       { return MINUS;}
"*"                       { return MUL;}
"/"                       { return DIV;}
"%"                       { return MOD;} 
"="                       { return EQ;}
"<>"                      { return NEQ;}
"<"                       { return LT;}
">"                       { return GT;}
"<="                      { return LE;}
">="                      { return GE;}
"("                       { return LPAREN;}
")"                       { return RPAREN;}
"["                       { return LBRACK;}
"]"                       { return RBRACK;}
":"                       { return COLON;}
";"                       { return SEMICOLON;}
","                       { return COMMA;}
"."                       { return PERIOD;}
\"				  {return DQUOTE;}
\n 				  { lineCount++; }
"//".*                    { }  /* ignore comments check issue */
[ \t]+                  /* ignore whitespace */
.                         {return INVALID;}
%%
