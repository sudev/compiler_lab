%{
#include <stdlib.h>
void yyerror(char *);
#include "y.tab.h"
%}

digit   [0-9]+
%%
[ \t\n]*    ;
\+       {return *yytext;}
{digit}   {return DIGIT;}
.      {printf("Invalid char");}
%%
int yywrap(void)
{
    return 1;
}


