#include <stdio.h>
#include <unistd.h>


int main() {
	int id = fork();
	if (id == 0) {
		char *args[] = {"chromium-browser", NULL};
  		execvp(args[0], args);
	} else {
		printf("Parent\n");
	}
}