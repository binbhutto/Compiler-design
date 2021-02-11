/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 *
 * Description: print file using fgetc.
 */

/*
 *          type (char)                    val (int)
 *
 *	   Relation: R |---> Takes Precedence Over: 7
 *	       	     R |---> Yields Precedence To : 6
 *				 R |---> Accepts              : 5
 *
 *	   Operator: O |---> Addition (+)		  : 0
 *				 O |---> Subtraction (-) 	  : 1
 *				 O |---> Multiplication (*)	  : 2
 *				 O |---> Division (/):        : 3
 *				 O |---> Terminal ($):        : 4
 *
 *	    Operand: P |---> Only Numeric Value   : x
 */

#define RESERVE_TYPE            '$'
#define RESERVE_VALUE	         11
#define RESERVE_VALUE_STOP       12
#define RESERVE_VALUE_TERMINATE  13

#define RELATION_TYPE       'R' 
#define OPERATOR_TYPE       'O'
#define OPERAND_TYPE        'P'

#define TAKES_P_VALUE        7 
#define YIELDS_P_VALUE       6
#define ACCEPT		         5

#define ADDITION_VALUE       0
#define SUBTRACTION_VALUE    1
#define MULTIPLICATION_VALUE 2
#define DIVISION_VALUE       3
#define TERMINATE_VALUE      4


int precedenceTable[5][5] = {
//        '+'            '-'             '*'             '/'            '$'      
	{TAKES_P_VALUE, TAKES_P_VALUE, YIELDS_P_VALUE, YIELDS_P_VALUE, TAKES_P_VALUE},	// '+'
	{TAKES_P_VALUE, TAKES_P_VALUE, YIELDS_P_VALUE, YIELDS_P_VALUE, TAKES_P_VALUE},	// '-'
	{TAKES_P_VALUE, TAKES_P_VALUE, TAKES_P_VALUE, TAKES_P_VALUE, TAKES_P_VALUE},	// '*'
	{TAKES_P_VALUE, TAKES_P_VALUE, TAKES_P_VALUE, TAKES_P_VALUE, TAKES_P_VALUE},		// '/'
	{YIELDS_P_VALUE, YIELDS_P_VALUE, YIELDS_P_VALUE, YIELDS_P_VALUE, ACCEPT}		// '$'
};

typedef struct stackRec {
	char type;
	int val;
}stackRec;

extern stackRec stopElement;
void printlist(stackRec element);

typedef struct node{
	stackRec data;
	struct node *next;
}node;

node *top = NULL;
void push(stackRec element) {
	node *temp=(node *)malloc(sizeof(stackRec));
	temp -> data = element;
	temp -> next = top;
	top = temp;
}
stackRec pop() {
	if(top == NULL) {
		return stopElement;
	} else {
		node *temp = top;
		stackRec returnValue = top->data;
		top = top -> next;
		free(temp);
		return returnValue;
	}
}
void display() {
	node *temp = top;
	printlist(temp->data);
	while(temp->next != NULL) {
		temp = temp->next;
		printlist(temp->data);
	}
	printf("\n\n");
}
stackRec peekOperatorElement() {
	node *temp = top;
	if((temp->data).type == OPERATOR_TYPE) {
			return temp->data;
	}
	while(temp->next != NULL) {
		temp = temp->next;
		if((temp->data).type == OPERATOR_TYPE) {
			return temp->data;
		}
	}
	return stopElement;
}
void printlist(stackRec element) {

	if(element.type == OPERAND_TYPE) {
		printf("|%d|-->", element.val);
	} else {
		switch(element.val) {
			case 0:				 			
				printf("|+|-->");
				break;
			case 1:				 			
				printf("|-|-->");
				break;
			case 2:				 			
				printf("|*|-->");
				break;
			case 3:				 			
				printf("|/|-->");
				break;
			case 4:				 			
				printf("|$|-->");
				break;
			case 5:				 			
				printf("|acc|-->");
				break;
			case 6:				 			
				printf("|<|-->");
				break;
			case 7:				 			
				printf("|>|-->");
				break;
		}
	}

}

