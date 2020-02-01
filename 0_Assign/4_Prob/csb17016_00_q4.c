#include<stdio.h>
#include<stdlib.h>

void checkValidity_of_mainArguments(int count);

int main(int argc, char *argv[]) {

	checkValidity_of_mainArguments(argc);
	short buffer;
	int count = 0;

	FILE *fptr = fopen(argv[1],"rb");

	printf("%07o    ",count);
	while(fread(&buffer, sizeof(short),1,fptr) == 1) {
		count += sizeof(short);
		printf("%06o  ",buffer);
		if(count%16 == 0) {
			printf("\n%07o    ",count);
		}

	} 
	printf("\n%07o\n",count);

}
void checkValidity_of_mainArguments(int count) {
	if(count < 2) {
		printf("\nprovide a valid command\n\t\t Suggested format: $./<a.out> <filename>");
		exit(1);
	}
}