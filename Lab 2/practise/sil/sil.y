%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}

%token DECL ENDDECL

%%


