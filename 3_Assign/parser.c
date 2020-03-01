/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 * Description: Imagine the syntax of a programming language construct such as while-loop --
 *
 *				while ( condition ) 
 *				begin 
 *				      statement ; 
 *				            : 
 *				end
 *
 *				where while, begin, end are keywords; condition can be a single comparision expression
 * 				(such as x == 20, etc.); and statement is the assignment to a location the result of a
 *				single arithmatic operation (eg., a = 10 * b).
 *				
 *				Write a context free grammar for the above construct, and create an operator precedence
 *				parsing table based on the grammar. Hint: Represent the grammar in appropriate data structures,
 *				then create the LEADING and TRAILING sets for the non-terminals of the grammar.
 */
#include <stdio.h>
#include <stdlib.h>
#include "lex.h"

extern int yylex();
extern FILE *yyin;
extern char *yytext;

void check_validity_of_main_arguments(int count);

int main(int argc, char *argv[]) {
	check_validity_of_main_arguments(argc);
	yyin = fopen(argv[1],"r");

	char *token_arr[] = {
					NULL,
					"TOK_KEYWORD", 
					"TOK_IDENTIFIER",
					"TOK_NUMBER",
					"TOK_ASSIGN",
					"TOK_EQUAL",
					"TOK_OPEN_PARAN",
					"TOK_CLOSE_PARAN",
					"TOK_SEMICOLON",
					"TOK_PLUS",
					"TOK_MINUS",
					"TOK_MULT",
					"TOK_DIV",
					"TOK_INVALID" 
				};

	int token;
	while((token = yylex())) {
		printf("Token: %d \t | \t%s\t | \t%s\n", token, yytext, token_arr[token]);		
	}

}
void check_validity_of_main_arguments(int count) {
	if(count < 2) {
		printf("\nPlease provide a valid command\n\t\t Suggested format: $ <a.out> <file.c>\n\n");
		exit(0);
	}
}