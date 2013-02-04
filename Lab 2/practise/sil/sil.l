/* */
%{
#include <stdlib.h>
    void yyerror(char *);
#include "y.tab.h"
    %}


%%

decl  {return DECL;}
enddecl {return ENDDECL;}


%%

int yywrap(void) 
            {
        return 1;
            }

