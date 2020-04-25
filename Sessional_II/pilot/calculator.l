%{
#include <stdio.h>
#include <stdlib.h>
#include "calculator.tab.h"
%}

%%

[0-9]+(\.[0-9])?([eE][0-9]+)?	{yylval.f = atof(yytext); return NUM;}
[-+()*/]			{return yytext[0];}
[ \f\t\v\n]			{;}

%%

int yywrap() {
	return -1;
}
