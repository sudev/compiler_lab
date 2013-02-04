%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}

%token DECL ENDDECL INTEGERE BOOLEANE INTMAIN

%%

start:  global main
     ;

global: DECL declstate ENDDECL
      ;

declstate:  decle declstate 
         |
         ;
decle:  INTEGERE ids decle 
     | BOOLEANE ids decle
     |
     ;
ids:    id idsr 
   |    id '['INTEGER']' idsr
   ;
idsr:   ',' ids
    |';'
    ;

main:   INTMAIN maindecl body '}'
    ;
maindecl:   DECL mainstate ENDDECL
        ;
mainstate:  INTEGERE mids mdecl
         |  BOOLEANE mids mdecl
         |
         ;
mids:   id midsr
    ;
midsr:  "," mids
     |  ";"
     ;

