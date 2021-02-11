#include<stdio.h>
#include<stdlib.h>
#include "stateTable.h"

#define ID  
#define RELOP
#define NUMBER

#define FINALSTATES 17



FILE *fptr;
char symbol;

int prevState;
int state=0;
int symbolIndex;

int main(int argc, char *argv[]) {

	fptr = fopen(argv[1],"r");

	while((symbol = fgetc(fptr)) != EOF) {
		symbolIndex = getSymbolIndex(symbol);
		//printf("Symbol Index: %d\n", symbolIndex);
		if(symbolIndex == 101) {
			printf("Undefined Symbol Encountered: %c", symbol);
			exit(1);
		}

		prevState = state;
		//printf("prevState: %d\n", prevState);
		state = stateTable[state][symbolIndex];
		//printf("state: %d\n", state);
		if(state != FINALSTATES) {
			continue;
		}
		
		state = 0;
		switch(prevState) {
			case 2:
					printf("RELOP, LE\n");
					break;
			case 3:
					printf("RELOP, NE\n");
					ungetc(symbol, fptr);
					break;
			case 5:
					printf("RELOP, CM\n");
					break;
			case 6:
					printf("RELOP, EQ\n");
					ungetc(symbol, fptr);
					break;
			case 8:
					printf("RELOP, GE\n");
					break;
			case 9:
					printf("RELOP, GT\n");
					ungetc(symbol, fptr);
					break;
			case 11:
					printf("ID\n");
					ungetc(symbol, fptr);
					break;
			case 13:
					printf("NUMBER\n");
					ungetc(symbol, fptr);
					break;
			case 15:
					ungetc(symbol, fptr);
					break;

		}
	}
}

