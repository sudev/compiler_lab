%{
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}

%token DECL ENDDECL INTEGERE BOOLEANE INTMAIN ID END BEGIN IF ELSE  ENDIF WHILE DO ENDWHILE THEN 

%%

start:  global main
     ;

global: DECL declstate ENDDECL
      ;

/* global declaration section */
declstate:  decle declstate 
         |
         ;
decle:  INTEGERE ids decle 
     | BOOLEANE ids decle
     |
     ;
ids:    ID  idsr 
   |    ID '['INTEGER']' idsr
   ;
idsr:   ',' ids
    |';'
    ;
/* main section */
main:   INTMAIN maindecl body '}'
    ;

/*main declaration section */

maindecl:   DECL mainstate ENDDECL
        ;
mainstate:  INTEGERE mids mdecl
         |  BOOLEANE mids mdecl
         |
         ;
mids:   ID midsr
    ;
midsr:  ',' mids
     |  ';'
     ;
/*body of the main function */

body:   BEGIN statements ret END
    ;
statements: assign statements 
          | cond statements 
          | itr statements 
          | ipop statements 
          ;
assign: ID '=' INTEGER ';' 
      | ID '[' INTEGER ']' ]'=' INTEGER ';'
      ;
cond:   IF logicalexpr THEN statements optional 
    ;
optional:   ELSE statements ENDIF ';' 
        | ENDIF';'
        ;
itr:    WHILE logicalexpr DO statements ENDWHILE ';'
   ;
ipop:  READ'('ID')'';' 
    |       READ'('


