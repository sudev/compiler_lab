%{
#include <stdlib.h>
#include "y.tab.h"

#define EQ	0
#define GE	2
#define NE	3
#define LT	4
#define LE	1
#define GT	5

#define TRUE	1
#define FALSE	0

extern YYSTYPE yylval;

%}

int 		[0-9]+
alphabet 	[a-zA-Z]
id 		[a-zA-Z_][{alphabet}|{int}|_]*
mathopr 	[\-+\*\/\%]
logopr		NOT|AND|OR
extras		\;|\{|\}|\(|\)|\,|\[|\]|=
relop		
%%

"end"		{return END;}
"decl"		{return DECL;}
"enddecl"	{return ENDDECL;}
"integer"	{return INTEGERE;}
"boolean"	{return BOOLEANE;}
"main"		{return MAIN;}
"begin"		{return BEG;}
"else"		{return ELSE;}
"if"		{return IF;}
"then"		{return THEN;}
"while"		{return WHILE;}
"endif"		{return ENDIF;}
"return"	{return RETURN;}
"do"		{return DO;}
"read"		{return READ;}
"write"		{return WRITE;}	
"endwhile"	{return ENDWHILE;}

(true|TRUE)	{yylval.ival=TRUE;
		return BNUM;
		}
		

(false|FALSE)	{
		yylval.ival=FALSE;
		return BNUM;
		}


{int}		{
		yylval.ival=atoi(yytext);
		return INTEGER;
		}

{mathopr}	{return *yytext;}
{relop}		{return RELOP;}
{logopr}	{return *yytext;}

{extras}		{return *yytext;}

{id}		{
		char *temp=malloc(yyleng*sizeof(char)+1);
		strcpy(temp, yytext);
		temp[yyleng]='\0';
		yylval.str=temp;
		return ID;
		}
[ \t\n]		;
[\n]		yylineno++;
.		{yyerror("Character not valid \n");}
%%
