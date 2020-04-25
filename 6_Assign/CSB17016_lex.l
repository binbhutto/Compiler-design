%{
#include "CSB17016_lex.h"
%}

%%
"while"					{ return TOK_WHILE; }
"begin"					{ return TOK_BEGIN; }
"end"					{ return TOK_END; }
"+"						{ return TOK_ADD; }
"*"						{ return TOK_MULT; }
[a-zA-Z][_a-zA-Z0-9]*	{ return TOK_IDENTIFIER; }
[0-9]+					{ return TOK_NUMBER; }
"="						{ return TOK_ASSIGNMENT; }
"=="					{ return TOK_COMP_EQ; }
"!="					{ return TOK_COMP_NEQ; }
"("						{ return TOK_OPEN_PARAN; }
")"						{ return TOK_CLOSE_PARAN;}
";"						{ return TOK_SEMICOLON;	 }
"$"						{ return TOK_EOF; }
[ \t\n]					{ ; }
[.]						{ return TOK_INVALID; }
%%

int yywrap(void)
{
	return 1;
}
