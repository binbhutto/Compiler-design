#include <stdio.h>
#include "lex.h"

extern int yylex();
extern FILE *yyin;

int main(void) {
	yyin = fopen("csb17016_01_q1_prog.c", "r");
	int token;
	char *token_arr[] = {
						NULL,
						"KEYWORD", 
						"IDENTIFIER",
						"NUMBER",
						"ASSIGN",
						"OPEN_BRACE",
						"CLOSE_BRACE",
						"OPEN_PARAN",
						"CLOSE_PARAN",
						"SEMICOLON",
						"STRING_LTR" 
					};
	token = yylex();
	while(token) {
		printf("Vlaue: %d\t%s\n", token, token_arr[token]);
		token = yylex();

	}

}