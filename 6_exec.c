#include "headers.h"

int main() {
	char *args[] = {"readlink", "/proc/self/exe", NULL};
	execvp(args[0], args);

	printf("end");
	return 0;
}