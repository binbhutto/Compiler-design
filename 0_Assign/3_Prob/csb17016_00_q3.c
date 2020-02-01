#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

void checkValidity_of_mainArguments(int count);
FILE * openFile_in_textMode(char *fileInitials);
FILE * openFile_in_binaryMode(char *fileInitials);


int main(int argc, char *argv[]) {
	
	checkValidity_of_mainArguments(argc);

	FILE *fptr_txt, *fptr_bin;
	fptr_txt = openFile_in_textMode(argv[1]);
	fptr_bin = openFile_in_binaryMode(argv[1]);
	
	char string[20];
	int rollNo;
	int itemCount_name;
	for(int students = 1; students <= 2; students++) {

		printf("Student %d:\n\t\tName:\t\t",students);
		scanf(" %[^\n]s",string);
		itemCount_name = strlen(string);
		printf("\t\tRoll No:\t");
		scanf("%d",&rollNo);

		fprintf(fptr_txt,"%s,%d\n",string,rollNo);

		fwrite(string,sizeof(char),itemCount_name,fptr_bin);
		fwrite(",",sizeof(","),1,fptr_bin);
		fwrite(&rollNo,sizeof(int),1,fptr_bin);
		fwrite("\n",sizeof("\n"),1,fptr_bin);

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
