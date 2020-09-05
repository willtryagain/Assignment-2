#include "headers.h"

int main(int argc, char const *argv[]) {
	printf("before %d\n", getpid());
	int fork_return = fork();

	printf("twice %d\n", getpid());
	
	if (fork_return == 0) 
		printf("child %d\n", getpid());
	else 
		printf("parent %d\n", getpid());
	
	printf("twice %d\n", getpid());
	return 0;
}