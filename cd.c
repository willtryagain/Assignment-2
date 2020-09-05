#include "headers.h"
#include "macros.h"


void cd(int argc, char *begin, char* argv[]) {
	char cwd[SIZE];
	printf("%s\n", begin);
	for (int i = 0; i < argc; ++i)
        printf("%s\n", argv[i]);
	getcwd(cwd, SIZE);
	if (errno)
		perror("getpwd in cd");
	if (argc > 2) {
		printf("cd: too many arguments\n");
		return;
	} else {
		if (argc == 1)
			chdir(begin);
		else if (strcmp(argv[1], "..") == 0 &&
			strcmp(cwd, begin) == 0) {
			//recheck modify path
			strcpy(begin, "");
		}
		else
			chdir(argv[1]);
		if (errno)
			perror("chdir");
		
	}
}

// int main(int argc, char const *argv[]) {
// 	char *args[] = {"cd"};
// 	cd(2, args);
// 	return 0;
// }