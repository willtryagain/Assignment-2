#include "headers.h"
#include "modify_path.h"
#include "macros.h"


void pwd(int count, char *begin, char *args[]) {
	char pwd[SIZE];
	// if (count > 1) {
	// 	printf("\n");
	// 	printf("pwd: too many arguments");
	// 	return;
	// }
	getcwd(pwd, SIZE);
	if (errno)
		perror("pwd");
	// modify_path(begin, pwd);
	printf("%s", pwd);
	printf("\n");
}