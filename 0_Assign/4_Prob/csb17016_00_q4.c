/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 *
 * Description: 'od' like program from linux with limited functionality of octal number dump only
 */
#include<stdio.h>
#include<stdlib.h>
#define OCTALVLAUE_PER_LINE 16

void checkValidity_of_mainArguments(int count);
void readFilesAnd_dumpOctalValue(short *buffer, int *count, FILE *fptr);


int main(int argc, char *argv[]) {

	checkValidity_of_mainArguments(argc);
	
	FILE *fptr = fopen(argv[1],"rb");

	short buffer;
	int count = 0;
	readFilesAnd_dumpOctalValue(&buffer, &count, fptr);
}

void checkValidity_of_mainArguments(int count) {
	if(count < 2) {
		printf("\nprovide a valid command\n\t\t Suggested format: $./<a.out> <filename>");
		exit(1);
	}
}
void readFilesAnd_dumpOctalValue(short *buffer, int *count, FILE *fptr) {


	printf("%07o    ", *count);
	while(fread(buffer, sizeof(short),1,fptr) == 1) {
		*count += sizeof(short);
		printf("%06o  ",*buffer);
		if(*count % OCTALVLAUE_PER_LINE == 0) {
			printf("\n%07o    ",*count);
		}

	} 
	printf("\n%07o\n", *count);
}