%{
	
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define IA 2
#define BA 3
#define I 0
#define B 1

unsigned int errtotal=0;
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


int gsame(char *);
int lsame(char *);

int gettype(char *);


%}

%defines

%union
{
int ival;
int type;
char *str;
}

%token END DECL ENDDECL INTEGERE BOOLEANE AND OR NOT MAIN BEG ELSE IF THEN WHILE ENDIF RETURN DO READ WRITE ENDWHILE RELOP
%token <ival> INTEGER BNUM
%token <str> ID	



%right RELOP
%right	NOT
%left AND OR
%left	'-' '+'
%left	'/' '*' '%'

%type <type> vari expr

%%
start:	gdecl intmain 
     ;
condi: IF expr THEN stmts ENDIF ';'	{if($2!=B) yyerror("if bool");}
      | IF expr THEN stmts ELSE stmts ENDIF ';'	{if($2!=B) yyerror("if bool");}
      ;

iter: WHILE expr DO stmts ENDWHILE ';'{if($2!=B) yyerror("while boolean");}
  ;
  
op	: READ '(' vari ')' ';'			{if($3!=I) yyerror("wroong type");}
	| WRITE '(' expr ')' ';'		{if($3!=I) yyerror("wroong type");}
	;

expr	: vari	{$$=$1;}
| expr '%' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr AND expr	{if(($1==B)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr OR expr	{if(($1==B)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| NOT expr	{if($2==B) $$=$2; else yyerror("wrong type");}
| expr RELOP expr{if(($1==I)&&($1==$3)) $$=B; else yyerror("wrong type");}
| expr '+' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr '-' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr '*' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| expr '/' expr	{if(($1==I)&&($1==$3)) $$=$1; else yyerror("wrong type");}
| INTEGER		{$$=I;}
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
    
stmts:	stmts stmt
    |
    ;
body : BEG stmts RETURN INTEGER ';' END
     ;
	
lidls: lidls ',' ID	{Linsert($3, dectype);}
      | ID	{Linsert($1, dectype);}
      ;

ldeclw:	BOOLEANE {dectype=B;} lidls ';'
	|INTEGERE {dectype=I;} lidls ';'
	;

ldecls : ldecls ldeclw	
	| ldeclw
	;
	
ldecl: DECL ldecls ENDDECL
    |
    ;

intmain	: INTEGERE MAIN '(' ')' '{' ldecl body '}'
	;

id:	ID '[' INTEGER ']' {Ginsert($1, dectype, $3);}
	|ID {Ginsert($1, dectype, 1 );}
	;
glist:glist id
      |id
      ;

gdec: INTEGERE {dectype=I;} glist ';'
    | BOOLEANE {dectype=B;} glist ';'
    ;
    
gdecs: gdecs gdec
      |gdec
      ;

gdecl:	DECL gdecs ENDDECL
      |
      ;
 

     

%%
int main(){
yyparse();
return 0;
}

int yywrap(void)
{
  if(!errtotal)
  printf("no typrecheck error");
    return 1;
}
   
void yyerror(char *s)
{
fprintf(stderr, "%s - line no : %d\n", s, yylineno);
errtotal++;
}


void Ginsert(char *name, int type,unsigned int size)
{
if(gsame(name)>=0)
{
yyerror("Variable declared more than once ");
return;
}
struct GLOBAL * ptr=malloc(sizeof(struct GLOBAL));
ptr->name=name;
ptr->size=size;
	if(size>1)
	{
if(type==I)
ptr->type=IA;
else if(type==B)
ptr->type=BA;
}
else
ptr->type=type;
if(Gtop==NULL)
Gtop=ptr;
else
{
struct GLOBAL * temp = Gtop;
while(temp->next!=NULL)
temp=temp->next;
temp->next=ptr;
	}
}


void Linsert(char *name, int type)
{
if(lsame(name)>=0)
{
yyerror("Duplicate variable");
return;
}
struct LOCAL *ptr=malloc(sizeof(struct LOCAL));
ptr->name=name;
ptr->type=type;
if(Ltop==NULL)
Ltop=ptr;
	else
	{
struct LOCAL * temp = Ltop;
while(temp->next!=NULL)
	temp=temp->next;
	temp->next=ptr;
}
}


int gettype(char *name)
{
struct LOCAL * lptr = Ltop;
while(lptr!=NULL)
	if(strcmp(lptr->name, name)==0)
	return lptr->type; 
else
	lptr=lptr->next;
	struct GLOBAL *gptr=Gtop;
while(gptr!=NULL)
if(strcmp(gptr->name, name)==0)
return gptr->type; 
else
gptr=gptr->next;
yyerror("Undefined Variable");
return -1;
}

int gsame(char * name)
{
struct GLOBAL * ptr=Gtop;
while(ptr!=NULL)
if(strcmp(ptr->name, name)==0)
return 1;
else
ptr=ptr->next;
return -1;
}

int lsame(char * name)
{
struct LOCAL * ptr=Ltop;
while(ptr!=NULL)
if(strcmp(ptr->name, name)==0)
return 1;
else
ptr=ptr->next;
return -1;
}
 





