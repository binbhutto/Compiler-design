%{
#include "lex.h"
%}

%%
"main"					{ return KEYWORD; }
"int"					{ return KEYWORD; }
"float"					{ return KEYWORD; }
"char"					{ return KEYWORD; }
"void"					{ return KEYWORD; }
[a-zA-Z][_a-zA-Z0-9]*	{ return IDENTIFIER; }
[0-9]+					{ return NUMBER; }
\"(\\.|[^\\"])*\"		{ return STRING_LTR; }
"="						{ return ASSIGN; }
"{"						{ return OPEN_BRACE; }
"}"						{ return CLOSE_BRACE; }
"("						{ return OPEN_PARAN; }
")"						{ return CLOSE_PARAN;}
";"						{ return SEMICOLON;	 }
[ \t\n]					{ ; }
.						{ printf("Unexpected Character\n"); }
%%

int yywrap(void)
{
	return 1;
}
