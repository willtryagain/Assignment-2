#include <sys/types.h>
#include <sys/wait.h>
#include "headers.h"

int main() {
	int fork_return = fork();
	int i;
	int n = 3;
	if (fork_return == 0) {
		for (int i = 0; i < n; ++i)
			printf("child: %d\n", i+1);
	} else {
		wait(NULL);
		for (int i = 0; i < n; ++i)
			printf("parent: %d\n", i+1);
	}
}