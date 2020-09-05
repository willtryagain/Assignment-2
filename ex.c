#include "headers.h"
#include "macros.h"
#include "cd.h"
#include "lsall.h"
#include "pwd.h"

void format(char *word) {
	int n = strlen(word);
	if (word[n-1] == '\n')
		word[n-1] = 0;
}

int ex(int count, char* begin, char* args[SIZE]) {
	if (count == 0)
		return -1;
	// for (int i = 1; i <= count; ++i) 
	// 	printf("%s/", args[i]);
	// for (int i = ; i <= count; ++i) 
	// 	format(args[i]);
	// for (int i = 0; i < count; ++i) 
	// 	printf("%s/", args[i]);
	// printf("\n");
	
	switch (strlen(args[0])) {
		case 2:
			if (strcmp(args[0], "cd") == 0)
				cd(count, begin, args);
			if (strcmp(args[0], "ls") == 0) {
				// for (int i = 0; i < count; ++i)  {
				// 	args[i][strlen(args[i])] = '\n';
				// 	args[i][strlen(args[i])] = 0;
				// }
				ls(count, args);
			}
			break;
		case 3:
			if (strcmp(args[0], "pwd") == 0)
				pwd(count, args);
			break;
		case 4:
			if (strcmp(args[0], "exit") == 0)
				exit(EXIT_SUCCESS);
			break;
		case 5:
			if (strcmp(args[0], "pinfo") == 0)
				return 3;
			break;
	}
	return 5;
}