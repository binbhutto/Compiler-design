#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#define CHARACTER_COUNT 4

char queue[CHARACTER_COUNT];
int front = 0,rear = 0, capacity = CHARACTER_COUNT;
int enqueue(char insert);
int dequeue();

int main(int argc, char *argv[]) {

	char letter;
	FILE *fptr = fopen(argv[1],"r");

	int isPreviousCharacter_ascii = false;
	int charPrintable_count = 0;

	while((letter = fgetc(fptr)) != EOF ) {

		if(enqueue(letter) == 1 ) {
			printf("queue is full\n");
		}

		if(isprint(letter)) {
			//printf("\nchar value is : %d\n", (int)letter);

			if(charPrintable_count >= 3) {
				if(charPrintable_count == 3) {
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

	return 0;
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
