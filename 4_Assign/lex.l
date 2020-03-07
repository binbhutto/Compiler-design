%{
#include "lex.h"
%}

%%
"while"					{ return TOK_KEYWORD; }
"begin"					{ return TOK_KEYWORD; }
"end"					{ return TOK_KEYWORD; }
"+"						{ return TOK_PLUS; }
"-"						{ return TOK_MINUS; }
"*"						{ return TOK_MULT; }
"/"						{ return TOK_DIV; }
[a-zA-Z][_a-zA-Z0-9]*	{ return TOK_IDENTIFIER; }
[0-9]+					{ return TOK_NUMBER; }
"="						{ return TOK_ASSIGN; }
"=="					{ return TOK_EQUAL; }
"("						{ return TOK_OPEN_PARAN; }
")"						{ return TOK_CLOSE_PARAN;}
";"						{ return TOK_SEMICOLON;	 }
[ \t\n]					{ ; }
.						{ return TOK_INVALID; }
%%

int yywrap(void)
{
	return 1;
}