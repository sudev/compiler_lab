digit	[0-9]
digits	{digit}{digit}+
alphabet	[a-zA-Z]
id {alphabet}{alphabet}*
key decl|end|if|else|then|while|enddecl|integer|boolean|begin|endif|endwhile|return|write
eq	=
lt	>
gt	<
le	>=
ge	<=
ne 	!=
delim	;
plus	+
minus	-
mul	*
div	/
eqeq	==
modulo	%

%%
{digit}	{printf("digit %s\n",yytext);}
{digits} {printf("digits %s\n",yytext);}
{alphabet} {printf("Alphabet %s\n",yytext);}
{key}	{printf("keyword %s\n",yytext);}
{id}	{printf("id, %s\n",yytext);}
{delim}	{printf("deliminator %s\n",yytext);}
{eq}	{printf("operator %s\n",yytext);}
{gt}	{printf("operator %s\n",yytext);}
{lt}	{printf("operator %s\n",yytext);}
{le}	{printf("operator %s\n",yytext);}
{ge}	{printf("operator %s\n",yytext);}
{ne}	{printf("operator %s\n",yytext);}


{minus}	{printf("operator %s\n",yytext);}

{eqeq}	{printf("operator %s\n",yytext);}
{modulo}	{printf("operator %s\n",yytext);}

%%
