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

%token  MAIN DECL ENDDECL RETURN INTEGERE BOOLEANE ID ENDEE BEG IF ELSE  ENDIF WHILE DO ENDWHILE THEN INTEGER READ WRITE MATHOPR LOGICALOPR 

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
    
main:   INTEGERE MAIN '('')' '{'  maindecl body '}'		{ $$ = create("Int-main",$6,0); $6->next = $7; printfunction($$); } 
    ;

maindecl:   DECL mainstate ENDDECL				{ $$ = create("Int-main-decla ",$2, NULL);  }
        ;
mainstate:  INTEGERE mids mainstate				{ $$ = create("Int decla" ,NULL,NULL); $$->next=$3; }
         |  BOOLEANE mids mainstate				{ $$ = create("Bool decla" ,NULL,NULL); $$->next=$3; }
         |							{ $$ = NULL;}	
         ;
mids:   ID midsr
    ;
midsr:  ',' mids
     |  ';'
     ;

body:   BEG statements ret ENDEE				{ $$ = create("Int-main-body ", create("stmtBlock",$2,$3), 0); }
    ;
 
statements: assign statements 					{ $$ = $1;  $1->next=$2; }
          | cond statements 					{ $$ = $1;  $1->next=$2; }
          | itr statements 					{ $$ = $1;  $1->next=$2; }
          | ipop statements 					{ $$ = $1;  $1->next=$2; }
          |							{ $$ = NULL;}
          ;

assign: ID '=' INTEGER ';' 					{ $$ = create("Int assign" ,NULL,NULL);  }
      | ID '[' INTEGER ']' '=' INTEGER ';'			{ $$ = create("Array " ,NULL,NULL); }
      ;

cond:   IF logicalexpr THEN statements ENDIF ';' 		{ $$ = create("IF " ,$2,NULL);  $2->next=$4;}
    |	IF logicalexpr THEN statements ELSE statements ENDIF ';'{ $$ = create (" IF ",$2,NULL); $2->next=$4; $4->next=$6;}
    ;


itr:    WHILE logicalexpr DO statements ENDWHILE ';'		{ $$ = create("While " ,NULL,NULL); }
   ;

ipop:  READ'('ID')'';' 						{ $$ = create("Read " ,NULL,NULL);   }
    |  READ'('array')'';'					{ $$ = create("Read " ,NULL,NULL); }
    |  WRITE'(' arithmeticexpr ')'';'				{ $$ = create("write" ,$3,NULL);  }
    ;


array:  ID'['array2']'
     ;
array2: array1
      ;
array1: INTEGER
      | ID'['array1']'
      ;

logicalexpr:    arithmeticexpr LOGICALOPR arithmeticexpr	{ $$ = create("logicalexpr " ,$1,NULL); $1->next =$3;  }
           ;

arithmeticexpr: arithmeticexpr MATHOPR arithmeticexpr		{ $$ = $2; $2->child= $1; $1->next = $3;  }
	      | ID						{ $$ = $1;}
              | ID'[' arithmeticexpr ']'			{ $$ = $3;}
              | INTEGER						{ $$ = $1;}	
              | '(' arithmeticexpr ')'				{ $$ = $2;}
              ;
ret:    RETURN INTEGER ';'					{ $$ = create("return  " ,NULL,NULL); }
	;
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
      printf("\n");
   }
   printf(")");
   printf("\n");
}
   
struct node *create(const char *name, struct node *child,struct node *next)
{
  struct node *nextlevel = malloc(sizeof(struct node)); 		//memory allocation to new guy with type struct node
  nextlevel->name = name;
  nextlevel->next = next;
  nextlevel->child = child;
  return nextlevel; 							//returns the new node to guy 
}
