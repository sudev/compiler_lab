/* */
%{
#include <stdlib.h>
    void yyerror(char *);
#include "y.tab.h"
    %}

int [0-9]+
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

%%

int yywrap(void) 
            {
        return 1;
            }

