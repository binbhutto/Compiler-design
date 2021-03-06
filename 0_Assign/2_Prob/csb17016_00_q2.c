/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 *
 * Description: Prints the specific numbered word as per user's repquest from each line.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void checkValidity_of_mainArguments(int count);
void printSpecified_word_fromEachLine(char *filename, int wordNo);

int main(int argc, char *argv[]) {
	
	checkValidity_of_mainArguments(argc);

	char *filename = argv[1];
	int wordNo = atoi(argv[2]);
	printSpecified_word_fromEachLine(filename,wordNo);

	return 0;
}

void checkValidity_of_mainArguments(int count) {
	if(count < 3) {
		printf("\nPlease provide a valid command\n\t\t Suggested format: $./<a.out> <filename.txt> <number>");
		exit(1);
	}

}
void printSpecified_word_fromEachLine(char *filename, int wordNo) {
	FILE *fptr = fopen(filename,"r");
	if(fptr == NULL) {
		printf("Something went wrong while opening the file !\n\n");
		exit(1);
	}
	/*
	 * previouseSpace acknowledges new word encounter
	 * printSuccess refers to any successful print of expected word print else helps to print NULL 
	 * count keeps track of current word number in line while reading
	 */
	
	int previousSpace = false;
	int printSuccess = false;
	int count = 1;
	char letter;

	while((letter = fgetc(fptr)) != EOF) {
		if(letter == ' ') {
			previousSpace = true;
		} else if(letter == '\n') {
			previousSpace = false;
			if(printSuccess == false) {
				printf("NULL");
			}
			printSuccess = false;
			printf("\n");
			count = 1;
		} else if(previousSpace == true) {
			previousSpace = false;
			count++;
			if(count == wordNo) {
				printSuccess = true;
				printf("%c",letter);
			}
		} else {
			previousSpace = false;
			if(count == wordNo) {
				printSuccess = true;
				printf("%c",letter);
			}
		}	
	}

}
