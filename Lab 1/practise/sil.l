digit	[0-9]
digits	{digit}{digit}+
alphabet	[a-zA-Z]
word	{alphabet}{alphabet}+
keyword decl|end|if|else|then|while|enddecl|integer|boolean|begin|endif|endwhile
%%
{digit}	{printf("digit\n");}
{digits} {printf("digits\n");}
{alphabet} {printf("Alphabet\n");}
{word}	{printf("word\n");}
%%
