/* */
%{
#include <stdlib.h>
    void yyerror(char *);
#include "y.tab.h"
    %}

int [0-9]+
id  
%%


decl  {return DECL;}
enddecl {return ENDDECL;}
integer {return INTEGERE;}
boolean {return BOOLEANE;}
\;   {return *yytext;}
\,  {return *yytext;}
"["  {return *yytext;}
"]"  {return *yytext;}
int {return INTEGER;}
"int main(){"   {return INTMAIN;}
"{" {return *yytext;}
"}" {return *yytext;}

%%

int yywrap(void) 
            {
        return 1;
            }

