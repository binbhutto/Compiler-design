
%%
while                      { return WHILE; }
[A-Za-z]([A-Za-z]|[0-9])*  { return ID; }
[0-9]+                     { return NUM; }
"=="					   { return EQUAL; }
"!="					   { return NOT_EQUAL; }
">="					   { return LT_EQUAL; }
"<="					   { return GT_EQUAL; }
"<"					       { return LT; }
">"					       { return GT; }
"$"                        { yyterminate(); }
[ \t\n\r]                  { ; }
.                          { return yytext[0]; }
%%
