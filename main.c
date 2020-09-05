#include "headers.h"
#include "macros.h"
#include "prompt.h"
#include "process_args.h"

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
	char begin[SIZE], str[SIZE];
	get_begin(begin);

	while (1) {
		prompt(begin);
		fgets(str, SIZE, stdin);
		split_commands(str, begin);
	}
	return 0;
}