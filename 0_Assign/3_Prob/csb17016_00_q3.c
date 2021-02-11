/*
 * Copyright (c) Adil Bin Bhutto. All rights reserved.
 *
 * Description: It takes 20 student names and their respective rollno from user
 * 				and stores them in 
 *									1) Binary 
 *								and 2) Text 	format.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define TOTAL_STUDENT 20

void checkValidity_of_mainArguments(int count);
FILE * openFile_in_textMode(char *fileInitials);
FILE * openFile_in_binaryMode(char *fileInitials);

void getUserInput_of_Student_and_rollno(char *studentName, int *rollNo, int *studentName_length, int *students);
void writeTheInput_inTextFile(char *studentName,int rollNo,FILE *fptr_txt);
void writeTheInput_inBinaryFile(char *studentName,int studentName_length,int *rollNo,FILE *fptr_bin);

int main(int argc, char *argv[]) {
	
	checkValidity_of_mainArguments(argc);

	FILE *fptr_txt, *fptr_bin;
	fptr_txt = openFile_in_textMode(argv[1]);
	fptr_bin = openFile_in_binaryMode(argv[1]);
	
	char studentName[20];
	int rollNo;
	int studentName_length;
	for(int students = 1; students <= TOTAL_STUDENT; students++) {

		getUserInput_of_Student_and_rollno(studentName,&rollNo,&studentName_length, &students);
		writeTheInput_inTextFile(studentName,rollNo,fptr_txt);
		writeTheInput_inBinaryFile(studentName,studentName_length,&rollNo,fptr_bin);
	}
	
	fclose(fptr_txt);
	fclose(fptr_bin);
	return 0;
}

void checkValidity_of_mainArguments(int count) {
	if(count < 2) {
		printf("\nprovide a valid command\n\t\t Suggested format: $./<a.out> <filename>");
		exit(1);
	}
}
FILE * openFile_in_textMode(char *fileInitials) {
	char buffer[20];
	strcpy(buffer,fileInitials);
	char *textFile = strcat(buffer,".txt");
	FILE *fptr = fopen(textFile, "w+");
	if(fptr == NULL) {
		printf("Something went wrong while opening text file\n");
	}
	return fptr;
}
FILE * openFile_in_binaryMode(char *fileInitials) {
	char buffer[20];
	strcpy(buffer,fileInitials);
	char *binaryFile = strcat(buffer,".bin");
	FILE *fptr = fopen(binaryFile, "wb+");
	if(fptr == NULL) {
		printf("Something went wrong while opening binary file");
	}
	return fptr;
}
void getUserInput_of_Student_and_rollno(char *studentName, int *rollNo, int *studentName_length, int *students){
	printf("Student %d:\n\t\tName:\t\t",*students);
	scanf(" %[^\n]s",studentName);
	printf("\t\tRoll No:\t");
	scanf("%d",rollNo);
	*studentName_length = strlen(studentName);
}
void writeTheInput_inTextFile(char *studentName,int rollNo,FILE *fptr_txt){
	
	fprintf(fptr_txt,"%s,%d\n",studentName,rollNo);
}
void writeTheInput_inBinaryFile(char *studentName,int studentName_length,int *rollNo,FILE *fptr_bin){
	fwrite(studentName,sizeof(char),studentName_length,fptr_bin);
	fwrite(",",sizeof(","),1,fptr_bin);
	fwrite(rollNo,sizeof(int),1,fptr_bin);
	fwrite("\n",sizeof("\n"),1,fptr_bin);
}
