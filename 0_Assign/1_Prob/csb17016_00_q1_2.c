/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 */

#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#define MAX_SIZE 100

void print_on_terminal_after_read(char *filename);
void check_validity_of_main_arguments(int count);
int isContain_newlineCharacter(char *string);
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

	char string[MAX_SIZE];
	int count = 1;
	/*
	 * Adding the serial numbers of lines as prefix 
	 */
	printf("\n");
	while((fgets(string,MAX_SIZE,fptr)) != NULL) {
		if(count == 1) {
			printf("%d\t", count++);
		}
		if(isContain_newlineCharacter(string)) {
			printf("%s%d\t",string,count);
			count++;
		} else {
			printf("%s",string);
		}
	}
	printf("\n\n");
	fclose(fptr);
}
int isContain_newlineCharacter(char *string) {
	int i=0;
	while(string[i] != '\0') {
		if(string[i] == '\n') {
			return true;
		}
		i++;
	}
	return false;
}
