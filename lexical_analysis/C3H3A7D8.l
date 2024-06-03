%{
#include <stdio.h>
#include <string.h>

//using START for BEGIN, TRUTH for true, FALSE for LIE

int lineCount=1;
%}

%%
[Pp][Rr][Oo][Gg][Rr][Aa][Mm]  {printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Ii][Nn][Tt][Ee][Gg][Ee][Rr]  {printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Rr][Ee][Aa][Ll]           	{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Bb][Oo][Oo][Ll][Ee][Aa][Nn]  {printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Cc][Hh][Aa][Rr]           	{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Vv][Aa][Rr]              	{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Tt][Oo]            		{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Dd][Oo][Ww][Nn][Tt][Oo]      {printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Ii][Ff]             		{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Ee][Ll][Ss][Ee]           	{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Tt][Hh][Ee][Nn]			{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Ww][Hh][Ii][Ll][Ee]          {printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Ff][Oo][Rr]            	{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Dd][Oo]              		{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Aa][Rr][Rr][Aa][Yy]          {printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Aa][Nn][Dd]            	{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Oo][Rr]            		{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Nn][Oo][Tt]           		{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Bb][Ee][Gg][Ii][Nn]          {printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Ee][Nn][Dd]            	{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Rr][Ee][Aa][Dd]            	{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Ww][Rr][Ii][Tt][Ee]          {printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Oo][Ff] 				{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Tt][Rr][Uu][Ee]			{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }
[Ff][Aa][Ll][Ss][Ee]		{printf("%d\t%s\tKEYWORD\n", lineCount, yytext); }

[a-zA-Z_][a-zA-Z0-9_]*    {printf("%d\t%s\tIDENTIFIER\n", lineCount, yytext);  }
[-]?[0-9]+                    {printf("%d\t%s\tNUMBERS\n", lineCount, yytext);  }
[-]?[0-9]+\.[0-9]+            {printf("%d\t%s\tNUMBERS\n", lineCount, yytext);  }







\"[^\"\n]*\" 		  {	printf("%d\t\"\tPUNCTUATOR\n", lineCount);
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
					printf("%d\t%s\tSTRING\n", lineCount, string_lexeme);
					printf("%d\t\"\tPUNCTUATOR\n", lineCount); 
					 
					
					
					}







\'[^\']\'                 {printf("%d\t%s\tCHARACTER\n", lineCount, yytext);  }
":="                      {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
"+"                       {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
"-"                       {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
"*"                       {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
"/"                       {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
"%"                       {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); } 
"="                       {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
"<>"                      {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
"<"                       {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
">"                       {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
"<="                      {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
">="                      {printf("%d\t%s\tOPERATOR\n", lineCount, yytext); }
"("                       {printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext); }
")"                       {printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext); }
"["                       {printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext); }
"]"                       {printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext); }
":"                       {printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext); }
";"                       {printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext); }
","                       {printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext); }
"."                       {printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext); }
\"				  {printf("%d\t%s\tPUNCTUATOR\n", lineCount, yytext); }
\n 				  { lineCount++; }
"//".*                    { }  /* ignore comments check issue */
[ \t]+                  /* ignore whitespace */
.                         {printf("Invalid character: %s\n", yytext); }
%%

int yywrap(){

    return 1;

}

int main(int argc, char *argv[]) {
	FILE *file = fopen(argv[1], "r");
	yyin = file;
	yylex();
    	fclose(yyin);
    	return 0;
}


