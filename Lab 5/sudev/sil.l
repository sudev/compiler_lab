%{
#include "commons.h"
#include "y.tab.h"
extern int line, sec;
extern datatype_t *decl_type, *param_type;
extern datatype_t *DT_INT, *DT_BOOL;
extern struct symstack_n *cur_func_def;
%}

UDEF_TOK	[a-zA-Z][a-zA-Z0-9_]*

%%

"//".*		;
decl		{ return DECL; }
enddecl		{ return ENDDECL; }
begin		{ return BEG; }
end			{ return END; }
return		{ return RETURN; }
read		{ return READ; }
write		{ return WRITE; }
if			{ return IF; }
then		{ return THEN; }
else		{ return ELSE; }
endif		{ return ENDIF; }
while		{ return WHILE; }
do			{ return DO; }
endwhile	{ return ENDWHILE; }
boolean		{ if (sec == SEC_FDECL) param_type = DT_BOOL; else decl_type = DT_BOOL; return DATATYPE; }
integer		{ if (sec == SEC_FDECL) param_type = DT_INT; else decl_type = DT_INT; return DATATYPE; }
NOT			{ yylval = create_node(T_NOT, 0, 0); return NOT; }
AND			{ yylval = create_node(T_AND, 0, 0); return BIN_LOG_OP; }
OR			{ yylval = create_node(T_OR, 0, 0); return BIN_LOG_OP; }
"=="		{ yylval = create_node(T_REL_E, 0, 0); return REL_OP; }
">="		{ yylval = create_node(T_REL_GE, 0, 0); return REL_OP; }
"<="		{ yylval = create_node(T_REL_LE, 0, 0); return REL_OP; }
"!="		{ yylval = create_node(T_REL_NE, 0, 0); return REL_OP; }
">"			{ yylval = create_node('>', 0, 0); return REL_OP; }
"<"			{ yylval = create_node('<', 0, 0); return REL_OP; }
"+"			{ yylval = create_node('+', 0, 0); return ADDITIVE_OP; }
"-"			{ yylval = create_node('-', 0, 0); return ADDITIVE_OP; }
"*"			{ yylval = create_node('*', 0, 0); return MULTIVE_OP; }
"/"			{ yylval = create_node('/', 0, 0); return MULTIVE_OP; }
"%"			{ yylval = create_node('%', 0, 0); return MULTIVE_OP; }
[&,=;(){}]	{ return *yytext; }
"["			{ return '['; }
"]"			{ return ']'; }
TRUE		{
			  yylval = create_node(T_BOOL_LIT, NULL, (void*) 1);
			  return B_LITERAL;
			}
FALSE		{
			  yylval = create_node(T_BOOL_LIT, NULL, (void*) 0);
			  return B_LITERAL;
			}
{UDEF_TOK}	{
			  if (sec == SEC_DECL) {
				new_symbol(yytext); //add symbol to stack (top, ofcourse!)
			  } else if (sec == SEC_FDECL) { 
				//Skip - things are done in yacc
			  } else if (sec == SEC_FBODY) {
				yylval = create_node(T_ID, NULL, lookup_sym(yytext));
				if (yylval->extra.st_entry == NULL)
				  yyerror("Invalid identifier!");
			  } else { //Function definition
				cur_func_def = lookup_sym(yytext);
				if (cur_func_def == NULL)
				  yyerror("No such function is declared!");
			  }
			  return IDENTIFIER;
			}
[0-9]+		{
			  yylval = create_node(T_INT_LIT, NULL, (void*) atol(yytext));
			  return I_LITERAL;
			}
[ \t]		;
\n			line++;
.			yyerror("Ignoring an invalid character!");
%%
int yywrap() { return 1; }
