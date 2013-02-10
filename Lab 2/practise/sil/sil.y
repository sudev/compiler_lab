%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(char *);


struct node 
  {
  struct node *child;	//left guy 
  struct node *next;	//next guy with pointer pointing to it 
  const char *name; 	//name / type of the current struct 
  };
  
#define YYSTYPE struct node *
void printfunction(struct node *); //function printing the ast 
struct node *create(const char *name, struct node *child, struct node *next); //funtion to create more nodes 


%}

%token INTMAIN DECL ENDDECL RETURN INTEGERE BOOLEANE ID ENDEE BEG IF ELSE  ENDIF WHILE DO ENDWHILE THEN INTEGER READ WRITE MATHOPR LOGICALOPR 

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

body:   BEG statements ret ENDEE
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
void printfunction(struct node *pr)
{
  printf("(");
  printf("%s", pr->name);
  struct node *child = pr->child;					//asigns new struct for recursive loop
  while(child)
  {
      printfunction(child);
      child = child->next;
   }
   printf(")");
}
   
struct node *create(const char *name, struct node *child,struct node *next)
{
  struct node *nextlevel = malloc(sizeof(struct node)); 		//memory allocation to new guy with type struct node
  nextlevel->name = name;
  nextlevel->next = next;
  nextlevel->child = child;
  return nextlevel; 							//returns the new node to guy 
}
