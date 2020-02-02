/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 *
 * Description: 'strings' like program from linux which tries to all the strings from a file
 * 				and string length must be greater than 4
 */
#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>
#define CHARACTER_COUNT 4

char queue[CHARACTER_COUNT];
int front = 0,rear = 0, capacity = CHARACTER_COUNT;
int enqueue(char insert);
int dequeue();

void checkValidity_of_mainArguments(int count);
void printStrings(FILE *fptr);

int main(int argc, char *argv[]) {

	checkValidity_of_mainArguments(argc);

	FILE *fptr = fopen(argv[1],"r");
	printStrings(fptr);

	return 0;
}

void checkValidity_of_mainArguments(int count) {
	if(count < 2) {
		printf("\nprovide a valid command\n\t\t Suggested format: $./<a.out> <filename>");
		exit(1);
	}
}

void printStrings(FILE *fptr) {
	char letter;
	int isPreviousCharacter_ascii = false;
	int charPrintable_count = 0;

	while((letter = fgetc(fptr)) != EOF ) {

		if(enqueue(letter) == 1 ) {
			printf("queue is full\n");
		}

		if(isprint(letter)) {

			if(charPrintable_count >= (CHARACTER_COUNT - 1)) {
				if(charPrintable_count == (CHARACTER_COUNT - 1)) {
					for(int i = 0; i < 4; i++){
						printf("%c",dequeue());
					}
					charPrintable_count++;
				} else {
					printf("%c",dequeue());
					charPrintable_count++;
				}
			} else {
				isPreviousCharacter_ascii = true;
				charPrintable_count++;
			}						
		} else {

			while(dequeue() != 1) {
				dequeue();
			}
			if((isPreviousCharacter_ascii == true) && (charPrintable_count > 4))
				printf("\n");
			charPrintable_count = 0;
			isPreviousCharacter_ascii = false;
		}
		
	}
}


int enqueue(char insert) {
	if(rear == capacity) {
		return 1;
	} else {
		queue[rear] = insert;
		rear++;
		return 0;
	}
}

int dequeue() {
	if(front == rear) {
		return 1;
	} else {
		int value = queue[front];
		for(int i = front; i < rear; i++) {
			queue[i] = queue[i+1]; 
		}
		rear--;
		return value;
	}
}
