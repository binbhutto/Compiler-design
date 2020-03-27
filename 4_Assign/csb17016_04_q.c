/* Copyright (c) Adil Bin Bhutto. All rights reserved.
 *
 * Descripton: Write a recursive descent parser for the construct mentioned in the previous question.
 *
 * Grammar:
 * 			D  -> w(C)bSe							Non-Terminals:	D , Starting Symbol
 * 			C  -> ixE | iyE											C , Condition 
 * 			S  -> i=E;S | epsilon									S , Statement
 * 			E  -> TE'												E , Arithmatic Expression
 *			E' -> +TE' | epsilon 									E', Intermediate Term
 * 			T  -> FT' 												T , Intermediate Term
 *			T' -> *FT' | epsilon 									T', Intermediate Term
 * 			F  -> (E) | i | n 										F , Intermediate Term
 *														
 *														Termianls:	w, while
 *																	b, begin
 *																	e, end
 *																	x, ==
 *																	y, !=
 *																	i, identifier
 *																	=, assignment
 *																	;, semicolon
 *																	n, number
 *																	+, addition
 *																	*, multiplication
 *																	-, subtraction
 *																	(, open brace
 *																	), close brace
 *														      		epsilon, Epsilon
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "lex.h"

extern int yylex();
extern FILE *yyin;
extern char *yytext;

char token;

void match(char symbol);
void check_validity_of_main_arguments(int count);

void D();
void C();
void S();
void E();
void E_prime();
void T();
void T_prime();
void F();

int main(int argc, char *argv[]) {
	check_validity_of_main_arguments(argc);
	yyin = fopen(argv[1],"r");
	token = yylex();
	while(token = yylex()) {
		print("%c",token);
	}
	// D();
	// if(token == '$') {
	// 	printf("Parsing Successful\n");
	// }
}
void check_validity_of_main_arguments(int count) {
	if(count < 2) {
		printf("\nPlease provide a valid command\n\t\t Suggested format: $ <a.out> <file.c>\n\n");
		exit(0);
	}
}
void match(char symbol) {
	if(token == symbol) {
		token = yylex();
	} else {
		printf("Parsing Failed\n");
		exit(0);
	}
}

void D() {
	if ( token == 'w') {
		match('w');
		match('(');
		C();
		match(')');
		match('b');
		S();
		match('e');
	} 
}
void C() {
	if(token == 'i') {
		match('i');
		if(token == 'x' || token == 'y') {
			switch(token) {
				case 'x':
					match('x');
					break;
				case 'y':
					match('y');
			}
			E();
		}
	}

}
void S() {
	if(token == 'i') {
		match('i');
		match('=');
		E();
		match(';');
		S();
	} else {
		return;
	}

}
void E() {
	T();
	E_prime();

}
void E_prime(){
	if(token == '+') {
		match('+');
		T();
		E_prime();
	} else {
		return;
	}
}
void T() {
	F();
	T_prime();
}
void T_prime() {
	if(token == '*') {
		match('*');
		F();
		T_prime();
	} else {
		return;
	}
}
void F() {
	if(token == '(') {
		match('(');
		E();
		match(')');
	} else if (token == 'i') {
		match('i');
	} else if (token == 'n') {
		match('n');
	}

}









