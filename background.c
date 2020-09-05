#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int id = fork();
	int SIZE = 1024;
	char str[SIZE];
	if (id == 0) {
		char *args[] = {"chromium-browser", NULL};
  		printf("\n");
  		// printf("\t%d", getpid());
  		execvp(args[0], args);
  		// return 0;
	}
	while (1) {
		 if (id) {
			// printf("Parent\n");
			wait(NULL);
			printf("$");
			fgets(str, SIZE, stdin);
		}
	}
}