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
"integer main(){"   {return INTMAIN;}
"{" {return *yytext;}
"}" {return *yytext;}
"=" {return *yytext;}
{id}  {return ID;}
"begin" {return BEG;}

"if" {return IF;}
"ELSE" {return ELSE;}
"then"    {return THEN;}
"endif"   {return ENDIF;}
"while"   {return WHILE;}
"do"  {return DO;}
"endwhile"    {return ENDWHILE;}
"then"  {return THEN;}
"read"    {return READ;}
"wirte"    {return WRITE;}
{mathopr}   {return MATHOPR;}
{logicalopr} {return LOGICALOPR;}
return	{return RETURN;}
[ \n\t]	;

%%
int yywrap(void) 
{
        return 1;
}

