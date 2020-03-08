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
 * 
 * Grammar:
 * 			D -> w(C)bSe							Non-Terminals:	D, Starting Symbol
 * 			C -> i x E | i y E										C, Condition 
 * 			S -> i = E; | i = E;S									S, Statement
 * 			E -> E + T | T 											E, Arithmatic Expression
 * 			T -> T * F | F 											T, Intermediate Term
 * 			F -> (E) | i | n 										F, Intermediate Term
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
 *	Operator Precedence Table:
 *		  w b e x y i = ; n + * - ( )
 *	  	w                         =
 *		b     =     <
 *		e
 *		x           <     < < <   < >
 *		y           <     < < <   < >       
 *		i       = =   = >   > >     >
 *		=           <   = < < <   <
 *		;     >     >
 *		n               >   > >     >
 *		+           <   > < > <   < >
 *		*           <   > < > >   < >
 *		-           <               =
 *		(   =       <     < < <   <
 *		)               >   > >     >													
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#define MAX_PROD 10	
#define MAX_SIZE 50
	
char *grammar[MAX_PROD];
int print_rec[MAX_PROD];
FILE *fptr;

void print(char ** strings);

void TRAILING(char *string, char **strings, int currentPosition, int totalProductions);
void LEADING(char *string, char **strings, int currentPosition, int totalProductions);
bool checkTerminal(char c);
int findProduction(char NT, char **strings, int currentPosition, int totalProductions);
void rec_initialize(int *rec){
	for (int i = 0; i < sizeof(rec); i++) {
		rec[i] = 0;
	}
}

int main () {


	for (int i = 0; i < MAX_PROD; i++ ) {
		grammar[i] = (char *)malloc(MAX_SIZE * sizeof(char));

	}
	fptr = fopen("grammar.txt", "r");
	if(fptr == NULL) {
		printf("Something went wrong while opening the grammar file\n");
		return 1;
	}

	int i = 0;
	while(fgets(grammar[i], MAX_SIZE, fptr) != NULL) {
		i++;
	}
	int totalProductions = i;
	printf("\n\nTRAILING set :\n");
	for(int i = 0; i < totalProductions; i++) {
		rec_initialize(print_rec);
		printf("\t\t\t%c: { ", grammar[i][0]);
		TRAILING(grammar[i], grammar, i, totalProductions);
		printf("}\n");
	}
	printf("LEADING set :\n");
	for(int i = 0; i < totalProductions; i++) {
		rec_initialize(print_rec);
		printf("\t\t\t%c: { ", grammar[i][0]);
		LEADING(grammar[i], grammar, i, totalProductions);
		printf("}\n");
	}
	printf("\n\n");

	fclose(fptr);
	return 0;
}

void TRAILING(char *string, char **strings, int currentPosition, int totalProductions) {
	int i = MAX_SIZE - 1;
	while(string[i] != '\n')i--;
	for(i--; i >= 1; i--) {
		if(checkTerminal(string[i])) {
			printf("%c, ", string[i]);
			while((string[i] != '|') && (string[i] != '-')) i--;
		} else if (isupper(string[i]) && (string[i+1] == '\n' || string[i+1] == '|')) {
			int productionNumber;
			if((productionNumber = findProduction(string[i], strings, currentPosition, totalProductions)) != -1) {
				TRAILING(strings[productionNumber], strings, productionNumber, totalProductions);
			}
		} else if (string[i] != '|') {
			continue;
		}
		if (string[i] == '-') break;
	}

}
void LEADING(char *string, char **strings, int currentPosition, int totalProductions) {
	int i = 2;
	for(; i < MAX_SIZE; i++) {
		if(checkTerminal(string[i])) {
			printf("%c, ", string[i]);
			while((string[i] != '|') && (string[i] != '\n')) i++;
		} else if (isupper(string[i]) && (string[i-1] == '|' || string[i-1] == '-')) {
			int productionNumber;
			if((productionNumber = findProduction(string[i], strings, currentPosition, totalProductions)) != -1) {
				LEADING(strings[productionNumber], strings, productionNumber, totalProductions);
			}
		}
		if (string[i] == '\n') break;
	}

}

bool checkTerminal(char c) {
	if (isupper(c) || c == '|' || c == '-' || c == ' ' || c == '\n') return false;
	else return true;
}

int findProduction(char NT, char **strings, int currentPosition, int totalProductions) {
	for(int i = 0; i < totalProductions; i++) {
		if( i == currentPosition ) continue;
		if(strings[i][0] == NT && print_rec[i] == 0) {
			print_rec[i] = 1;
			return i;
		} 
	}
	return -1;

}
void print(char ** strings) {
	for (int i = 0; i < MAX_PROD; i++){
		printf("%c: %s\n",grammar[i][0], strings[i]);
	}
}








