%{
	#include "y.tab.h"
	int yylineno;
	
	
	
%}

id	[_a-zA-Z][_0-9a-zA-Z]*
number  [0-9]+
int 	[+-]?{number}	
mathop 	[-+\*\/\%]
relop	==|>|<|>=|<=|!=
logop	AND|OR



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
NOT		return NOT;
AND		return AND;
OR		return OR;



{id}		{
		yylval.ptr=makenode("ID", NULL, NULL, NULL);
		return ID;
		}

{number}	{
		yylval.ptr=makenode("NO", NULL, NULL, NULL);
		return NUMBER;
		}

[=\(\)\[\];,\{\}]	return *yytext;

{mathop}	{ 
		return *yytext;
		}

{relop}		{ 
		yylval.ptr=makenode("RELOP", NULL, NULL, NULL);
		 return RELOP;
		}


	
.		printf("invalid character");
%%


