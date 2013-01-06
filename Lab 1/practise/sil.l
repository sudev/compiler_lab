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
plus	\+
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
{eq}	{printf("Equal %s\n",yytext);}
{gt}	{printf("greater than %s\n",yytext);}
{lt}	{printf("less than %s\n",yytext);}
{le}	{printf("less than equal %s\n",yytext);}
{ge}	{printf("greater than equal %s\n",yytext);}
{ne}	{printf("not equal  %s\n",yytext);}
{plus}	{printf("plus %s\n",yytext);}

{minus}	{printf("minus %s\n",yytext);}

{eqeq}	{printf("equal equal  %s\n",yytext);}
{modulo}	{printf("modulo %s\n",yytext);}

%%
