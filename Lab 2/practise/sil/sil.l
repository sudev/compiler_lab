%{
#include <stdlib.h>
    void yyerror(char *);
#include "y.tab.h"
%}

int [0-9]+
alphabet    [a-zA-z]
id  {alphabet}[{alphabet}|{int}]*
mathopr	[+-\*\/\%]
%%


decl  {return DECL;}
enddecl {return ENDDECL;}
integer {return INTEGERE;}
boolean {return BOOLEANE;}
\;   {return *yytext;}
"["  {return *yytext;}
"]"  {return *yytext;}
int {return INTEGER;}
"int main(){"   {return INTMAIN;}
"{" {return *yytext;}
"}" {return *yytext;}
"=" {return *yytext;}
id  {return ID;}
BEGIN {return BEGIN;}
END {return END;}
if {return IF;}
ELSE {return ELSE;}
then    {return THEN;}
endif   {return ENDIF;}
while   {return WHILE;}
do  {return DO;}
endwhile    {return ENDWHILE;}
then  {return THEN;}
read    {return READ;}
wirte    {return WRITE;}
mathopr	{return MATHOPR;}
logicalopr {return LOGICALOPR;}
return	{return RETURN;}


%%
int yywrap(void) 
{
        return 1;
}

