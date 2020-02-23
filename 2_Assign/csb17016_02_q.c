#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "opTable.h"

extern node *top;

stackRec prevElement = {RESERVE_TYPE, RESERVE_VALUE};
stackRec currentElement = {RESERVE_TYPE, RESERVE_VALUE};
stackRec stopElement = {RESERVE_TYPE, RESERVE_VALUE_STOP};
stackRec terminateElement = {RESERVE_TYPE, RESERVE_VALUE_TERMINATE};

bool isInputValid(stackRec startElement, stackRec prevElement, stackRec currentElement, stackRec terminateElement);
bool isElementsEqual(stackRec elementA, stackRec elementB);
stackRec getUserInput();
bool isPureNumber(char *string);
bool isPure_singleChar(char *string);

int shiftReduce(stackRec currentElement);

stackRec terminalOperator = {OPERATOR_TYPE, TERMINATE_VALUE};


int main() {

	stackRec startElement = prevElement;

	push(terminalOperator);
	printf("\n\t\tOperator Manual:\n\t\t\t\tThis Calculator accepts only valid numerical values and +,-,*,/ operators\n\t\t\t\t          It showcases the mechanics of stack based calculation\n\t\t\t\t               Brackets are not supported in this version\n\t\t\t\t      * To terminate your arithmatic sequence use '$' as end of input\n");

	while (!isElementsEqual(currentElement, stopElement)) {
		prevElement = currentElement;

		currentElement = getUserInput();
		if(!isInputValid(startElement, prevElement, currentElement, terminateElement)) {
			printf("\n\t\t----------------------------  Input Sequence is not Valid. Please try again !  ---------------------\n");
			return 1;
		}
		if(!isElementsEqual(currentElement, stopElement)) {
			shiftReduce(currentElement);
		}


	}

	shiftReduce(terminalOperator);
	printf("\n\n\t\t\tResult of the Given Arithmatic Expresion is:\t%d\n\n", pop().val);
	return 0;
}


bool isInputValid(stackRec startElement, stackRec prevElement, stackRec currentElement, stackRec terminateElement){
	
	if(isElementsEqual(currentElement, terminateElement)) {
		return false;
	} else if(isElementsEqual(prevElement, startElement) && currentElement.type != OPERAND_TYPE) {
		return false;
	} else if (currentElement.type == prevElement.type) {
		return false;
	} else if (isElementsEqual(stopElement, currentElement) && (prevElement.type != OPERAND_TYPE)){
		return false;
	} else {
		return true;
	}
}
bool isElementsEqual(stackRec elementA, stackRec elementB) {

	if((elementA.val == elementB.val) && (elementA.type == elementB.type)) {
		return true;
	} else {
		return false;
	}
}
stackRec getUserInput() {
	stackRec returnElement;
	char buffer[10];

	printf("Arithmatic Exp. Please: ");
	scanf("%s",buffer);

	if(isPureNumber(buffer)) {
		returnElement.type = OPERAND_TYPE;
		returnElement.val = atoi(buffer);
		return returnElement;
	} else if(isPure_singleChar(buffer)) {
		char operator = buffer[0];
		returnElement.type = OPERATOR_TYPE;

		if(operator == '+') {
			returnElement.val = ADDITION_VALUE;
			return returnElement;
		} else if (operator == '-') {
			returnElement.val = SUBTRACTION_VALUE;
			return returnElement;
		} else if (operator == '*') {
			returnElement.val = MULTIPLICATION_VALUE;
			return returnElement;
		} else if (operator == '/') {
			returnElement.val = DIVISION_VALUE;
			return returnElement;
		} else if (operator == '$') {
			return stopElement;
		} else {
			return terminateElement;
		}
	} else {
		return terminateElement;
	}
}
bool isPureNumber(char *string){
	for(int i=0; i < strlen(string); i++) {
		if(!isdigit(string[i])) {
			return false;
		}
	}
	return true; 
}
bool isPure_singleChar(char *string){
	if((int)strlen(string) == 1) {
		return true;
	}
	return false; 
}
int shiftReduce(stackRec currentElement) {
	if(currentElement.type == OPERAND_TYPE) {
		push(currentElement);
		display();
	} else {
		stackRec operatorElement;
		operatorElement = peekOperatorElement();
		if(isElementsEqual(operatorElement, stopElement)) {
			return 1;
		} else {
			int relation;
			relation = precedenceTable[operatorElement.val][currentElement.val];

			if(relation == YIELDS_P_VALUE) {
				stackRec relationElement = {RELATION_TYPE, relation};
				push(relationElement);
				push(currentElement);
				display();

			} else if(relation == TAKES_P_VALUE) {
				while (relation != YIELDS_P_VALUE) {
					int Result, A, B, Op;
					B = pop().val;
					Op = pop().val;
					pop();
					A = pop().val;
					switch(Op) {
						case 0:
							Result = A + B;
							break;
						case 1:
							Result = A - B;
							break;
						case 2:
							Result = A * B;
							break;
						case 3:
							Result = A / B;
							break;
					}
					stackRec resultElement = {OPERAND_TYPE, Result};
					push(resultElement);
					display();

					operatorElement = peekOperatorElement();
					if(isElementsEqual(operatorElement, stopElement)) {
						return 1;
					}
					relation = precedenceTable[operatorElement.val][currentElement.val];
				}
				stackRec relationElement = {RELATION_TYPE, relation};
				push(relationElement);
				push(currentElement);
				display();
			} 
		}

	}
	return 0;
}


