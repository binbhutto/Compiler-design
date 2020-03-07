#include<stdio.h>
int main() {
	int i = 0;
	for(; i < 10; ++i) {
		printf("Inside: %d\n", i);
	}
	printf("Outside: %d\n", i);

 return 0;
}