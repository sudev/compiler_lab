%{
	
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define IA 2
#define BA 3
#define I 0
#define B 1

unsigned int err_count=0;
extern int yylineno;
unsigned int dectype;

struct LOCAL {
  char *name;
  int type;
  struct LOCAL *next;
};

struct GLOBAL {
  char *name;
//keep track of array decls 
  int size;
  int type;
//pointer to the next item in table 
  struct GLOBAL *next;
};

//asssume top element to be NULL in table 
struct LOCAL *Ltop=NULL;
struct GLOBAL *Gtop=NULL;

//lex yacc 
int yylex(void);
void yyerror(char *);

//insert functions for global and local variables
void Ginsert(char *, int, unsigned int);
void Linsert(char *, int);


int gdupcheck(char *);
int ldupcheck(char *);

int gettype(char *);


%}

%defines

%union
{
int ival;
int relop;
int type;
char *str;
}

%token END DECL ENDDECL INTEGERE BOOLEANE AND OR NOT MAIN BEG ELSE IF THEN WHILE ENDIF RETURN DO READ WRITE ENDWHILE 
%token <ival> NUM BNUM
%token <str> ID	
%token <relop> RELOP


%right RELOP
%right	NOT
%left AND OR
%left	'-' '+'
%left	'/' '*' '%'

%type <type> var expr

%%

op	: READ '(' var ')' ';'			{if($3!=I) yyerror("wroong type");}
	| WRITE '(' expr ')' ';'		{if($3!=I) yyerror("wroong type");}
	;

expr	: var	{$$=$1;}
| expr '%' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr AND expr	{if(($1==B)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr OR expr	{if(($1==B)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| NOT expr	{if($2==B) $$=$2; else yyerror("wrong type");}
| expr RELOP expr{if(($1==I)&&($1==$3)) $$=B; else yyerror("wrong type");}
| expr '+' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr '-' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr '*' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr '/' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| NUM		{$$=I;}
| BNUM		{$$=B;}
| '(' expr ')'	{$$=$2;}
;

vari: ID'['expr']'{if($3!=I)
		yyerror("only integer allowed  indexing an array ");	
		else
		{
		$$=gettype($1);
		if($$==IA)
		$$=I;
		else if ($$==BA)
		$$=B;
		}
	} 
    |ID {$$=gettype($1);}
    ;

assign: vari '=' expr ';'{if(($1==IA)||($1==BA))
		yyerror("No array  in here");
		else if($1!=$3) 
		yyerror("wrong type");}
	;
stmt: assign
    | condi
    | op
    | iter
    ;
    
stmt:	stmt stmt
    |
    ;
body 	: BEG stmt RETURN INTEGER ';' END
	;
	
lidls: lidls ',' ID	{Linsert($3, dectype);}
      | ID	{Linsert($1, dectype);}
      ;

ldecl:	BOOLEANE {dectype=B;} lidls ';'
	|INTEGERE {dectype=I;} lidls ';'
	;

ldecls : ldecls ldecl
	| ldecl
	;
	
ldecl: DECL ldecls ENDDECL
	    |
	    ;

intmain	: INTEGERE MAIN '(' ')' '{' ldecl body '}'
	;

id:	ID '[' INTEGER ']' {Ginsert($1, dectype, $3);}
	|ID {Ginsert($1, dectype, 1);}
	;
glist:	glist, id
      | id 
      ;

gdec: INTEGERE {dectype=I;} glist ';'
    | BOOLEANE {dectype=B;} glist ';'
    |
    ;
    
gdecs: gdecs gdec
      |gdec
      ;

gdecl:	DECL gdecs ENDDECL
      |
      ;
 
start:	gdecl intmain 
     ;
     




























