%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}

%token DIGIT

%%

program:    expr;
expr:       DIGIT '+' expr
            |DIGIT
            ;
%%

void yyerror(char *s) {
fprintf(stderr, "%s\n", s);
}

int main(void) {
yyparse();
return 0;
}


