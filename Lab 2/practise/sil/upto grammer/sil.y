%{
#include <stdio.h>

void yyerror(char *);

%}

%token INTMAIN DECL ENDDECL RETURN INTEGERE BOOLEANE ID END BEG IF ELSE  ENDIF WHILE DO ENDWHILE THEN INTEGER READ WRITE MATHOPR LOGICALOPR 

%left OR
%left AND
%left '+' '-'
%left '*' '/'

%%

start:  global main
     ;

global: DECL declstate ENDDECL
      |
      ;


declstate:  INTEGERE ids declstate 
     | BOOLEANE ids declstate
     |
     ;
ids:    ID  idsr 
   |    ID '['INTEGER']' idsr
   ;
idsr:   ',' ids
    |';'
    ;
    
main:   INTMAIN maindecl body '}'
    ;


maindecl:   DECL mainstate ENDDECL
        ;
mainstate:  INTEGERE mids mainstate
         |  BOOLEANE mids mainstate
         |
         ;
mids:   ID midsr
    ;
midsr:  ',' mids
     |  ';'
     ;

body:   BEG statements ret END
    ;

statements: assign statements 
          | cond statements 
          | itr statements 
          | ipop statements 
          |
          ;

assign: ID '=' INTEGER ';' 
      | ID '[' INTEGER ']' '=' INTEGER ';'
      ;

cond:   IF logicalexpr THEN statements optional 
    ;

optional:   ELSE statements ENDIF ';' 
        | ENDIF';'
        ;

itr:    WHILE logicalexpr DO statements ENDWHILE ';'
   ;

ipop:  READ'('ID')'';' 
    |  READ'('array')'';'
    |  WRITE'(' arithmeticexpr ')'';'
    ;


array:  ID'['array2']'
     ;
array2: array1
      ;
array1: INTEGER
      | ID'['array1']'
      ;

logicalexpr:    arithmeticexpr LOGICALOPR arithmeticexpr
           ;

arithmeticexpr: arithmeticexpr MATHOPR arithmeticexpr
	      | ID
              | ID'[' arithmeticexpr ']'
              | INTEGER
              | '(' arithmeticexpr ')'
              ;
ret:    RETURN INTEGER ';'
%%

int main()
{
	yyparse();
	return 0;
}
void yyerror(char *s)
{
	fprintf(stderr, "Error: %s\n", s);
}