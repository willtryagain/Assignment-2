#include "prompt.h"
#include "headers.h"

const int SIZE = 1024;

void get_begin(char *begin) {
	char cwd[SIZE];
	getcwd(cwd, SIZE);
	if (errno) {
		perror("working directory main");
		return;
	}
	strcpy(begin, cwd);
}

int main() {
	char begin[SIZE];
	get_begin(begin);

	while (1) {
		prompt(begin);
		
	}
}