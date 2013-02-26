%{
	#include<string.h>
	#include<stdio.h>
	#include<stdlib.h>
	
	
	unsigned int err_count=0;
	extern int yylineno;
	unsigned int dectype;

#define INT 0
#define BOOL 1
#define INT_ARRAY 2
#define BOOL_ARRAY 3

			
	struct GST {
		char *name;
		int type;
		int size;
		struct GST *next;
	};
	
	struct LST {
		char *name;
		int type;
		struct LST *next;
	};	
		
	struct GST *Ghead=NULL;
	struct LST *Lhead=NULL;
	
	
	int yylex(void);
	void yyerror(char *);
	void Ginsert(char *, int, unsigned int);
	void Linsert(char *, int);
	int gettype(char *);
	int gdupcheck(char *);
	int ldupcheck(char *);
	
%}

%defines

%union{
	int type;
	char *str;
	int ival;
	int relop;
	}
	
	
%token MAIN IF THEN ELSE ENDIF DECL ENDDECL BEG END WHILE DO ENDWHILE RETURN READ WRITE INTEGER BOOLEAN AND OR NOT
%token <str> ID
%token <ival> NUM BNUM
%token <relop> RELOP


%right RELOP
%right	NOT
%left AND OR
%left	'-' '+'
%left	'/' '*' '%'


%type <type> var expr

%%

program : global_decl main
	;
	
global_decl 	: DECL g_decls ENDDECL
	    	|
	    	;
	   
g_decls : g_decls g_decl
	| g_decl 
	;
	
g_decl 	: INTEGER {dectype=INT;} gid_list ';'		
	| BOOLEAN {dectype=BOOL;} gid_list ';'		
	;
	
gid_list : gid_list ',' id
	 | id
	 ;
	 
id	: ID				{Ginsert($1, dectype, 1);}
	| ID'['NUM']'			{Ginsert($1, dectype, $3);}
	;

main 	: INTEGER MAIN '(' ')' '{' local_decl body '}'
	;
	
	
local_decl	: DECL l_decls ENDDECL
		|
		;
		
l_decls : l_decls l_decl
	| l_decl
	;
	
l_decl	: INTEGER {dectype=INT;} lid_list ';' 		
	| BOOLEAN {dectype=BOOL;} lid_list ';'		
	;
	
lid_list 	: lid_list ',' ID	{Linsert($3, dectype);}
		| ID			{Linsert($1, dectype);}
	 	;
	 
body 	: BEG stmt_list	RETURN NUM ';' END

stmt_list	: stmt_list stmt
		|
		;
		
stmt	: assignment 						
	| conditional 
	| iterative
	| io 
	;


assignment	: var '=' expr ';'	{if(($1==INT_ARRAY)||($1==BOOL_ARRAY))
						yyerror("Arrays cannot be assigned");
					else if($1!=$3) 
						yyerror("Type Mismatch");
						
					}
		;
		
var	: ID			{$$=gettype($1);}
	| ID'['expr']'		{if($3!=INT)
					yyerror("Array index must be an integer");	
				else
				 	{
				 	$$=gettype($1);
				 	if($$==INT_ARRAY)
				 		$$=INT;
				 	else if ($$==BOOL_ARRAY)
				 		$$=BOOL;
					}
				}
	;
	

expr	: var			{$$=$1;}			
	| NUM			{$$=INT;}
	| BNUM			{$$=BOOL;}
	| '(' expr ')'		{$$=$2;}
	| expr '+' expr		{if(($1==INT)&&($1==$3)) $$=$1; else yyerror("Type Mismatch");}
	| expr '-' expr		{if(($1==INT)&&($1==$3)) $$=$1; else yyerror("Type Mismatch");}
	| expr '*' expr		{if(($1==INT)&&($1==$3)) $$=$1; else yyerror("Type Mismatch");}
	| expr '/' expr		{if(($1==INT)&&($1==$3)) $$=$1; else yyerror("Type Mismatch");}
	| expr '%' expr		{if(($1==INT)&&($1==$3)) $$=$1; else yyerror("Type Mismatch");}
	| expr AND expr		{if(($1==BOOL)&&($1==$3)) $$=$1; else yyerror("Type Mismatch");}
	| expr OR expr		{if(($1==BOOL)&&($1==$3)) $$=$1; else yyerror("Type Mismatch");}
	| NOT expr		{if($2==BOOL) $$=$2; else yyerror("Type Mismatch");}
	| expr RELOP expr	{if(($1==INT)&&($1==$3)) $$=BOOL; else yyerror("Type Mismatch");}
	;


conditional	: IF expr THEN stmt_list ENDIF ';'			{if($2!=BOOL) yyerror("Condition must be a boolean test");}
		| IF expr THEN stmt_list ELSE stmt_list ENDIF ';'	{if($2!=BOOL) yyerror("Condition must be a boolean test");}
		;
		
iterative	: WHILE expr DO stmt_list ENDWHILE ';'			{if($2!=BOOL) yyerror("Condition must be a boolean test");}
		;
		
io	: READ '(' var ')' ';'			{if($3!=INT) yyerror("Type Mismatch");}
	| WRITE '(' expr ')' ';'		{if($3!=INT) yyerror("Type Mismatch");}
	;
		
%%


int main()
{
	yyparse();
	return 0;
}
void yyerror(char *s)
{
	fprintf(stderr, "%s - line no : %d\n", s, yylineno);
	err_count++;
}
int yywrap(void)
{
	if(err_count==0)
	printf("successfully parsed\n");
	return 1;
}


void Ginsert(char *name, int type,unsigned int size)
{

	if(gdupcheck(name)>=0)
	{
		yyerror("Duplicate variable");
		return;
	}
		
	struct GST * ptr=malloc(sizeof(struct GST));
	
	ptr->name=name;
	ptr->size=size;
	if(size>1)
	{
		if(type==INT)
			ptr->type=INT_ARRAY;
		else if(type==BOOL)
			ptr->type=BOOL_ARRAY;
	}
	else
		ptr->type=type;
	
	if(Ghead==NULL)
		Ghead=ptr;
	else
	{
		struct GST * temp = Ghead;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=ptr;
	}
}


void Linsert(char *name, int type)
{

	if(ldupcheck(name)>=0)
	{
		yyerror("Duplicate variable");
		return;
	}
	struct LST *ptr=malloc(sizeof(struct LST));
	
	ptr->name=name;
	ptr->type=type;
	
	if(Lhead==NULL)
		Lhead=ptr;
	else
	{
		struct LST * temp = Lhead;
		while(temp->next!=NULL)
			temp=temp->next;
		temp->next=ptr;
	}
}


int gettype(char *name)
{
	struct LST * lptr = Lhead;
	while(lptr!=NULL)
		if(strcmp(lptr->name, name)==0)
			return lptr->type; 
		else
			lptr=lptr->next;
	
	struct GST *gptr=Ghead;
	
	while(gptr!=NULL)
		if(strcmp(gptr->name, name)==0)
			return gptr->type; 
		else
			gptr=gptr->next;
	

	yyerror("Undefined Variable");
	
	return -1;
}

int gdupcheck(char * name)
{
	struct GST * ptr=Ghead;
	while(ptr!=NULL)
		if(strcmp(ptr->name, name)==0)
			return 1;
		else
			ptr=ptr->next;
			
	return -1;
}

int ldupcheck(char * name)
{
	struct LST * ptr=Lhead;
	while(ptr!=NULL)
		if(strcmp(ptr->name, name)==0)
			return 1;
		else
			ptr=ptr->next;
			
	return -1;
}
	 
