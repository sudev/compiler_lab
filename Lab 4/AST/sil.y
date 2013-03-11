%{
	#include<stdio.h>
	int yylex(void);
	void yyerror(char *);
	extern int yylineno;
	int tabcount=-1;
	
	struct quad{
	  char op;
	  char * one;
	  char * two;
	  char * three;
	}

	struct Node{
	
	char *str;
	struct Node *next1;
	struct Node *next2;
	struct Node *next3;
	};
	
	struct Node * makenode(char *str, struct Node *next1,struct Node *next2, struct Node *next3);
	struct quad * makequad(char *str, struct quad *one, struct quad *two,char *s);
	void printtree(struct Node * ptr);
%}

%token <ptr> IF ELSE ENDIF DECL ENDDECL BEG END WHILE DO ENDWHILE RETURN READ WRITE TYPE MAIN THEN NOT BOOLEAN AND OR INTEGER ID RELOP

%token <ptr> NUMBER



%left OR
%left AND
%left '+' '-'
%left '*' '/' '%'

%type <ptr> main local_decl local_declarations body statements statement assignment conditional iterative io expr arith_expr log_expr var id_list integer boolean

%union {
	struct Node *ptr;
};

%%

program : global_decl main
	;

global_decl : DECL declarations ENDDECL		
	    | 
	    ;

declarations : INTEGER var vars ';' declarations
	     | BOOLEAN var vars ';' declarations
	     |
	     ;

var : ID				
    | ID'['NUMBER']'			{$$=makenode("ARR", $1, $3, NULL);}
    ;

vars : ',' var vars
     |
     ;


main : INTEGER MAIN '('')' '{' local_decl body '}' 		{$$=makenode("MAIN", $6, $7, NULL); printtree($$);}
     ;


local_decl : DECL local_declarations ENDDECL 			{$$=makenode("DECLS",$2, NULL, NULL);}
	   |							{$$=NULL;}
	   ;

local_declarations : integer ';' local_declarations			{$$=makenode("DECLN", $1, $3, NULL);}
		   | boolean ';' local_declarations			{$$=makenode("DECLN", $1, $3, NULL);}
		   |						{$$=NULL;}
		   ;
		   
integer : INTEGER id_list					{$$=makenode("TYPE", $2, NULL, NULL);}
	;
	
boolean : BOOLEAN id_list					{$$=makenode("TYPE", $2, NULL, NULL);}
	;
		
id_list : id_list ',' ID					{$$=makenode("LIST", $1, $3, NULL);}
	   | ID							{$$=$1;}
	   ;

body : BEG statements RETURN NUMBER ';' END 			{$$=makenode("STMTS", $2, NULL, NULL);}
     ;

statements : statement statements				{$$=makenode("STMT", $1, $2, NULL);  }
	   |							{$$=NULL;}
	   ;

statement : assignment 						
	  | conditional 
	  | iterative
	  | io 
	  ;

assignment : var '=' expr ';'					{$$=makenode("=", $1, $3, NULL);}
	   ;

conditional : IF log_expr THEN statements ENDIF	';'		{$$=makenode("IF", $2, $4, NULL);}
	    | IF log_expr THEN statements ELSE statements ENDIF	';'	{$$=makenode("IFELSE", $2, $4, $6);}
	    ;

iterative : WHILE log_expr DO statements ENDWHILE ';'		{$$=makenode("ITER", $2, $4, NULL);}
	  ;

io : READ '(' var ')' ';'					{$$=makenode("READ", $3, NULL, NULL);}
   | WRITE '(' arith_expr ')'	';'				{$$=makenode("WRITE", $3, NULL, NULL);}
   ;


expr : arith_expr
     | log_expr
     ;

arith_expr : arith_expr '+' arith_expr			{$$=makenode("+", $1, $3, NULL);}
	   | arith_expr '-' arith_expr			{$$=makenode("-", $1, $3, NULL);}
	   | arith_expr '*' arith_expr			{$$=makenode("*", $1, $3, NULL);}
	   | arith_expr '/' arith_expr			{$$=makenode("/", $1, $3, NULL);}
	   | arith_expr '%' arith_expr			{$$=makenode("%", $1, $3, NULL);}
	   | ID							
	   | NUMBER
	   | ID'['arith_expr']'				{$$=makenode("ARR", $1, $3, NULL);}	
	   | '(' arith_expr ')'				{$$=$2;}
	   ;


log_expr : log_expr AND log_expr				{$$=makenode("AND", $1, $3, NULL);}
	 | log_expr OR log_expr					{$$=makenode("OR", $1, $3, NULL);}
	 | NOT log_expr						{$$=makenode("NOT", $2, NULL, NULL);}
	 | arith_expr RELOP arith_expr				{$$=makenode("REL", $1, $3, NULL);}
	 | '(' log_expr ')'					{$$=$2;}
	 ;



%%

int main()
{
	yyparse();
	return 0;
}
void yyerror(char *s)
{
	fprintf(stderr, "%s in line no : %d\n", s, yylineno);
}
int yywrap(void)
{
	
}

struct Node * makenode(char *str, struct Node *next1,struct Node *next2, struct Node *next3)
{
	struct Node *node = malloc(sizeof(struct Node));
	node->str=str;
	node->next1=next1;
	node->next2=next2;
	node->next3=next3;
	
	return node;
}

void printtree(struct Node * ptr)
{
	int i;

	if(ptr==NULL)
		return;
	
	tabcount++;

	for(i=0;i<tabcount;i++)
		printf("\t");
	printf(" ( ");
		
	printf("%s\n", ptr->str);
	
	printtree(ptr->next1);
	printtree(ptr->next2);
	printtree(ptr->next3);
	
	for(i=0;i<tabcount;i++)
		printf("\t");
	printf(" ) \n");
	tabcount--;
	
}
	

void threecode(Node *x)
{
  if( x == NULL)
    {
      return;
    }
  char *temp;
  temp = malloc(10);
  sprintf(temp,"temp%d",i);
  threecode(x->next1);
  threecode(x->next2);
  if(strcmp(x->str,"ID")==0)
    makequad("l",NULL,NULL,NULL);
  if(strcmp(x->str,"+")==0)
    makequad("=",quad[i-1],quad[i-2],temp);
  if(strcmp(x->str,"-")==0)
    makequad("-",quad[i-1],quad[i-2],temp);
}

void makenode(c)
