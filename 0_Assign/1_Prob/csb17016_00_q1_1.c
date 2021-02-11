/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 *
 * Description: print file using fgetc.
 */

#include<stdlib.h>
#include<stdio.h>

void print_on_terminal_after_read(char *filename);
void check_validity_of_main_arguments(int count);
int main(int argc, char *argv[]) {

	check_validity_of_main_arguments(argc);	
	print_on_terminal_after_read(argv[1]);

	return 0;
}
void check_validity_of_main_arguments(int count) {
	if(count < 2) {
		printf("\nPlease provide a valid command\n\t\t Suggested format: $ <a.out> <file.txt>\n\n");
		exit(0);
	}
}
void print_on_terminal_after_read (char *filename) {
	FILE *fptr = fopen(filename,"r");
	if(fptr == NULL) {
		printf("\n\tSomething went wrong while opening the file !\n\n");
		exit(0);
	}

	char letter;
	int count = 1;
	/*
	 * Adding the serial numbers of lines as prefix 
	 */
	printf("\n");
	while((letter = fgetc(fptr)) != EOF) {
		if(count == 1) {
			printf("%d\t%c",count,letter);
			count++;
		} else if(letter == '\n') {
			printf("%c%d\t",letter,count);
			count++;
		} else {
			printf("%c",letter);
		}
	}
	printf("\n\n");
	fclose(fptr);
}
