#include "headers.h"

int main() {
	int fork_return = fork();
	if (fork_return == 0) {
		printf("\nI'm the child");
		printf("\nMy ID is %d", getpid());
		printf("\nfork return %d", fork_return); 
		return 0;
	} else {
		printf("\nI'm the parent");
		printf("\nMy ID is %d", getpid());
		printf("\nfork return %d", fork_return); 
		return 0;
	}
}