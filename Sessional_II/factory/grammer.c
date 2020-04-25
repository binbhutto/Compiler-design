/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 * Description: Implement the routines to compute the FIRST and FOLLOW sets of the non-terminals
 * 				of a given grammar. Also, write the routine to create an LL(1) parsing table for the grammar.
 *
 *				Hint: Take a suitable grammar and represent it in appropriate data structures.
 * Sample:
 *
 *			while ( condition ) {
 *			 
 *				    statement ; 
 *				        : 
 *                      :
 *			}
 *
 *
 * Grammar:
 * 			D  -> w(C){S}							
 * 			C  -> iXE
 *			X  -> q | u | v | x | y | z											
 *			S  -> i=E;S | e									
 *			E  -> TR												
 *			R  -> +TR | e 									
 *			T  -> FH 												
 *			H  -> *FH | e 									
 *			F  -> (E) | i | n
 *														
 * Termianls:	w, while			Non-Terminals:	D , Starting Symbol
 *				q, ==        						C , Condition 
 *				u, !=    							S , Statement
 *				v, <=								E , Arithmatic Expression
 *				x, >=								R , Intermediate Term
 *              y, <                                T , Intermediate Term
 *              z, >                                H , Intermediate Term
 *				i, identifier						F , Intermediate Term	
 *				=, assignment						
 *				;, semicolon											
 *				n, number
 *				+, addition
 *				*, multiplication
 *				-, subtraction
 *				(, open brace
 *				), close brace
 *				e, Epsilon								
 */	