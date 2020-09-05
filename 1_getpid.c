#include "headers.h"

int main() {
	int pid = getpid();
	printf("My process ID is %d\n", pid);
	for (int i = 0; i < 3; ++i)
		printf("%d\n", getpid());
	for (;;);
	
	return 0;
}