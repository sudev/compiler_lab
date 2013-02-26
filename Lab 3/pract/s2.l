%{

#include "y.tab.h"
int yylineno;

extern YYSTYPE yylval;


#define EQ	0
#define LE	1
#define GE	2
#define NE	3
#define LT	4
#define GT	5

#define TRUE	1
#define FALSE	0

%}


id		[_a-zA-Z][_0-9a-zA-Z]*
num		[0-9]+
mathop		[-+\*\/\%]
logop		AND|OR|NOT
other		[\(\)\[\]\{\}\;,=]

%%

[ \t]		;
[\n]		yylineno++;

main		return MAIN;
if		return IF;
then		return THEN;
else		return ELSE;
endif		return ENDIF;
decl		return DECL;
enddecl		return ENDDECL;
begin		return BEG;
end		return END;
while		return WHILE;
do		return DO;
endwhile	return ENDWHILE;
return 		return RETURN;
read		return READ;
write		return WRITE;
integer		return INTEGER;
boolean		return BOOLEAN;


(true|TRUE)	{yylval.ival=TRUE;
		return BNUM;
		}
		
(false|FALSE)	{
		yylval.ival=FALSE;
		return BNUM;
		}

		
{num}		{
		yylval.ival=atoi(yytext);
		return NUM;
		}
		
{mathop}	{return *yytext;}

==		{
		yylval.relop=EQ;
		return RELOP;
		}

\>=		{
		yylval.relop=GE;
		return RELOP;
		}
		
\<=		{
		yylval.relop=LE;
		return RELOP;
		}
		
!=		{
		yylval.relop=NE;
		return RELOP;
		}
		
\<		{
		yylval.relop=LT;
		return RELOP;
		}

\>		{
		yylval.relop=GT;
		return RELOP;
		}
		
		

{logop}		{return *yytext;}

{other}		{return *yytext;}

{id}		{
		char *temp=malloc(yyleng*sizeof(char)+1);
		strcpy(temp, yytext);
		temp[yyleng]='\0';
		yylval.str=temp;
		return ID;
		}


.		yyerror("invalid character\n");

%%	

 
