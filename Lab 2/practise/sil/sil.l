%{
#include <stdlib.h>
#include "y.tab.h"

%}

int [0-9]+
alphabet    [a-zA-Z]
id  {alphabet}[{alphabet}|{int}]*
mathopr	[\-+\*\/\%]
logicalopr	>|<|==|!=|>=|<=
%%

"end" {return ENDEE;} 
"decl"  {return DECL;}
"enddecl" {return ENDDECL;}
"integer" {return INTEGERE;}
"boolean" {return BOOLEANE;}
\;   {return *yytext;}
"["  {return *yytext;}
"]"  {return *yytext;}
{int} {return INTEGER;}
"main"	{return MAIN;}
"{" {return *yytext;}
"}" {return *yytext;}
"=" {return *yytext;}

"begin" {return BEG;}
"(" 	{return *yytext;}
")"	{return *yytext;}
"if" {return IF;}
"ELSE" {return ELSE;}
"then"    {return THEN;}
"endif"   {return ENDIF;}
"while"   {return WHILE;}
"do"  {return DO;}
"endwhile"    {return ENDWHILE;}
"read"    {return READ;}
"wirte"    {return WRITE;}
","	{return *yytext;}

{mathopr}   {yylval = create("mathopr",NULL,NULL);return MATHOPR;}
{logicalopr} {yylval = create("logicalopr",NULL,NULL);return LOGICALOPR;  }
return	{return RETURN;}
{id}  {yylval = create("ID",NULL,NULL); return ID;}
[ \n\t]	;

%%
int yywrap(void) 
{
        return 1;
}

